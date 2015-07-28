#ifndef VHAnalysis_h
#define VHAnalysis_h

#include "VHNtuple.h"
#include "file.h"
#include <TH1F.h>
#include <TString.h>
#include <string>
#include "histos.h"
#include "BTagging.h"
#include "EvtInfo.h"

class VHAnalysis : public VHNtuple {

  public:
    VHAnalysis(TTree* tree, const std::string& outfname);
    VHAnalysis() = delete;
    virtual ~VHAnalysis();

    void Loop();
    void WriteHistos();


  private:
    File m_outfile;

    //List Historgram
    Histos m_kinVariables;
    Histos m_truthLeptons;
    Histos m_truthCompo;
    //_____________________

    BTagging m_btag;

    //Histogram 
    TH1F* m_cutflow;

    TH1F* m_nelectron_init;
    TH1F* m_nelectron_aftercut;
    
    TH1F* m_nmuons_init;
    TH1F* m_nmuons_aftercut;
    
    TH1F* m_MET_init;
    TH1F* m_MET_aftercut;
    
    TH1F* m_MPT_init;
    TH1F* m_MPT_aftercut;
    
    TH1F* m_dphiMETMPT_init;
    TH1F* m_dphiMETMPT_aftercut;
    
    TH1F* m_nSigJets_init;
    TH1F* m_nSigJets_aftercut;
    
    TH1F* m_SigJet1_pt_init;
    TH1F* m_SigJet1_pt_aftercut;
    
    TH1F* m_nSigVetoJets_init;
    TH1F* m_nSigVetoJets_aftercut;
    
    TH1F* m_sumpt12_init;
    TH1F* m_sumpt12_aftercut;
    
    TH1F* m_sumpt123_init;
    TH1F* m_sumpt123_aftercut;
    
    TH1F* m_dphiMETdijet_init;
    TH1F* m_dphiMETdijet_aftercut;
    
    TH1F* m_dRSigJet1SigJet2_init;
    TH1F* m_dRSigJet1SigJet2_aftercut;
    
    TH1F* m_massdijet_init;
    TH1F* m_massdijet_aftercut;
    //____________________________________

    //Histo Comparaison bJet / bQuark
    TH1F* m_bquark_pt;
    TH1F* m_bquark_eta;
    TH1F* m_bquark_phi;
    TH1F* m_DeltaR_bQuarkbJet;
    TH1F* m_DeltaR_bQuarkSecondJet;
    TH1F* m_rapprtPT_bJetbQuarkMATCH;
    TH1F* m_DeltaR_bQuarkThirdJet;
    //_____________________________________


    void InitializeHistograms();
    void ProcessEntry(Long64_t ientry);
    bool ApplySelection(EvtInfo& evt);
    void PlotVariables(EvtInfo& evt, const std::string& prefix);
    void FillPlots(EvtInfo& evt);
    void DoBTagging(EvtInfo& evt);

    void StudyMCLeptons(EvtInfo& evt);
    void StudyJetQuark(EvtInfo& evt);

};

#endif
