#pragma once
#include "Simulation.h"

class JoinPolicy {
   public:
     virtual int join(Simulation &s, vector<int> &mOffers)=0;
     virtual JoinPolicy* clone ()=0;
     virtual ~JoinPolicy()=default;
 };

class MandatesJoinPolicy : public JoinPolicy {
  public:
     virtual int join(Simulation &s, vector<int> &mOffers);
     virtual JoinPolicy* clone();
};

class LastOfferJoinPolicy : public JoinPolicy {
  public:
     virtual int join(Simulation &s, vector<int> &mOffers);
     virtual JoinPolicy* clone ();
};
