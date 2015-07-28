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
  m_truthLeptons(),
  m_truthCompo(),
  m_btag()
{

  InitializeHistograms();

}

VHAnalysis::~VHAnalysis() {
  m_outfile->Close();
}

void VHAnalysis::InitializeHistograms() {

  //Selection Cut Histogramm
  m_nelectron_init = new TH1F( "m_nelectron_init", "m_nelectron_init;nb_electrons", 100, 0, 1);
  m_nelectron_aftercut = new TH1F( "m_nelectron_aftercut", "m_nelectron_aftercut;nb_electrons", 100, 0,  1);

  m_nmuons_init = new TH1F( "m_nmuons_init", "m_nmuons_init;nb_muons", 100, 0, 100);
  m_nmuons_aftercut = new TH1F( "m_nmuons_aftercut", "m_nmuons_aftercut;nb_muons", 100, 0, 100);

  m_MET_init = new TH1F( "m_MET_init", "m_MET_init;MET", 100, 0, 300e3);
  m_MET_aftercut = new TH1F( "m_MET_aftercut", "m_MET_aftercut;MET", 100, 0, 300e3);

  m_MPT_init = new TH1F( "m_MPT_init", "m_MPT_init;MPT", 100, 0, 300e3);
  m_MPT_aftercut = new TH1F( "m_MPT_aftercut", "m_MPT_aftercut;MPT", 100, 0, 300e3);

  m_dphiMETMPT_init = new TH1F( "m_dphiMETMPT_init", "m_dphiMETMPT_init;DeltaPhiMETMPT", 100, 0, 4);
  m_dphiMETMPT_aftercut = new TH1F( "m_dphiMETMPT_aftercut", "m_dphiMETMPT_aftercut;DeltaPhiMETMPT", 100, 0, 4);

  m_nSigJets_init = new TH1F( "m_nSigJets_init", "m_nnSigJets_init;nb_Jets", 10, 0, 10);
  m_nSigJets_aftercut = new TH1F( "m_nSigJets_aftercut", "m_nSigJets_aftercut;nb_Jets", 10, 0, 10);

  m_SigJet1_pt_init = new TH1F( "m_SigJet1_pt_init", "m_SigJet1_pt_init;pt_Signal1", 10, 0, 300e3);
  m_SigJet1_pt_aftercut = new TH1F( "m_SigJet1_pt_aftercut", "m_SigJet1_pt_aftercut;pt_Signal1", 10, 0, 300e3);

  m_nSigVetoJets_init = new TH1F( "m_nSigVetoJets_init", "m_nSigVetoJets_init;nb_Jets", 10, 0, 10);
  m_nSigVetoJets_aftercut = new TH1F( "m_nSigVetoJets_aftercut", "m_nSigVetoJets_aftercut;nb_Jets", 10, 0, 10);

  m_sumpt12_init = new TH1F( "m_sumpt12_init", "m_sumpt12_init;sum_pt1pt2", 100, 0, 500e3);
  m_sumpt12_aftercut = new TH1F( "m_sumpt12_aftercut", "m_sumpt12_aftercut;sum_pt1pt2", 100, 0, 500e3);

  m_sumpt123_init = new TH1F( "m_sumpt123_init", "m_sumpt123_init;sum_pt1pt2pt3", 100, 0, 600e3);
  m_sumpt123_aftercut = new TH1F( "m_sumpt123_aftercut", "m_sumpt123_aftercut;sum_pt1pt2pt3", 100, 0, 600e3);

  m_dphiMETdijet_init = new TH1F( "m_dphiMETdijet_init", "m_dphiMETdijet_init;DeltaPhiMETdijet", 100, 0, 4);
  m_dphiMETdijet_aftercut = new TH1F( "m_dphiMETdijet_aftercut", "m_dphiMETdijet_aftercut;DeltaPhiMETdijet", 100, 0, 4);

  m_dRSigJet1SigJet2_init = new TH1F( "m_dRSigJet1SigJet2_init", "m_dRSigJet1SigJet2_init;DeltaRsig1sig2", 100, 0, 4.5);
  m_dRSigJet1SigJet2_aftercut = new TH1F( "m_dRSigJet1SigJet2_aftercut", "m_dRSigJet1SigJet2_aftercut;DeltaRsig1sig2", 100, 0, 4.5);

  m_massdijet_init = new TH1F( "m_massdijet_init", "m_massdijet_init;massDijet", 100, 0, 250);
  m_massdijet_aftercut = new TH1F( "m_massdijet_aftercut", "m_massdijet_aftercut;massDijet", 100, 0, 250);
  //______________________________________________________________________________________________________________________________________

  m_cutflow = new TH1F("cutflow", "cutflow", 20, -0.5, 19.5);
  m_cutflow->SetDirectory(0);

  //Histogramm list for categorizing 
  m_kinVariables.addHisto("jet1pT;p_{T} [GeV]", {100, 0, 300});
  m_kinVariables.addHisto("jet2pT;p_{T} [GeV]", {100, 0, 250});
  m_kinVariables.addHisto("jet3pT;p_{T} [GeV]", {100, 0, 200});
  m_kinVariables.addHisto("jet1eta;#eta", {100, 0, 3});
  m_kinVariables.addHisto("jet2eta;#eta", {100, 0, 3});
  m_kinVariables.addHisto("jet3eta;#eta", {100, 0, 3});
  m_kinVariables.addHisto("jet1truth;jet_{flavor}", {16, 0, 16});
  m_kinVariables.addHisto("jet2truth;jet_{flavor}", {16, 0, 16});
  m_kinVariables.addHisto("jet3truth;jet_{flavor}", {16, 0, 16});
  m_kinVariables.addHisto("massj1j2;M [MeV]", {100, 50, 200});
  m_kinVariables.addHisto("massj1j2j3;M [MeV]", {100, 50, 500});
  m_kinVariables.addHisto("DeltaRj1j2;#Delta R", {100, 0, 2.5});
  m_kinVariables.addHisto("DeltaPhij1j2;#Delta #phi [rad]", {100, 0, 2.5});
  m_kinVariables.addHisto("DeltaEtaj1j2;#Delta #eta", {100, 0, 2.5});
  m_kinVariables.addHisto("DeltaPhiMETdijet;#Delta #phi [rad]", {100, 2, 3.5});
  m_kinVariables.addHisto("MET;MET [GeV]", {100, 70, 300});
  m_kinVariables.addHisto("sumpt1pt2MET;#sum (p_{T_{12}} + MET) [GeV]", {100, 200, 600});
  m_kinVariables.addHisto("sumpt1pt2pt3MET;#sum (p_{T_{123}} + MET) [GeV]", {100, 250, 700});
  m_kinVariables.addHisto2D("jet1truthvsjet2truth;jet1_{flavor};jet2_{flavor}", {16, 0, 16}, {16, 0, 16});
  m_kinVariables.addHisto2D("jet1truthvsjet3truth;jet1_{flavor};jet3_{flavor}", {16, 0, 16}, {16, 0, 16});
  m_kinVariables.addHisto2D("jet2truthvsjet3truth;jet2_{flavor};jet3_{flavor}", {16, 0, 16}, {16, 0, 16});
  //________________________________________________________________________________________________________

  m_truthLeptons.addHisto("leppT;p_{T} [GeV]", {40, 0, 100});
  m_truthLeptons.addHisto("lepeta;#eta", {40, -5, 5});

  std::vector<std::string> categories {"FullHad", "e", "mu", "tau", "e-e", "e-mu", "mu-mu", "e-tau", "mu-tau", "tau-tau"};
  m_truthCompo.addHisto("compo;Categories", categories);

  //Histo Comparaison bJet / bQuark
  m_bquark_pt = new TH1F("m_bquark_pt", "m_bquark_pt", 100, 0, 300e3);
  m_bquark_eta = new TH1F("m_bquark_eta", "m_bquark_eta", 100, 0, 4);
  m_bquark_phi = new TH1F("m_bquark_phi", "m_bquark_phi", 100, 0, 4);
  m_DeltaR_bQuarkbJet = new TH1F("m_DeltaR_bQuarkbJet", "m_DeltaR_bQuarkbJet", 100, 0, 4);
  m_DeltaR_bQuarkSecondJet = new TH1F("m_DeltaR_bQuarkSecondJet", "m_DeltaR_bQuarkSecondJet", 100, 0, 4);
  m_rapprtPT_bJetbQuarkMATCH = new TH1F("m_rapprtPT_bJetbQuarkMATCH", "m_rapprtPT_bJetbQuarkMATCH", 100, 0, 4);
  m_DeltaR_bQuarkThirdJet = new TH1F("m_DeltaR_bQuarkThirdJet", "m_DeltaR_bQuarkThirdJet", 100, 0, 4);
}

