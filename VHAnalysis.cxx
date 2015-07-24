#include "VHAnalysis.h"

#include <iostream>
#include <TVector2.h>
#include <vector>
#include <TMath.h>
#include <string>
#include <TLorentzVector.h>

VHAnalysis::VHAnalysis(TTree* tree, const std::string& outfname) :
  VHNtuple(tree),
  m_outfile(outfname, "recreate"),
  m_kinVariables(),
  m_btag()
{

  InitializeHistograms();

}

VHAnalysis::~VHAnalysis() {
  m_outfile->Close();
}

void VHAnalysis::InitializeHistograms() {


  m_nelectron_init = new TH1F( "m_nelectron_init", "m_nelectron_init;nb_electrons", 100, 0, 100);
  m_nelectron_aftercut = new TH1F( "m_nelectron_aftercut", "m_nelectron_aftercut;nb_electrons", 100, 0,  100);

  m_nmuons_init = new TH1F( "m_nmuons_init", "m_nmuons_init;nb_muons", 100, 0, 100);
  m_nmuon_aftercut = new TH1F( "m_nmuon_aftercut", "m_nmuon_aftercut;nb_muons", 100, 0, 100);
  
  m_MET_init = new TH1F( "m_MET_init", "m_MET_init;MET", 100, 0, 300e3);
  m_MET_aftercut = new TH1F( "m_MET_aftercut", "m_MET_aftercut;MET", 100, 0, 300e3);
  
  m_MPT_init = new TH1F( "m_MPT_init", "m_MPT_init;MPT", 100, 0, 300e3);
  m_MPT_aftercut = new TH1F( "m_MPT_aftercut", "m_MPT_aftercut;MPT", 100, 0, 300e3);
  
  m_dphiMETMPT_init = new TH1F( "m_dphiMETMPT_init", "m_dphiMETMPT_init;DeltaPhiMETMPT", 100, 0, 6.5);
  m_dphiMETMPT_aftercut = new TH1F( "m_dphiMETMPT_aftercut", "m_dphiMETMPT_aftercut;DeltaPhiMETMPT", 100, 0, 6.5);
  
  m_SigJets_init = new TH1F( "m_SigJets_init", "m_SigJets_init;nb_Jets", 100, 0, 10);
  m_SigJets_aftercut = new TH1F( "m_SigJets_aftercut", "m_SigJets_aftercut;nb_Jets", 100, 0, 10);
  
  m_SigJet1_pt_init = new TH1F( "m_SigJet1_pt_init", "m_SigJet1_pt_init;pt_Signal1", 100, 0, 300e3);
  m_SigJet1_pt_aftercut = new TH1F( "m_SigJet1_pt_aftercut", "m_SigJet1_pt_aftercut;pt_Signal1", 100, 0, 300e3);
  
  m_SigVetoJets_init = new TH1F( "m_SigVetoJets_init", "m_SigVetoJets_init;nb_Jets", 100, 0, 10);
  m_SigVetoJets_aftercut = new TH1F( "m_SigVetoJets_aftercut", "m_SigVetoJets_aftercut;nb_Jets", 100, 0, 10);

  m_sumpt12_init = new TH1F( "m_sumpt12_init", "m_sumpt12_init;sum_pt1pt2", 100, 0, 500e3);
  m_sumpt12_aftercut = new TH1F( "m_sumpt12_aftercut", "m_sumpt12_aftercut;sum_pt1pt2", 100, 0, 500e3);

  m_sumpt123_init = new TH1F( "m_sumpt123_init", "m_sumpt123_init;sum_pt1pt2pt3", 100, 0, 500e3);
  m_sumpt123_aftercut = new TH1F( "m_sumpt123_aftercut", "m_sumpt123_aftercut;sum_pt1pt2pt3", 100, 0, 500e3);

  m_dphiMETdijet_init = new TH1F( "m_dphiMETdijet_init", "m_dphiMETdijet_init;DeltaPhiMETdijet", 100, 0, 6.5);
  m_dphiMETdijet_aftercut = new TH1F( "m_dphiMETdijet_aftercut", "m_dphiMETdijet_aftercut;DeltaPhiMETdijet", 100, 0, 6.5);

  m_dRSigJet1SigJet2_init = new TH1F( "m_dRSigJet1SigJet2_init", "m_dRSigJet1SigJet2_init;DeltaRsig1sig2", 100, 0, 4.5);
  m_dRSigJet1SigJet2_aftercut = new TH1F( "m_dRSigJet1SigJet2_aftercut", "m_dRSigJet1SigJet2_aftercut;DeltaRsig1sig2", 100, 0, 4.5);

  m_massdijet_init = new TH1F( "m_massdijet_init", "m_massdijet_init;massDijet", 100, 0, 250e3);
  m_massdijet_aftercut = new TH1F( "m_massdijet_aftercut", "m_massdijet_aftercut;massDijet", 100, 0, 250e3);

  m_cutflow = new TH1F("cutflow", "cutflow", 20, -0.5, 19.5);
  m_cutflow->SetDirectory(0);

  m_kinVariables.addHisto("jet1pT;p_{T} [GeV]", {100, 0, 500});
  

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

  PlotVariables(evt, "pretag_");

  DoBTagging(evt);

  PlotVariables(evt, "btag_");
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
    evt.j3 = vetoJets[0];
  }
  //__________________________


  // let the EvtInfo fill itself the jet TLorentzVectors
  evt.FillTLVs(jets_E, jets_pt, jets_phi, jets_eta, jets_truth);
  evt.met.SetPtEtaPhiM(met_pt/1.e3, 0, met_phi, 0);
  //______________________________________________________________


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

