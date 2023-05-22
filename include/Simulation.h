#pragma once

#include <vector>
#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    Graph &accessGraph();
    void addPartyToCoalition(int PartyId, int mandates, int coalition);
    vector<int> &getMandatesPerCoalitionVector();


private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<vector<int>> mCoalitions;
    vector<int> mandatesPerCoalition;
};
