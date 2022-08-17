//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 18 12:54:01 2022 by ROOT version 6.24/02
// from TTree 102/X,Y Positions on MicroMegas
// found on file: testem5.root
//////////////////////////////////////////////////////////

#ifndef mmanalys_h
#define mmanalys_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class mmanalys {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        TMM1X;
   Double_t        TMM1Y;
   Double_t        TMM2X;
   Double_t        TMM2Y;
   Double_t        TMM3X;
   Double_t        TMM3Y;
   Double_t        TMM4X;
   Double_t        TMM4Y;

   // List of branches
   TBranch        *b_TMM1X;   //!
   TBranch        *b_TMM1Y;   //!
   TBranch        *b_TMM2X;   //!
   TBranch        *b_TMM2Y;   //!
   TBranch        *b_TMM3X;   //!
   TBranch        *b_TMM3Y;   //!
   TBranch        *b_TMM4X;   //!
   TBranch        *b_TMM4Y;   //!

   mmanalys(TTree *tree=0);
   virtual ~mmanalys();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef mmanalys_cxx
mmanalys::mmanalys(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("testem5b.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("testem5b.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("testem5b.root:/ntuple");
      dir->GetObject("102",tree);

   }
   Init(tree);
}

mmanalys::~mmanalys()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t mmanalys::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t mmanalys::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void mmanalys::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("TMM1X", &TMM1X, &b_TMM1X);
   fChain->SetBranchAddress("TMM1Y", &TMM1Y, &b_TMM1Y);
   fChain->SetBranchAddress("TMM2X", &TMM2X, &b_TMM2X);
   fChain->SetBranchAddress("TMM2Y", &TMM2Y, &b_TMM2Y);
   fChain->SetBranchAddress("TMM3X", &TMM3X, &b_TMM3X);
   fChain->SetBranchAddress("TMM3Y", &TMM3Y, &b_TMM3Y);
   fChain->SetBranchAddress("TMM4X", &TMM4X, &b_TMM4X);
   fChain->SetBranchAddress("TMM4Y", &TMM4Y, &b_TMM4Y);
   Notify();
}

Bool_t mmanalys::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void mmanalys::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t mmanalys::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef mmanalys_cxx
