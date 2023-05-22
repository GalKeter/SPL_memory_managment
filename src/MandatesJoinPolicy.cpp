#include "JoinPolicy.h"
#include "Simulation.h"

int MandatesJoinPolicy:: join(Simulation &s, vector<int> &mOffers)
{
    vector<int> mandatesVector=s.getMandatesPerCoalitionVector();
    int coalitionToJoin = -1;
    int maxMandates = -1;
    for (unsigned int i = 0; i < mOffers.size(); i++){
        if(mOffers[i] != -1){
            if (maxMandates<mandatesVector[i])
            {
                coalitionToJoin=i;
                maxMandates=mandatesVector[i];
            }
            else if (maxMandates==mandatesVector[i])
            {
                if (mOffers[i]<mOffers[coalitionToJoin]) //checks which coalition offered first
                    coalitionToJoin=i;
            } 
        }  
    }
    return coalitionToJoin;
}

JoinPolicy* MandatesJoinPolicy::clone()
{
    return new MandatesJoinPolicy;
};