void VHAnalysis::Loop() {
   if (fChain == 0) return;
   fChain->SetBranchStatus("*",0);  // disable all branches
   fChain->SetBranchStatus("jets*",1);
   fChain->SetBranchStatus("muons_isVHL*",1);
   fChain->SetBranchStatus("electrons_isVHL*",1);
   fChain->SetBranchStatus("n*",1);
   fChain->SetBranchStatus("mc*",1);
   fChain->SetBranchStatus("trackmet*",1);
   fChain->SetBranchStatus("met*",1);
   fChain->SetBranchStatus("eve_mc*",1);

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%100000 == 0) {
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

  StudyMCLeptons(evt);

  StudyJetQuark(evt);
}

bool VHAnalysis::ApplySelection(EvtInfo& evt) {

  m_cutflow->Fill(0., evt.mc_weight);

  int nLooseElectrons = 0;
  for(bool b : *electrons_isVHL) {
    if(b) { nelectrons++; }
  }
  m_nelectron_init->Fill(nelectrons);
  if(nLooseElectrons > 0) { return false; }
  m_nelectron_aftercut->Fill(nelectrons);

  m_cutflow->Fill(1, evt.mc_weight);

  int nLooseMuons = 0;
  for(bool b : *muons_isVHL) {
    if(b) { nmuons++; }
  }
  m_nmuons_init->Fill(nmuons);
  if(nLooseMuons > 0) { return false; }
  m_nmuons_aftercut->Fill(nmuons);

  m_cutflow->Fill(2, evt.mc_weight);

  m_MET_init->Fill(met_pt);
  if(met_pt < 120e3) { return false; }
  m_MET_aftercut->Fill(met_pt);

  m_cutflow->Fill(3, evt.mc_weight);

  m_MPT_init->Fill(trackmet_pt);
  if(trackmet_pt < 30e3) { return false; }
  m_MPT_aftercut->Fill(trackmet_pt);

  m_cutflow->Fill(4, evt.mc_weight);

  float dphiMETMPT = fabs(TVector2::Phi_mpi_pi(met_phi-trackmet_phi));
  m_dphiMETMPT_init->Fill(dphiMETMPT);
  if(dphiMETMPT > TMath::Pi()/2) { return false; }
  m_dphiMETMPT_aftercut->Fill(dphiMETMPT);

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
  m_nSigJets_init->Fill(sigJets.size() + vetoJets.size());
  if(sigJets.size() < 2) { return false; }
  m_nSigJets_aftercut->Fill(sigJets.size() + vetoJets.size());
  
  m_cutflow->Fill(6, evt.mc_weight);

  // order in pt
  if(jets_pt->at(sigJets[0]) < jets_pt->at(sigJets[1])) {
    int tmp = sigJets[0];
    sigJets[0] = sigJets[1];
    sigJets[1] = tmp;
  }

  m_SigJet1_pt_init->Fill(jets_pt->at(sigJets[0]));
  if(jets_pt->at(sigJets[0]) < 45e3) { return false; }
  m_SigJet1_pt_aftercut->Fill(jets_pt->at(sigJets[0]));

  m_cutflow->Fill(7, evt.mc_weight);

  m_nSigVetoJets_init->Fill(sigJets.size() + vetoJets.size());
  if(sigJets.size() + vetoJets.size() > 3) { return false; }
  m_nSigVetoJets_aftercut->Fill(sigJets.size() + vetoJets.size());

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
  evt.met.SetPtEtaPhiE(met_pt/1.e3, 0, met_phi, met_pt/1.e3);
  //______________________________________________________________


  bool passSumPt = true;
  if(evt.has3j()) {
    m_sumpt123_init->Fill(jets_pt->at(evt.j1) + jets_pt->at(evt.j2) + jets_pt->at(evt.j3));
    if(jets_pt->at(evt.j1) + jets_pt->at(evt.j2) + jets_pt->at(evt.j3) < 150e3) {
      return false;
    }
    m_sumpt123_aftercut->Fill(jets_pt->at(evt.j1) + jets_pt->at(evt.j2) + jets_pt->at(evt.j3));
  }
  else {
    m_sumpt12_init->Fill(jets_pt->at(evt.j1) + jets_pt->at(evt.j2));
    if(jets_pt->at(evt.j1) + jets_pt->at(evt.j2) < 120e3) {
      return false;
    }
    m_sumpt12_aftercut->Fill(jets_pt->at(evt.j1) + jets_pt->at(evt.j2));
  }

  m_cutflow->Fill(9, evt.mc_weight);

  m_dphiMETdijet_init->Fill(evt.met.DeltaPhi(evt.dijet));
  if( fabs(evt.met.DeltaPhi(evt.dijet)) < 140 * TMath::Pi()/180. ) { return false; }
  m_dphiMETdijet_aftercut->Fill(evt.met.DeltaPhi(evt.dijet));

  m_cutflow->Fill(10, evt.mc_weight);

  m_dRSigJet1SigJet2_init->Fill(evt.jet1.DeltaR(evt.jet2));
  if(evt.jet1.DeltaR(evt.jet2) > 2) { return false; }
  m_dRSigJet1SigJet2_aftercut->Fill(evt.jet1.DeltaR(evt.jet2));

  m_cutflow->Fill(11, evt.mc_weight);

  m_massdijet_init->Fill(evt.dijet.M());
  if(evt.dijet.M() < 90 || evt.dijet.M() > 150) { return false; }
  m_massdijet_aftercut->Fill(evt.dijet.M());

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

  TLorentzVector sum1;    // TLorentzVector for the sum of jet1pT, jet2pT and MET
  TLorentzVector sum2;    // TLorentzVector for the sum of jet1pT, jet2pT, jet3pT and MET


  m_kinVariables.fillCurrent("jet1pT", evt.jet1.Pt(), evt.total_weight());
  m_kinVariables.fillCurrent("jet2pT", evt.jet2.Pt(), evt.total_weight());
  m_kinVariables.fillCurrent("jet1eta", evt.jet1.Eta(), evt.total_weight());
  m_kinVariables.fillCurrent("jet2eta", evt.jet2.Eta(), evt.total_weight());
  m_kinVariables.fillCurrent("jet1truth", evt.type1, evt.total_weight());
  m_kinVariables.fillCurrent("jet2truth", evt.type2, evt.total_weight());
  m_kinVariables.fillCurrent("massj1j2", evt.dijet.M(), evt.total_weight());
  m_kinVariables.fillCurrent("DeltaRj1j2", evt.jet1.DeltaR(evt.jet2), evt.total_weight());
  m_kinVariables.fillCurrent("DeltaPhij1j2", evt.jet1.DeltaPhi(evt.jet2), evt.total_weight());
  m_kinVariables.fillCurrent("DeltaEtaj1j2", fabs(evt.jet1.Eta()-evt.jet2.Eta()), evt.total_weight());
  m_kinVariables.fillCurrent("DeltaPhiMETdijet", evt.met.DeltaPhi(evt.dijet), evt.total_weight());
  m_kinVariables.fillCurrent("MET", evt.met.Pt(), evt.total_weight());
  m_kinVariables.fillCurrent("sumpt1pt2MET", evt.jet1.Pt()+evt.jet2.Pt()+evt.met.Pt(), evt.total_weight());
  m_kinVariables.fillCurrent2D("jet1truthvsjet2truth", evt.type1, evt.type2, evt.total_weight());

  if(evt.has3j()){   
    m_kinVariables.fillCurrent("jet3pT", evt.jet3.Pt(), evt.total_weight());
    m_kinVariables.fillCurrent("jet3eta", evt.jet3.Eta(), evt.total_weight());
    m_kinVariables.fillCurrent("jet3truth", evt.type3, evt.total_weight());
    m_kinVariables.fillCurrent("massj1j2j3", evt.trijet.M(), evt.total_weight());
    m_kinVariables.fillCurrent("sumpt1pt2pt3MET", evt.jet1.Pt()+evt.jet2.Pt()+evt.jet3.Pt()+evt.met.Pt(), evt.total_weight());
    m_kinVariables.fillCurrent2D("jet1truthvsjet3truth", evt.type1, evt.type3, evt.total_weight());
    m_kinVariables.fillCurrent2D("jet2truthvsjet3truth", evt.type2, evt.type3, evt.total_weight());
  }

}
 
