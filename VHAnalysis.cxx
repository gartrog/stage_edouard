#include "VHAnalysis.h"

#include <iostream>
#include <TVector2.h>
#include <vector>
#include <TMath.h>
#include <string>

VHAnalysis::VHAnalysis(TTree* tree, const std::string& outfname) :
  VHNtuple(tree),
  m_outfile(outfname, "recreate")
{

  InitializeHistograms();

}

VHAnalysis::~VHAnalysis() {
  m_outfile->Close();
}

void VHAnalysis::InitializeHistograms() {

  m_cutflow = new TH1F("cutflow", "cutflow", 20, -0.5, 19.5);
  m_cutflow->SetDirectory(0);

}

void VHAnalysis::Loop() {
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%10000 == 0) {
        std::cout << "Processing entry: " << jentry << std::endl;
      }
      ProcessEntry(jentry);
      // if (Cut(ientry) < 0) continue;
   }
   std::cout << "Done processing entries" << std::endl;
}

void VHAnalysis::ProcessEntry(Long64_t ientry) {
  EvtInfo evt;

  if(eve_mc_chan == 110351) { evt.mc_weight = 15.91425781; }
  if(eve_mc_chan == 110401) { evt.mc_weight = 0.1913586573; }

  bool res = ApplySelection(evt);

  if(!res) { return; }

}

bool VHAnalysis::ApplySelection(EvtInfo& evt) {

  m_cutflow->Fill(0., evt.mc_weight);

  int nLooseElectrons = 0;
  for(bool b : *electrons_isVHL) {
    if(b) { nelectrons++; }
  }
  if(nLooseElectrons > 0) { return false; }

  m_cutflow->Fill(1, evt.mc_weight);

  int nLooseMuons = 0;
  for(bool b : *muons_isVHL) {
    if(b) { nmuons++; }
  }
  if(nLooseMuons > 0) { return false; }

  m_cutflow->Fill(2, evt.mc_weight);

  if(met_pt < 120e3) { return false; }

  m_cutflow->Fill(3, evt.mc_weight);

  if(trackmet_pt < 30e3) { return false; }

  m_cutflow->Fill(4, evt.mc_weight);

  float dphiMETMPT = fabs(TVector2::Phi_mpi_pi(met_phi-trackmet_phi));
  if(dphiMETMPT > TMath::Pi()/2) { return false; }

  m_cutflow->Fill(5, evt.mc_weight);

  std::vector<int> sigJets;
  std::vector<int> vetoJets;
  for(int i=0; i<njets; i++) {
    if(jets_isSignal->at(i)) {
      sigJets.push_back(i);
    }
    else if(jets_isVetoJet->at(i)) {
      vetoJets.push_back(i);
    }
  }

  if(sigJets.size() < 2) { return false; }

  m_cutflow->Fill(6, evt.mc_weight);

  // order in pt
  if(jets_pt->at(sigJets[0]) < jets_pt->at(sigJets[1])) {
    int tmp = sigJets[0];
    sigJets[0] = sigJets[1];
    sigJets[1] = tmp;
  }

  if(jets_pt->at(sigJets[0]) < 45e3) { return false; }

  m_cutflow->Fill(7, evt.mc_weight);

  if(sigJets.size() + vetoJets.size() > 3) { return false; }

  m_cutflow->Fill(8, evt.mc_weight);

  // assign jets
  evt.j1 = sigJets[0];
  evt.j2 = sigJets[1];
  if(sigJets.size() == 3) {
    evt.j3 = sigJets[2];
  }
  if(vetoJets.size() > 0) {
    evt.j3 = vetoJets[1];
  }

  // let the EvtInfo fill itself the jet TLorentzVectors
  evt.FillTLVs(jets_E, jets_pt, jets_phi, jets_eta);
  evt.met.SetPtEtaPhiM(met_pt/1.e3, 0, met_phi, 0);

  bool passSumPt = true;
  if(evt.has3j()) {
    if(jets_pt->at(evt.j1) + jets_pt->at(evt.j2) + jets_pt->at(evt.j3) < 150e3) {
      return false;
    }
  }
  else {
    if(jets_pt->at(evt.j1) + jets_pt->at(evt.j2) < 120e3) {
      return false;
    }
  }

  m_cutflow->Fill(9, evt.mc_weight);

  if( fabs(evt.met.DeltaPhi(evt.dijet)) < 140 * TMath::Pi()/180. ) { return false; }

  m_cutflow->Fill(10, evt.mc_weight);

  if(evt.jet1.DeltaR(evt.jet2) > 2) { return false; }

  m_cutflow->Fill(11, evt.mc_weight);

  if(evt.dijet.M() < 90 || evt.dijet.M() > 150) { return false; }

  m_cutflow->Fill(12, evt.mc_weight);

  return true;
}

void VHAnalysis::WriteHistos() {
  std::cout << "Writing histograms to the output file" << std::endl;
  m_outfile->cd();

  m_cutflow->Write();
}

