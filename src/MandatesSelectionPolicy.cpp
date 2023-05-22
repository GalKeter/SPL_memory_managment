#include "SelectionPolicy.h"
#include "Graph.h"

void MandatesSelectionPolicy:: select(Graph &g, int partyId, int coalition){
    int maxMandates=-1;
    int selectedParty = -1;
    for(int i=0; i<g.getNumVertices(); ++i){
        int edgeWeight = g.getEdgeWeight(partyId,i);
        Party p = g.getParty(i);
        if(edgeWeight!=0){
            if(p.getState()!=Joined){
                if(!p.didOffer(coalition)){
                    if (maxMandates < p.getMandates()){
                        maxMandates = p.getMandates();
                        selectedParty = i;
                    }
              
               }       
            }
        }
    }
if (selectedParty!=-1)
     g.getPartyAtIndex(selectedParty).receiveOffer(coalition);
}

SelectionPolicy *MandatesSelectionPolicy:: clone()
{
    return new MandatesSelectionPolicy;
}

