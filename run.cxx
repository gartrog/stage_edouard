#include "VHAnalysis.h"
#include "TTree.h"
#include <file.h>
#include <iostream>

int main(int argc, char** argv) {
  File f("smallttbar.root");
  TTree* tree = f.getObject<TTree>("tupletest");
  VHAnalysis analysis(tree, "output.root");
  analysis.Loop();
  analysis.WriteHistos();

  f->Close();
  std::cout << "Closing input file" << std::endl;
  return 0;
}
