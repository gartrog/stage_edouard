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
  TTree* tree = f.getObject<TTree>("tupletest");
  VHAnalysis analysis(tree, "output.root");
  analysis.Loop();
  analysis.WriteHistos();

  f->Close();
  std::cout << "Closing input file" << std::endl;

  std::vector<std::string> names {"btag_nJet2MET0_jet1truthvsjet2truth", "btag_nJet2MET1_jet1truthvsjet2truth"};
  for(std::string& s : names) {
	//JetsFlavor(s);
  }
  
  return 0;
}