void VHAnalysis::DoBTagging(EvtInfo& evt) {
  float w1 = m_btag.getJetWeight(evt.jet1.Pt(), evt.jet1.Eta(), evt.type1);
  float w2 = m_btag.getJetWeight(evt.jet2.Pt(), evt.jet2.Eta(), evt.type2);
  evt.btag_weight = w1*w2;
}

void VHAnalysis::PlotVariables(EvtInfo& evt, const std::string& prefix) {
  m_kinVariables.setCut(prefix);
  FillPlots(evt);
  m_kinVariables.setCut(prefix+evt.kin_prefix());
  FillPlots(evt);
}

void VHAnalysis::FillPlots(EvtInfo& evt) {
  m_kinVariables.fillCurrent("jet1pT", evt.jet1.Pt(), evt.total_weight());

}

void VHAnalysis::WriteHistos() {
  std::cout << "Writing histograms to the output file" << std::endl;
  m_outfile->cd();

  m_nelectron_init->Write();
  m_nelectron_aftercut->Write();
  m_nmuons_init->Write();
  m_nmuon_aftercut->Write();
  m_MET_init->Write();
  m_MET_aftercut->Write();
  m_MPT_init->Write();
  m_MPT_aftercut->Write();
  m_dphiMETMPT_init->Write();
  m_dphiMETMPT_aftercut->Write();
  m_SigJets_init->Write();
  m_SigJets_aftercut->Write();
  m_SigJet1_pt_init->Write();
  m_SigJet1_pt_aftercut->Write();
  m_SigVetoJets_init->Write();
  m_SigVetoJets_aftercut->Write();
  m_sumpt12_init->Write();
  m_sumpt12_aftercut->Write();
  m_sumpt123_init->Write();
  m_sumpt123_aftercut->Write();
  m_dphiMETdijet_init->Write();
  m_dphiMETdijet_aftercut->Write();
  m_dRSigJet1SigJet2_init->Write();
  m_dRSigJet1SigJet2_aftercut->Write();
  m_massdijet_init->Write();
  m_massdijet_aftercut->Write();

  m_cutflow->Write();

  m_kinVariables.saveHists(&(*m_outfile));
}

