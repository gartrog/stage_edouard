//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 22 13:47:56 2015 by ROOT version 6.02/12
// from TTree tupletest/tupletest
// found on file: ttbar.root
//////////////////////////////////////////////////////////

#ifndef VHNtuple_h
#define VHNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

class VHNtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           njets;
   std::vector<float>   *jets_E;
   std::vector<float>   *jets_pt;
   std::vector<float>   *jets_phi;
   std::vector<float>   *jets_eta;
   std::vector<int>     *jets_ind;
   std::vector<float>   *jets_MV1;
   std::vector<int>     *jets_truth;
   std::vector<bool>    *jets_isVetoJet;
   std::vector<bool>    *jets_isSignal;
   Int_t           nfatJets;
   std::vector<float>   *fatJets_E;
   std::vector<float>   *fatJets_pt;
   std::vector<float>   *fatJets_phi;
   std::vector<float>   *fatJets_eta;
   std::vector<int>     *fatJets_ind;
   std::vector<float>   *fatJets_jvf;
   std::vector<float>   *fatJets_tau21;
   std::vector<float>   *fatJets_tau32;
   Int_t           nmuons;
   std::vector<float>   *muons_E;
   std::vector<float>   *muons_pt;
   std::vector<float>   *muons_phi;
   std::vector<float>   *muons_eta;
   std::vector<int>     *muons_ind;
   std::vector<float>   *muons_ptcone20;
   std::vector<float>   *muons_etcone30;
   std::vector<int>     *muons_type;
   std::vector<bool>    *muons_isVHL;
   std::vector<bool>    *muons_isZH;
   std::vector<bool>    *muons_isWH;
   Int_t           ntaus;
   std::vector<float>   *taus_E;
   std::vector<float>   *taus_pt;
   std::vector<float>   *taus_phi;
   std::vector<float>   *taus_eta;
   std::vector<int>     *taus_ind;
   Int_t           nelectrons;
   std::vector<float>   *electrons_E;
   std::vector<float>   *electrons_pt;
   std::vector<float>   *electrons_phi;
   std::vector<float>   *electrons_eta;
   std::vector<int>     *electrons_ind;
   std::vector<bool>    *electrons_passSel;
   std::vector<bool>    *electrons_isVTLH;
   std::vector<bool>    *electrons_isVHL;
   std::vector<bool>    *electrons_isWH;
   std::vector<bool>    *electrons_isZH;
   std::vector<float>   *electrons_ptcone20;
   std::vector<float>   *electrons_etcone30;
   Int_t           nmc;
   std::vector<float>   *mc_E;
   std::vector<float>   *mc_px;
   std::vector<float>   *mc_py;
   std::vector<float>   *mc_pz;
   std::vector<float>   *mc_pvz;
   std::vector<int>     *mc_ind;
   std::vector<int>     *mc_pdg;
   std::vector<int>     *mc_status;
   std::vector<int>     *mc_barcode;
   Int_t           eve_num;
   Int_t           eve_run;
   Int_t           eve_mc_num;
   Float_t         eve_pvz;
   Int_t           eve_nv3;
   Int_t           eve_mc_chan;
   Float_t         eve_mc_w;
   Bool_t          eve_isMC;
   Float_t         met_px;
   Float_t         met_py;
   Float_t         met_pt;
   Float_t         met_phi;
   Float_t         met_sumET;
   Float_t         trackmet_px;
   Float_t         trackmet_py;
   Float_t         trackmet_pt;
   Float_t         trackmet_phi;
   Float_t         trackmet_sumET;

   // List of branches
   TBranch        *b_njets;   //!
   TBranch        *b_jets_E;   //!
   TBranch        *b_jets_pt;   //!
   TBranch        *b_jets_phi;   //!
   TBranch        *b_jets_eta;   //!
   TBranch        *b_jets_ind;   //!
   TBranch        *b_jets_MV1;   //!
   TBranch        *b_jets_truth;   //!
   TBranch        *b_jets_isVetoJet;   //!
   TBranch        *b_jets_isSignal;   //!
   TBranch        *b_nfatJets;   //!
   TBranch        *b_fatJets_E;   //!
   TBranch        *b_fatJets_pt;   //!
   TBranch        *b_fatJets_phi;   //!
   TBranch        *b_fatJets_eta;   //!
   TBranch        *b_fatJets_ind;   //!
   TBranch        *b_fatJets_jvf;   //!
   TBranch        *b_fatJets_tau21;   //!
   TBranch        *b_fatJets_tau32;   //!
   TBranch        *b_nmuons;   //!
   TBranch        *b_muons_E;   //!
   TBranch        *b_muons_pt;   //!
   TBranch        *b_muons_phi;   //!
   TBranch        *b_muons_eta;   //!
   TBranch        *b_muons_ind;   //!
   TBranch        *b_muons_ptcone20;   //!
   TBranch        *b_muons_etcone30;   //!
   TBranch        *b_muons_type;   //!
   TBranch        *b_muons_isVHL;   //!
   TBranch        *b_muons_isZH;   //!
   TBranch        *b_muons_isWH;   //!
   TBranch        *b_ntaus;   //!
   TBranch        *b_taus_E;   //!
   TBranch        *b_taus_pt;   //!
   TBranch        *b_taus_phi;   //!
   TBranch        *b_taus_eta;   //!
   TBranch        *b_taus_ind;   //!
   TBranch        *b_nelectrons;   //!
   TBranch        *b_electrons_E;   //!
   TBranch        *b_electrons_pt;   //!
   TBranch        *b_electrons_phi;   //!
   TBranch        *b_electrons_eta;   //!
   TBranch        *b_electrons_ind;   //!
   TBranch        *b_electrons_passSel;   //!
   TBranch        *b_electrons_isVTLH;   //!
   TBranch        *b_electrons_isVHL;   //!
   TBranch        *b_electrons_isWH;   //!
   TBranch        *b_electrons_isZH;   //!
   TBranch        *b_electrons_ptcone20;   //!
   TBranch        *b_electrons_etcone30;   //!
   TBranch        *b_nmc;   //!
   TBranch        *b_mc_E;   //!
   TBranch        *b_mc_px;   //!
   TBranch        *b_mc_py;   //!
   TBranch        *b_mc_pz;   //!
   TBranch        *b_mc_pvz;   //!
   TBranch        *b_mc_ind;   //!
   TBranch        *b_mc_pdg;   //!
   TBranch        *b_mc_status;   //!
   TBranch        *b_mc_barcode;   //!
   TBranch        *b_eve_num;   //!
   TBranch        *b_eve_run;   //!
   TBranch        *b_eve_mc_num;   //!
   TBranch        *b_eve_pvz;   //!
   TBranch        *b_eve_nv3;   //!
   TBranch        *b_eve_mc_chan;   //!
   TBranch        *b_eve_mc_w;   //!
   TBranch        *b_eve_isMC;   //!
   TBranch        *b_met_px;   //!
   TBranch        *b_met_py;   //!
   TBranch        *b_met_pt;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_met_sumET;   //!
   TBranch        *b_trackmet_px;   //!
   TBranch        *b_trackmet_py;   //!
   TBranch        *b_trackmet_pt;   //!
   TBranch        *b_trackmet_phi;   //!
   TBranch        *b_trackmet_sumET;   //!

   VHNtuple(TTree *tree=0);
   virtual ~VHNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef VHNtuple_cxx
