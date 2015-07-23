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

    Histos m_kinVariables;

    BTagging m_btag;

    TH1F* m_cutflow;

    void InitializeHistograms();
    void ProcessEntry(Long64_t ientry);
    bool ApplySelection(EvtInfo& evt);
    void PlotVariables(EvtInfo& evt, const std::string& prefix);
    void FillPlots(EvtInfo& evt);
    void DoBTagging(EvtInfo& evt);

};

#endif
