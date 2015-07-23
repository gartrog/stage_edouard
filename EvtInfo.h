#ifndef EvtInfo_h
#define EvtInfo_h

#include <sstream>
#include <TLorentzVector.h>
#include <vector>

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

struct TruthInfo {
  std::vector<TLorentzVector> leps;
  std::vector<int> leps_types;

  bool isSemiLep() { return (leps.size() == 1); }
  bool isDiLep() { return (leps.size() == 2); }
  bool isFullHad() { return (leps.size() == 0); }

  TruthInfo() :
    leps(), leps_types()
  {}

  std::string prefix() {
    if(isSemiLep()) { return "semiLep"; }
    else if(isDiLep()) { return "diLep"; }
    else { return "fullHad"; }
  }

  std::string prefix(int type) {
    std::stringstream res;
    res << prefix() << "_";
    if(type == 11) { res << "e"; }
    else if(type == 13) { res << "mu"; }
    else if(type == 15) { res << "tau"; }
    return res.str();
  }

  std::string category() {
    if(isFullHad()) { return "FullHad"; }
    if(isSemiLep()) {
      switch(leps_types[0]) {
      case 11:
        return "e";
      case 13:
        return "mu";
      case 15:
        return "tau";
      }
    }
    switch(leps_types[0]+leps_types[1]) {
      case 22:
        return "e-e";
      case 24:
        return "e-mu";
      case 28:
        return "mu-tau";
      case 30:
        return "tau-tau";
      case 26:
        if(leps_types[0] == 13) {
          return "mu-mu";
        }
        return "e-tau";
    }
  }
};

#endif
