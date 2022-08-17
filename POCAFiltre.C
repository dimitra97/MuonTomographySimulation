{


  int Nbinsx=50,Nbinsy=50,Nbinsz=50;
  //int Nvoxels=500;
  int neighborszero;
  TFile *f=new TFile("Plots.root");
  TH3F *hist_image=(TH3F*)f->Get("hist_image;1");
  TH1F *hist_pocapoints=new TH1F("hist_pocapoints","POCA point counts per voxel",50,0,50);

  int sum=0;
  

  for(int i=0;i<Nbinsx;i++){
    for(int j=0;j<Nbinsy;j++){
      for(int k=0;k<Nbinsz;k++){
	neighborszero=0;

	for(int in=i-1;in<i+2;in++) {
	  if(hist_image->GetBinContent(in,j,k)==0) neighborszero+=1;
	}

	for(int jn=j-1;jn<j+2;jn++){
	  if(hist_image->GetBinContent(i,jn,k)==0) neighborszero+=1;

	}

	for(int kn=k-1;kn<k+2;kn++){
	  if(hist_image->GetBinContent(i,j,kn)==0) neighborszero+=1;

	}

	if(neighborszero>=4) {
	  hist_image->SetBinContent(i,j,k,0);
	  sum+=1;
	}

      }

    }
  }

  TFile *f1=new TFile("FiltredImage.root","RECREATE");

  TH2F *hist_image_xyproject=(TH2F*)hist_image->Project3D("xy");
  hist_image_xyproject->SetOption("COL2Z");
  hist_image_xyproject->Write();

  hist_image->SetOption("LEGO2Z");
  hist_image->Write();
  delete hist_image;

  f1->Close();

  std::cout<<sum<<std::endl;
  


}
