#include "Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mCoalitions(), mandatesPerCoalition() 
{
    for(Agent &agent: agents){ //create coalitions matrix and update mandates per coalition
        mCoalitions.push_back({agent.getPartyId()});
        mandatesPerCoalition.push_back(getParty(agent.getPartyId()).getMandates());
    } 
    int num_of_coalitions = agents.size(); //number of agents(=num of coalitions)
    mGraph.initialize_mOffers(num_of_coalitions);  
}

void Simulation::step()
{
    for(int i=0; i<mGraph.getNumVertices(); i++)
    {
        mGraph.getPartyAtIndex(i).step(*this);
    }
   for(Agent &agent:mAgents)
   {
        agent.step(*this);
   }
}

bool Simulation::shouldTerminate() const
{
    for (unsigned int i = 0; i < mandatesPerCoalition.size(); i++)
    {
        if(mandatesPerCoalition[i]>60)
            return true;
    }

    for (int i=0; i<mGraph.getNumVertices(); i++)
    {
        if (mGraph.getParty(i).getState()!=Joined)
            return false;
    }
    return true;  
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::accessGraph() //non-const getter
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

void Simulation::addPartyToCoalition(int PartyId, int mandates, int coalition){
    //adding party to coalition
    mCoalitions[coalition].push_back(PartyId);
    mandatesPerCoalition[coalition]+=mandates;
    //cloning agent
    Agent cloned_agent = Agent(mAgents[coalition]); 
    cloned_agent.setPartyId(PartyId);
    cloned_agent.setId(mAgents.size());
    mAgents.push_back(cloned_agent);
}

vector<int> &Simulation::getMandatesPerCoalitionVector(){
    return mandatesPerCoalition;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    return mCoalitions;
}
