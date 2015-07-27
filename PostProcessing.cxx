#include "PostProcessing.h"
#include "file.h"
#include <TH2F.h>
#include <TH1F.h>
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

  std::cout<< "Flavor Rapartition Table" << std::endl;
  std::cout << "" << std::endl;
  std::cout<< "bb = " << (nbb/ntot)*100 << "%" << std::endl;
  std::cout<< "bc = " << (nbc/ntot)*100 << "%" << std::endl;
  std::cout<< "bl = " << (nbl/ntot)*100 << "%" << std::endl;
  std::cout<< "bt = " << (nbt/ntot)*100 << "%" << std::endl;
  std::cout<< "other = " << (nother/ntot)*100 << "%" << std::endl;
  std::cout << "" << std::endl;
  std::cout<< "**************************************************************" << std::endl;
  std::cout << "" << std::endl;

  f->Close();
}
  

double Sorting(const std::string& name) {
  File f("output.root");
  TH1F* h = f.getObject<TH1F>(name);

  float ntot=0, nHad=0, nSemLep=0, nLep=0, n_e=0, n_mu=0, n_tau=0, n_ee=0, n_emu=0, n_mumu=0, n_etau=0, n_mutau=0, n_tautau=0;

  nHad+=h->GetBinContent(1);
  
  n_e+=h->GetBinContent(2);
  n_mu+=h->GetBinContent(3);
  n_tau+=h->GetBinContent(4);
  nSemLep+= n_e + n_mu + n_tau;

  n_ee+=h->GetBinContent(5);
  n_emu+=h->GetBinContent(6);
  n_mumu+=h->GetBinContent(7);
  n_etau+=h->GetBinContent(8);
  n_mutau+=h->GetBinContent(9);
  n_tautau+=h->GetBinContent(10);
  nLep+= n_ee + n_emu + n_mumu + n_etau + n_mutau + n_tautau;

  ntot=nHad + nSemLep + nLep;

  std::cout<< "Type Repartition Table" << std::endl;
  std::cout<< "" << std::endl;
  std::cout<< "nHad = " << (nHad/ntot)*100 << "%" << std::endl;
  std::cout<< "" << std::endl;
  std::cout<< "nSemLep = " << (nSemLep/ntot)*100 << "%" << std::endl;
  std::cout<< "n_e = " << (n_e/ntot)*100 << "%" << std::endl;
  std::cout<< "n_mu = " << (n_mu/ntot)*100 << "%" << std::endl;
  std::cout<< "n_tau = " << (n_tau/ntot)*100 << "%" << std::endl;
  std::cout<< "" << std::endl;
  std::cout<< "nLep = " << (nLep/ntot)*100 << "%" << std::endl;
  std::cout<< "n_ee = " << (n_ee/ntot)*100 << "%" << std::endl;
  std::cout<< "n_emu = " << (n_emu/ntot)*100 << "%" << std::endl;
  std::cout<< "n_mumu = " << (n_mumu/ntot)*100 << "%" << std::endl;
  std::cout<< "n_etau = " << (n_etau/ntot)*100 << "%" << std::endl;
  std::cout<< "n_mutau = " << (n_mutau/ntot)*100 << "%" << std::endl;
  std::cout<< "n_tautau = " << (n_tautau/ntot)*100 << "%" << std::endl;
  std::cout<< "" << std::endl;
  std::cout<< "**************************************************************" << std::endl;
  std::cout<< "" << std::endl;
  
}
