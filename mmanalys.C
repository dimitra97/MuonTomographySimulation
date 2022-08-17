#define mmanalys_cxx
#include "mmanalys.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TH1.h"
#include "TMath.h"
#include "Track.h"
#define pi TMath::Pi()
#define Nvoxels 1000



double distance(double x1,double y1,double z1,double x2,double y2, double z2){
  
  return(TMath::Sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2)));

}

//a function that finds the poca point (x,y,z) and returns it as a vector in 3d space

TVector3 POCA(double (&x)[Nvoxels], double (&y)[Nvoxels], double (&z)[Nvoxels], Track track1xz, Track track2xz, Track track1yz, Track track2yz){

  double x1,y1,z1,x2,y2,z2,dist;
  double mindist=100000.;
  TVector3 pocapoint;
  
  for(int i=0;i<Nvoxels;i++){
    z1=z[i];
    x1=(z1-track1xz.GetIntrc())/track1xz.GetSlope();
    y1=(z1-track1yz.GetIntrc())/track1yz.GetSlope();
    //std::cout<<i<<z[i]<<std::endl;
    for(int j=0;j<Nvoxels;j++){
      z2=z[j];
      x2=(z2-track2xz.GetIntrc())/track2xz.GetSlope();
      y2=(z2-track2yz.GetIntrc())/track2yz.GetSlope();
      dist=distance(x1,y1,z1,x2,y2,z2);
      // std::cout<<dist<<std::endl;
      if(dist<mindist){
	pocapoint=TVector3((x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
	mindist=dist;


      }
	

    }


  }

  return pocapoint;

}

void mmanalys::Loop()
{
  //   In a ROOT session, you can do:
  //      root> .L mmanalys.C
  //      root> mmanalys t
  //      root> t.GetEntry(12); // Fill t data members with entry number 12
  //      root> t.Show();       // Show values of entry 12
  //      root> t.Show(16);     // Read and show values of entry 16
  //      root> t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch


  double posz1[2]={125,75};
  double posz2[2]={-75,-125};
  double posx1[2];
  double posy1[2];
  double posx2[2];
  double posy2[2];
  double slopexz1,slopexz2,slopeyz1,slopeyz2,intrcxz1,intrcxz2,slope;
  double anglexz1,anglexz2,angleyz1,angleyz2,intrcyz1,intrcyz2;
  double zcube;
  TVector3 pocapoint;
  Track trackxz1,trackxz2,trackyz1,trackyz2;
  int sum=0;

 
  //voxelization for the poca algorithm
  //int Nvoxels=10000;
  double x[Nvoxels],y[Nvoxels],z[Nvoxels],dx=150./Nvoxels, dy=150./Nvoxels, dz=150./Nvoxels;
  x[0]=-75.; y[0]=-75.; z[0]=-75.;

  for(int i=1;i<Nvoxels+1;i++){
    x[i]=x[i-1]+dx;
    y[i]=y[i-1]+dy;
    z[i]=z[i-1]+dz;

  }

  TH1F *hist_scatteranglexz=new TH1F("hist_scatteranglexz","Deflection angle on xz", 40,-20,20);
  TH1F *hist_scatterangleyz=new TH1F("hist_scatterangleyz","Deflection angle on yz", 40,-20,20);
  TH3F *hist_image=new TH3F("hist_image","Image reconstruction with POCA algorithm",50,-75,75,50,-75,75,50,-75,75);
  TH1F *hist_pocapoints=new TH1F("hist_pocapoints","POCA point counts per voxel",Nvoxels,0,Nvoxels);
  

  
 


    if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;


    std::cout<<"jentry="<<jentry<<std::endl;
    posx1[0]=TMM1X;
    posx1[1]=TMM2X;
    posx2[0]=TMM3X;
    posx2[1]=TMM4X;

    posy1[0]=TMM1Y;
    posy1[1]=TMM2Y;
    posy2[0]=TMM3Y;
    posy2[1]=TMM4Y;

    TGraph* grxz1=new TGraph(2,posx1,posz1);
    TGraph* grxz2=new TGraph(2,posx2,posz2);
    TF1 *fg1=new TF1("fg1","pol1",posx1[0],posx1[1]);
    grxz1->Fit(fg1);
    TF1 *fg2=new TF1("fg2","pol1",posx2[0],posx2[1]);
    grxz2->Fit(fg2);
    //cout<<"entry="<<jentry<<endl;
    //slope=(posz1[0]-posz1[1])/(posx1[0]-posx1[1]);
    trackxz1.SetSlope(fg1->GetParameter(1));
    //slope=(posz2[0]-posz2[1])/(posx2[0]-posx2[1]);
    trackxz2.SetSlope(fg2->GetParameter(1));
    
    trackxz1.SetIntrc(fg1->GetParameter(0));
    trackxz2.SetIntrc(fg2->GetParameter(0));
    anglexz1=atan(trackxz1.GetSlope())*180/pi;
    anglexz2=atan(trackxz2.GetSlope())*180/pi;

    TGraph* gryz1=new TGraph(2,posy1,posz1);
    TGraph* gryz2=new TGraph(2,posy2,posz2);
    TF1 *fg1y=new TF1("fg1y","pol1",posy1[0],posy1[1]);
    gryz1->Fit(fg1y);
    TF1 *fg2y=new TF1("fg2y","pol1",posy2[0],posy2[1]);
    gryz2->Fit(fg2y);
    //cout<<"entry="<<jentry<<endl;
    //slope=(posz1[0]-posz1[1])/(posy1[0]-posy1[1]);
    trackyz1.SetSlope(fg1y->GetParameter(1));
    //slope=(posz2[0]-posz2[1])/(posy2[0]-posy2[1]);
    trackyz2.SetSlope(fg2y->GetParameter(1));
    trackyz1.SetIntrc(fg1y->GetParameter(0));
    trackyz2.SetIntrc(fg2y->GetParameter(0));
    angleyz1=atan(trackyz1.GetSlope())*180/pi;
    angleyz2=atan(trackyz2.GetSlope())*180/pi;
   

    if(anglexz1<0) anglexz1+=180;
    if(anglexz2<0) anglexz2+=180;
    if(angleyz1<0) angleyz1+=180;
    if(angleyz2<0) angleyz2+=180;
      
    hist_scatteranglexz->Fill(anglexz1-anglexz2);
     

    hist_scatterangleyz->Fill(angleyz1-angleyz2);

    if(abs(anglexz1-anglexz2)>=0.3 && abs(angleyz1-angleyz2)>=0.3){
      
      //std::cout<<"anglesxz="<<anglexz1<<","<<anglexz2<<std::endl;
      // std::cout<<"anglesyz="<<angleyz1<<","<<angleyz2<<std::endl;
    
    //POCA Algorithm for the image reconstruction--> Keeps the coordinates of the determined poca point in a threevector
    pocapoint=TVector3(POCA(x, y, z, trackxz1, trackxz2, trackyz1, trackyz2));
    // std::cout<<"poca(x,y,z)="<<pocapoint.x()<<","<<pocapoint.y()<<","<<pocapoint.z()<<std::endl;
    hist_image->Fill(pocapoint.x(),pocapoint.y(),pocapoint.z());
   

    }
      
    //std::cin.ignore();

    

   
    
   

  }

  TFile *file=new TFile("Plots.root","RECREATE");

   // TCanvas *c1=new TCanvas();
  //  c1->Divide(2,1);

  // c1->cd(1);
  hist_scatteranglexz->SetTitle("Scatter angle on xz plane");
  hist_scatteranglexz->Write();
  delete hist_scatteranglexz;

  //c1->cd(2);
  hist_scatterangleyz->SetTitle("Scatter angle on yz plane");
  hist_scatterangleyz->Write();
  delete hist_scatterangleyz;

  //TCanvas *c2=new TCanvas();
  hist_image->SetOption("LEGO2Z");
  hist_image->Write();
  delete hist_image;

  hist_pocapoints->SetTitle("POCA point counts");
  hist_pocapoints->Write();
  delete hist_pocapoints;

  
  // c1->Write();
  // c2->Write();
  
  file->Close();

  std::cout<<"sum="<<sum<<std::endl;

   

}
