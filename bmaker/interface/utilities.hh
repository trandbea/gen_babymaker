// Common utilities

#ifndef H_UTILITIES
#define H_UTILITIES

#include <vector>
#include <string>
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "TString.h"

typedef std::vector<const reco::Candidate*> vCands;
typedef reco::Candidate::LorentzVector LVector;

namespace utilities{

  enum SysEnum{kSysJER, kSysJECUp, kSysJECDn, kSysLast};

  float dPhi(float phi1, float phi2);
  float dR(float phi1, float phi2, float eta1, float eta2);
  bool greaterPt(const reco::Candidate *a, const reco::Candidate *b);
  float getMT(float pt1, float phi1, float pt2, float phi2);
  std::string execute(const std::string &cmd);
  TString roundNumber(double num, int decimals, double denom=1.);
  TString addCommas(double num);

}

#endif
