#include "PostProcessing.h"
#include "file.h"
#include <TH2F.h>
#include <iostream>


double JetsFlavor(const std::string& name) {
  File f("output.root");
  TH2F* h = f.getObject<TH2F>(name);

  int bin_bb, bin_bc, bin_bl, bin_bt, bin_other;
  int ntot=0, nbb=0, nbc=0, nbl=0, nbt=0, nother=0;

  bin_bb=h->GetBin( 4, 4);
  nbb+=h->GetBinContent(bin_bb);

  bin_bc=h->GetBin( 4, 3);
  nbc+=h->GetBinContent(bin_bc);
  bin_bc=h->GetBin( 3, 4);
  nbc+=h->GetBinContent(bin_bc);


  bin_bl=h->GetBin( 4, 0);
  nbl+=h->GetBinContent(bin_bl);
  bin_bl=h->GetBin( 0, 4);
  nbl+=h->GetBinContent(bin_bl);


  bin_bt=h->GetBin( 4, 14);
  nbt+=h->GetBinContent(bin_bt);
  bin_bt=h->GetBin( 14, 4);
  nbt+=h->GetBinContent(bin_bt);


  bin_other=h->GetBin( 3, 3);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 0, 0);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 0, 3);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 3, 0);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 14, 3);
  nother+=h->GetBinContent(bin_other);
  bin_other=h->GetBin( 3, 14);
  nother+=h->GetBinContent(bin_other);


  ntot=nbb+nbc+nbl+nbt+nother;

  std::cout<< "bb = " << (nbb/ntot)*100 << "%" << std::endl;
  std::cout<< "bc = " << (nbc/ntot)*100 << "%" << std::endl;
  std::cout<< "bl = " << (nbl/ntot)*100 << "%" << std::endl;
  std::cout<< "bt = " << (nbt/ntot)*100 << "%" << std::endl;
  std::cout<< "other = " << (nother/ntot)*100 << "%" << std::endl;
}