void VHAnalysis::WriteHistos() {
  std::cout << "Writing histograms to the output file" << std::endl;
  m_outfile->cd();

  m_nelectron_init->Write();
  m_nelectron_aftercut->Write();
  m_nmuons_init->Write();
  m_nmuons_aftercut->Write();
  m_MET_init->Write();
  m_MET_aftercut->Write();
  m_MPT_init->Write();
  m_MPT_aftercut->Write();
  m_dphiMETMPT_init->Write();
  m_dphiMETMPT_aftercut->Write();
  m_nSigJets_init->Write();
  m_nSigJets_aftercut->Write();
  m_SigJet1_pt_init->Write();
  m_SigJet1_pt_aftercut->Write();
  m_nSigVetoJets_init->Write();
  m_nSigVetoJets_aftercut->Write();
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
  m_truthLeptons.saveHists(&(*m_outfile));
  m_truthCompo.saveHists(&(*m_outfile));

  m_bquark_pt->Write();
  m_bquark_eta->Write();
  m_bquark_phi->Write();
  m_DeltaR_bQuarkbJet->Write();
  m_DeltaR_bQuarkSecondJet->Write();
  m_rapprtPT_bJetbQuarkMATCH->Write();
  m_DeltaR_bQuarkThirdJet->Write();

  m_outfile->Close();
}

