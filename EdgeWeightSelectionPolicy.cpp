#include "SelectionPolicy.h"
#include "Graph.h"

void EdgeWeightSelectionPolicy:: select(Graph &g, int partyId, int coalition)
{
    int max=0;
    int selectedParty = -1;
    for(int i=0; i<g.getNumVertices(); ++i){
        int edgeWeight = g.getEdgeWeight(partyId,i);
        if(edgeWeight!=0){
            if(g.getParty(i).getState()!=Joined){       
                if(!g.getParty(i).didOffer(coalition)){
                    if (max<edgeWeight){
                        max = edgeWeight;
                        selectedParty = i;
                    }
                 }
               }
             }
    }
if (selectedParty!=-1)
     g.getPartyAtIndex(selectedParty).receiveOffer(coalition);
}

SelectionPolicy *EdgeWeightSelectionPolicy:: clone()
{
    return new EdgeWeightSelectionPolicy;
}

