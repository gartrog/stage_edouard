#include "BTagging.h"
#include "file.h"
#include <iostream>

BTagging::BTagging() {
  File f("btagMaps.root");
  TH2F* tmp;
  tmp = f.getObject<TH2F>("bMV2c20OP70FlatCutvspteta70");
  m_bmap = dynamic_cast<TH2F*>(tmp->Clone());
  m_bmap->SetDirectory(0);
  tmp = f.getObject<TH2F>("cMV2c20OP70FlatCutvspteta70");
  m_cmap = dynamic_cast<TH2F*>(tmp->Clone());
  m_cmap->SetDirectory(0);
  tmp = f.getObject<TH2F>("uMV2c20OP70FlatCutvspteta70");
  m_lmap = dynamic_cast<TH2F*>(tmp->Clone());
  m_lmap->SetDirectory(0);
  f->Close();
}

BTagging::~BTagging() {
  delete m_bmap;
  delete m_cmap;
  delete m_lmap;
}

float BTagging::getJetWeight(float pt, float eta, int type) {
  int bin = -1;
  switch(type) {
    case 5:
      bin = m_bmap->FindBin(pt, fabs(eta));
      return m_bmap->GetBinContent(bin);
    case 4:
    case 15:
      bin = m_cmap->FindBin(pt, fabs(eta));
      return 1/m_cmap->GetBinContent(bin);
    case 0:
      bin = m_lmap->FindBin(pt, fabs(eta));
      return 1/m_lmap->GetBinContent(bin);
    default:
      std::cout << "BTagging::getJetWeight: ERROR flavour of jet " << type << " unknown !" << std::endl;
      break;
  }
  return -1;
}
