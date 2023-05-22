#include "JoinPolicy.h"
#include "Simulation.h"

int LastOfferJoinPolicy:: join(Simulation &s, vector<int> &mOffers)
{
    int coalitionToJoin = 0;
    for (unsigned int i = 1; i < mOffers.size(); i++){
        if(mOffers[coalitionToJoin]<mOffers[i])
            coalitionToJoin=i;  
    }
    return coalitionToJoin;
}

JoinPolicy* LastOfferJoinPolicy::clone()
{
    return new LastOfferJoinPolicy;
}

