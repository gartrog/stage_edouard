#include "VHAnalysis.h"
#include "TTree.h"
#include "PostProcessing.h"
#include <file.h>
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
  //File f("smallttbar.root");
  File f("ttbar.root");
  //File f("ZHvv125.root");
  TTree* tree = f.getObject<TTree>("tupletest");
  VHAnalysis analysis(tree, "output.root");
  //VHAnalysis analysis(tree, "outputHiggs.root");
  analysis.Loop();
  analysis.WriteHistos();

  f->Close();
  std::cout << "Closing input file" << std::endl;

  // std::vector<std::string> names {"btag_nJet2MET0_jet1truthvsjet2truth", "btag_nJet2MET1_jet1truthvsjet2truth",
                                  // "btag_nJet2MET2_jet1truthvsjet2truth", "btag_nJet2MET3_jet1truthvsjet2truth",
                                  // "btag_nJet3MET0_jet1truthvsjet2truth", "btag_nJet3MET1_jet1truthvsjet2truth",
                                  // "btag_nJet3MET2_jet1truthvsjet2truth", "btag_nJet3MET3_jet1truthvsjet2truth"};
  // for(std::string& s : names) {
    // JetsFlavor(s);
  // }
  // 
  // std::vector<std::string> noms {"nJet2MET0_compo", "nJet2MET1_compo",
                                  // "nJet2MET2_compo", "nJet2MET3_compo",
                                  // "nJet3MET0_compo", "nJet3MET1_compo",
                                  // "nJet3MET2_compo", "nJet3MET3_compo"};
  // for(std::string& ss : noms) {
    // Sorting(ss);
  // }
  // 
  return 0;
}
