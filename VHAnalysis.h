#ifndef VHAnalysis_h
#define VHAnalysis_h

#include "VHNtuple.h"
#include "file.h"
#include <TH1F.h>
#include <TString.h>
#include <string>
#include <TLorentzVector.h>
#include "histos.h"
#include "BTagging.h"
#include <sstream>

struct EvtInfo {
  float mc_weight;
  float btag_weight;
  int j1;
  int j2;
  int j3;
  TLorentzVector jet1;
  TLorentzVector jet2;
  TLorentzVector jet3;
  TLorentzVector dijet;
  TLorentzVector met;
  int type1;
  int type2;
  int type3;

  float total_weight() const { return mc_weight*btag_weight; }
  bool has3j() const { return j3!=-1; }

  std::string kin_prefix() const {
    std::stringstream ss;
    ss << "nJet";
    if(has3j()) { ss << "3"; }
    else { ss << "2"; }
    ss << "MET";
    if(met.Pt() < 160) { ss << "0"; }
    else if(met.Pt() < 200) { ss << "1"; }
    else if(met.Pt() < 300) { ss << "2"; }
    else { ss << "3"; }
    return ss.str();
  }

  EvtInfo() :
    mc_weight(1), btag_weight(1),
    j1(-1), j2(-1), j3(-1),
    jet1(), jet2(), jet3(), dijet(),
    met(), type1(-1), type2(-1), type3(-1)
  {}

  void FillTLVs(std::vector<float>* E, std::vector<float>* pt, std::vector<float>* phi,
                std::vector<float>* eta, std::vector<int>* truth) {
    // also fill jet flavour information
    jet1.SetPtEtaPhiE(pt->at(j1)/1.e3, eta->at(j1), phi->at(j1), E->at(j1)/1.e3);
    type1 = truth->at(j1);
    jet2.SetPtEtaPhiE(pt->at(j2)/1.e3, eta->at(j2), phi->at(j2), E->at(j2)/1.e3);
    type2 = truth->at(j2);
    if(has3j()) {
      jet3.SetPtEtaPhiE(pt->at(j3)/1.e3, eta->at(j3), phi->at(j3), E->at(j3)/1.e3);
      type3 = truth->at(j3);
    }
    dijet = jet1+jet2;
  }
};

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