VHNtuple::VHNtuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ttbar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ttbar.root");
      }
      f->GetObject("tupletest",tree);

   }
   Init(tree);
}

VHNtuple::~VHNtuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t VHNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t VHNtuple::LoadTree(Long64_t entry)
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

void VHNtuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jets_E = 0;
   jets_pt = 0;
   jets_phi = 0;
   jets_eta = 0;
   jets_ind = 0;
   jets_MV1 = 0;
   jets_truth = 0;
   jets_isVetoJet = 0;
   jets_isSignal = 0;
   fatJets_E = 0;
   fatJets_pt = 0;
   fatJets_phi = 0;
   fatJets_eta = 0;
   fatJets_ind = 0;
   fatJets_jvf = 0;
   fatJets_tau21 = 0;
   fatJets_tau32 = 0;
   muons_E = 0;
   muons_pt = 0;
   muons_phi = 0;
   muons_eta = 0;
   muons_ind = 0;
   muons_ptcone20 = 0;
   muons_etcone30 = 0;
   muons_type = 0;
   muons_isVHL = 0;
   muons_isZH = 0;
   muons_isWH = 0;
   taus_E = 0;
   taus_pt = 0;
   taus_phi = 0;
   taus_eta = 0;
   taus_ind = 0;
   electrons_E = 0;
   electrons_pt = 0;
   electrons_phi = 0;
   electrons_eta = 0;
   electrons_ind = 0;
   electrons_passSel = 0;
   electrons_isVTLH = 0;
   electrons_isVHL = 0;
   electrons_isWH = 0;
   electrons_isZH = 0;
   electrons_ptcone20 = 0;
   electrons_etcone30 = 0;
   mc_E = 0;
   mc_px = 0;
   mc_py = 0;
   mc_pz = 0;
   mc_pvz = 0;
   mc_ind = 0;
   mc_pdg = 0;
   mc_status = 0;
   mc_barcode = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("jets_E", &jets_E, &b_jets_E);
   fChain->SetBranchAddress("jets_pt", &jets_pt, &b_jets_pt);
   fChain->SetBranchAddress("jets_phi", &jets_phi, &b_jets_phi);
   fChain->SetBranchAddress("jets_eta", &jets_eta, &b_jets_eta);
   fChain->SetBranchAddress("jets_ind", &jets_ind, &b_jets_ind);
   fChain->SetBranchAddress("jets_MV1", &jets_MV1, &b_jets_MV1);
   fChain->SetBranchAddress("jets_truth", &jets_truth, &b_jets_truth);
   fChain->SetBranchAddress("jets_isVetoJet", &jets_isVetoJet, &b_jets_isVetoJet);
   fChain->SetBranchAddress("jets_isSignal", &jets_isSignal, &b_jets_isSignal);
   fChain->SetBranchAddress("nfatJets", &nfatJets, &b_nfatJets);
   fChain->SetBranchAddress("fatJets_E", &fatJets_E, &b_fatJets_E);
   fChain->SetBranchAddress("fatJets_pt", &fatJets_pt, &b_fatJets_pt);
   fChain->SetBranchAddress("fatJets_phi", &fatJets_phi, &b_fatJets_phi);
   fChain->SetBranchAddress("fatJets_eta", &fatJets_eta, &b_fatJets_eta);
   fChain->SetBranchAddress("fatJets_ind", &fatJets_ind, &b_fatJets_ind);
   fChain->SetBranchAddress("fatJets_jvf", &fatJets_jvf, &b_fatJets_jvf);
   fChain->SetBranchAddress("fatJets_tau21", &fatJets_tau21, &b_fatJets_tau21);
   fChain->SetBranchAddress("fatJets_tau32", &fatJets_tau32, &b_fatJets_tau32);
   fChain->SetBranchAddress("nmuons", &nmuons, &b_nmuons);
   fChain->SetBranchAddress("muons_E", &muons_E, &b_muons_E);
   fChain->SetBranchAddress("muons_pt", &muons_pt, &b_muons_pt);
   fChain->SetBranchAddress("muons_phi", &muons_phi, &b_muons_phi);
   fChain->SetBranchAddress("muons_eta", &muons_eta, &b_muons_eta);
   fChain->SetBranchAddress("muons_ind", &muons_ind, &b_muons_ind);
   fChain->SetBranchAddress("muons_ptcone20", &muons_ptcone20, &b_muons_ptcone20);
   fChain->SetBranchAddress("muons_etcone30", &muons_etcone30, &b_muons_etcone30);
   fChain->SetBranchAddress("muons_type", &muons_type, &b_muons_type);
   fChain->SetBranchAddress("muons_isVHL", &muons_isVHL, &b_muons_isVHL);
   fChain->SetBranchAddress("muons_isZH", &muons_isZH, &b_muons_isZH);
   fChain->SetBranchAddress("muons_isWH", &muons_isWH, &b_muons_isWH);
   fChain->SetBranchAddress("ntaus", &ntaus, &b_ntaus);
   fChain->SetBranchAddress("taus_E", &taus_E, &b_taus_E);
   fChain->SetBranchAddress("taus_pt", &taus_pt, &b_taus_pt);
   fChain->SetBranchAddress("taus_phi", &taus_phi, &b_taus_phi);
   fChain->SetBranchAddress("taus_eta", &taus_eta, &b_taus_eta);
   fChain->SetBranchAddress("taus_ind", &taus_ind, &b_taus_ind);
   fChain->SetBranchAddress("nelectrons", &nelectrons, &b_nelectrons);
   fChain->SetBranchAddress("electrons_E", &electrons_E, &b_electrons_E);
   fChain->SetBranchAddress("electrons_pt", &electrons_pt, &b_electrons_pt);
   fChain->SetBranchAddress("electrons_phi", &electrons_phi, &b_electrons_phi);
   fChain->SetBranchAddress("electrons_eta", &electrons_eta, &b_electrons_eta);
   fChain->SetBranchAddress("electrons_ind", &electrons_ind, &b_electrons_ind);
   fChain->SetBranchAddress("electrons_passSel", &electrons_passSel, &b_electrons_passSel);
   fChain->SetBranchAddress("electrons_isVTLH", &electrons_isVTLH, &b_electrons_isVTLH);
   fChain->SetBranchAddress("electrons_isVHL", &electrons_isVHL, &b_electrons_isVHL);
   fChain->SetBranchAddress("electrons_isWH", &electrons_isWH, &b_electrons_isWH);
   fChain->SetBranchAddress("electrons_isZH", &electrons_isZH, &b_electrons_isZH);
   fChain->SetBranchAddress("electrons_ptcone20", &electrons_ptcone20, &b_electrons_ptcone20);
   fChain->SetBranchAddress("electrons_etcone30", &electrons_etcone30, &b_electrons_etcone30);
   fChain->SetBranchAddress("nmc", &nmc, &b_nmc);
   fChain->SetBranchAddress("mc_E", &mc_E, &b_mc_E);
   fChain->SetBranchAddress("mc_px", &mc_px, &b_mc_px);
   fChain->SetBranchAddress("mc_py", &mc_py, &b_mc_py);
   fChain->SetBranchAddress("mc_pz", &mc_pz, &b_mc_pz);
   fChain->SetBranchAddress("mc_pvz", &mc_pvz, &b_mc_pvz);
   fChain->SetBranchAddress("mc_ind", &mc_ind, &b_mc_ind);
   fChain->SetBranchAddress("mc_pdg", &mc_pdg, &b_mc_pdg);
   fChain->SetBranchAddress("mc_status", &mc_status, &b_mc_status);
   fChain->SetBranchAddress("mc_barcode", &mc_barcode, &b_mc_barcode);
   fChain->SetBranchAddress("eve_num", &eve_num, &b_eve_num);
   fChain->SetBranchAddress("eve_run", &eve_run, &b_eve_run);
   fChain->SetBranchAddress("eve_mc_num", &eve_mc_num, &b_eve_mc_num);
   fChain->SetBranchAddress("eve_pvz", &eve_pvz, &b_eve_pvz);
   fChain->SetBranchAddress("eve_nv3", &eve_nv3, &b_eve_nv3);
   fChain->SetBranchAddress("eve_mc_chan", &eve_mc_chan, &b_eve_mc_chan);
   fChain->SetBranchAddress("eve_mc_w", &eve_mc_w, &b_eve_mc_w);
   fChain->SetBranchAddress("eve_isMC", &eve_isMC, &b_eve_isMC);
   fChain->SetBranchAddress("met_px", &met_px, &b_met_px);
   fChain->SetBranchAddress("met_py", &met_py, &b_met_py);
   fChain->SetBranchAddress("met_pt", &met_pt, &b_met_pt);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("met_sumET", &met_sumET, &b_met_sumET);
   fChain->SetBranchAddress("trackmet_px", &trackmet_px, &b_trackmet_px);
   fChain->SetBranchAddress("trackmet_py", &trackmet_py, &b_trackmet_py);
   fChain->SetBranchAddress("trackmet_pt", &trackmet_pt, &b_trackmet_pt);
   fChain->SetBranchAddress("trackmet_phi", &trackmet_phi, &b_trackmet_phi);
   fChain->SetBranchAddress("trackmet_sumET", &trackmet_sumET, &b_trackmet_sumET);
   Notify();
}

Bool_t VHNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void VHNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t VHNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef VHNtuple_cxx
