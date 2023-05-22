#pragma once
#include <vector>
#include "Party.h"

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party &getParty(int partyId) const;
    Party &getPartyAtIndex(int partyId);
    void initialize_mOffers(int size);

private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
};
