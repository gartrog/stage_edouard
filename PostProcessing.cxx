#include "PostProcessing.h"
#include "file.h"
#include <TH2F.h>
#include <iostream>


double JetsFlavor(const std::string& name) {
  File f("output.root");
  TH2F* h = f.getObject<TH2F>(name);

  int bin_bb, bin_bc, bin_bl, bin_bt, bin_other;
  float ntot=0, nbb=0, nbc=0, nbl=0, nbt=0, nother=0;

  bin_bb=h->GetBin( 6, 6);
  nbb+=h->GetBinContent(bin_bb);

  bin_bc=h->GetBin( 6, 5);
  nbc+=h->GetBinContent(bin_bc);
  bin_bc=h->GetBin( 5, 6);
  nbc+=h->GetBinContent(bin_bc);


  bin_bl=h->GetBin( 6, 1);
  nbl+=h->GetBinContent(bin_bl);
  bin_bl=h->GetBin( 1, 6);
  nbl+=h->GetBinContent(bin_bl);


  bin_bt=h->GetBin( 6, 16);
  nbt+=h->GetBinContent(bin_bt);
  bin_bt=h->GetBin( 16, 6);
  nbt+=h->GetBinContent(bin_bt);



  bin_other=h->GetBin( 5, 5);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 1, 1);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 1, 5);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 5, 1);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 16, 5);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 5, 16);
  nother+=h->GetBinContent(bin_other);


  ntot=nbb+nbc+nbl+nbt+nother;

  std::cout<< "bb = " << (nbb/ntot)*100 << "%" << std::endl;
  std::cout<< "bc = " << (nbc/ntot)*100 << "%" << std::endl;
  std::cout<< "bl = " << (nbl/ntot)*100 << "%" << std::endl;
  std::cout<< "bt = " << (nbt/ntot)*100 << "%" << std::endl;
  std::cout<< "other = " << (nother/ntot)*100 << "%" << std::endl;
  f->Close();
}