void VHAnalysis::StudyMCLeptons(EvtInfo& evt) {
  TruthInfo truth;
  std::vector<int> pos {6, 7, 8, 9};
  std::vector<int> leps_pdgIds {11, 13, 15};

  for(auto p : pos) {
    int pdgid = abs(mc_pdg->at(p));
    for(auto id : leps_pdgIds) {
      if(pdgid == id) {
        truth.leps_types.push_back(pdgid);
        TLorentzVector tlv;
        tlv.SetPxPyPzE(mc_px->at(p)/1.e3, mc_py->at(p)/1.e3, mc_pz->at(p)/1.e3, mc_E->at(p)/1.e3);
        truth.leps.push_back(tlv);
      }
    }
  }

  for(unsigned int i = 0; i < truth.leps.size(); i++) {
    m_truthLeptons.setCut(truth.prefix(truth.leps_types.at(i)));
    m_truthLeptons.fillCurrent("leppT", truth.leps[i].Pt(), evt.total_weight());
    m_truthLeptons.fillCurrent("lepeta", truth.leps[i].Eta(), evt.total_weight());
  }

  m_truthCompo.fill("all_compo", truth.category(), evt.total_weight());
  m_truthCompo.fill(evt.kin_prefix()+"_compo", truth.category(), evt.total_weight());

}
  
