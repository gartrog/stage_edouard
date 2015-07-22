#ifndef VHAnalysis_h
#define VHAnalysis_h

#include "VHNtuple.h"
#include "file.h"
#include <TH1F.h>
#include <TString.h>
#include <string>
#include <TLorentzVector.h>

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

  float total_weight() { return mc_weight*btag_weight; }
  bool has3j() { return j3!=-1; }

  EvtInfo() :
    mc_weight(1), btag_weight(1),
    j1(-1), j2(-1), j3(-1),
    jet1(), jet2(), jet3(), dijet(),
    met()
  {}

  void FillTLVs(std::vector<float>* E, std::vector<float>* pt, std::vector<float>* phi,
                std::vector<float>* eta) {
    jet1.SetPtEtaPhiE(pt->at(j1)/1.e3, eta->at(j1), phi->at(j1), E->at(j1));
    jet2.SetPtEtaPhiE(pt->at(j2)/1.e3, eta->at(j2), phi->at(j2), E->at(j2));
    if(has3j()) {
      jet3.SetPtEtaPhiE(pt->at(j3)/1.e3, eta->at(j3), phi->at(j3), E->at(j3));
    }
    dijet = jet1+jet2;
  }
};

class VHAnalysis : public VHNtuple {

  public:
    VHAnalysis(TTree* tree, const std::string& outfname);
    VHAnalysis() = delete;
    virtual ~VHAnalysis();

    File m_outfile;

    void InitializeHistograms();

    void Loop();
    void ProcessEntry(Long64_t ientry);
    bool ApplySelection(EvtInfo& evt);

    void WriteHistos();

    TH1F* m_cutflow;

};

#endif
