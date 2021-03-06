// Common utilities
 
#include <cmath>
#include <iostream>
#include "gen_babymaker/bmaker/interface/utilities.hh"
#include "TMath.h"

using namespace std;

namespace utilities{


  float dPhi(float phi1, float phi2){
    float delphi = TMath::Abs(TMath::Abs(TMath::Abs(phi1 - phi2) - TMath::Pi())-TMath::Pi());
    return delphi;
  }

  float dR(float phi1, float phi2, float eta1, float eta2){
    float dr = sqrt(pow(eta1-eta2,2)+pow(dPhi(phi1,phi2),2));
    return dr;
    
  }


  bool greaterPt(const reco::Candidate *a, const reco::Candidate *b) {
    return a->pt() > b->pt();
  }

  float getMT(float pt1, float phi1, float pt2, float phi2){
    //Faster calculation of mT in massless 
    return sqrt(2.*pt1*pt2*(1.-cos(phi2-phi1)));
  }

  string execute(const string &cmd){
    FILE *pipe = popen(cmd.c_str(), "r");
    if(!pipe) throw runtime_error("Could not open pipe.");
    const size_t buffer_size = 128;
    char buffer[buffer_size];
    string result = "";
    while(!feof(pipe)){
      if(fgets(buffer, buffer_size, pipe) != NULL) result += buffer;
    }

    pclose(pipe);
    return result;
  }

  TString roundNumber(double num, int decimals, double denom){
    if(denom==0) return " - ";
    double neg = 1; if(num*denom<0) neg = -1;
    num /= neg*denom; num += 0.5*pow(10.,-decimals);
    long num_int = static_cast<long>(num);
    long num_dec = static_cast<long>((1+num-num_int)*pow(10.,decimals));
    TString s_dec = ""; s_dec += num_dec; s_dec.Remove(0,1);
    TString result="";
    if(neg<0) result+="-";
    result+= num_int;
    if(decimals>0) {
      result+="."; result+=s_dec;
    }

    TString afterdot = result;
    afterdot.Remove(0,afterdot.First(".")+1);
    for(int i=0; i<decimals-afterdot.Length(); i++)
      result += "0";
    return result;
  }

  TString addCommas(double num){
    TString result(""); result += num;
    int posdot(result.First('.'));
    if(posdot==-1) posdot = result.Length();
    for(int ind(posdot-3); ind > 0; ind -= 3)
      result.Insert(ind, ",");
    return result;
  }

}