void VHAnalysis::StudyJetQuark(EvtInfo& evt) {
  TLorentzVector bJet;    //the bJet 
  TLorentzVector ndJet;   //second jet (the more distant from the selected bquark)
  TLorentzVector rdJet;   //third jet (if there is one)
  TLorentzVector bquark1;  //candidats à etre bquark matché au bJet    
  TLorentzVector bquark2;  //candidats à etre bquark matché au bJet
  TLorentzVector bquark_match;    //bquark matché to the bJet
  TLorentzVector bquark;    //the other bquark

  bquark1.SetPxPyPzE(mc_px->at(3), mc_py->at(3), mc_pz->at(3), mc_E->at(3));
  bquark2.SetPxPyPzE(mc_px->at(5), mc_py->at(5), mc_pz->at(5), mc_E->at(5));

  if(evt.type1==5 and evt.type2==5) { return; }
  if(evt.type1!=5 and evt.type2!=5) { return; }

  if(evt.type1==5) { 
    bJet = evt.jet1; 
    ndJet = evt.jet2;
  }

  else {
    if(evt.type2==5) {
      bJet = evt.jet2;
      ndJet = evt.jet1;
    }
  }

  if(bJet.DeltaR(bquark1)>0.4 and bJet.DeltaR(bquark2)>0.4) { return; }

  if(bJet.DeltaR(bquark1) < bJet.DeltaR(bquark2)) {
    bquark_match = bquark1;
    bquark = bquark2;
  }

  else {
    if(bJet.DeltaR(bquark2) < bJet.DeltaR(bquark1)) {
      bquark_match = bquark2;
      bquark = bquark1;
    }
  }
 
  m_bquark_pt->Fill(bquark.Pt(), evt.total_weight());
  m_bquark_eta->Fill(bquark.Eta(), evt.total_weight());
  m_bquark_phi->Fill(bquark.Phi(), evt.total_weight());
  m_DeltaR_bQuarkbJet->Fill(bquark.DeltaR(bJet), evt.total_weight());
  m_DeltaR_bQuarkSecondJet->Fill(bquark.DeltaR(ndJet), evt.total_weight());
  m_rapprtPT_bJetbQuarkMATCH->Fill( (bJet.Pt())*1000/(bquark_match.Pt()) , evt.total_weight());

  if(evt.has3j()) { 
    rdJet = evt.jet3;
    m_DeltaR_bQuarkThirdJet->Fill(bquark.DeltaR(rdJet), evt.total_weight());
  }

}


