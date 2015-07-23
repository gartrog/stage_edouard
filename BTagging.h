#ifndef BTagging_h
#define BTagging_h

#include <TH2F.h>

class BTagging
{
  public:
    BTagging();
    ~BTagging();

    float getJetWeight(float pt, float eta, int type);

  private:
    TH2F* m_bmap;
    TH2F* m_cmap;
    TH2F* m_lmap;


};

#endif
