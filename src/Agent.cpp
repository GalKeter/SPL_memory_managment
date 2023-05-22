#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), coalition(agentId)
{
}

Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()), coalition(other.coalition) //copy constructor
{
}

Agent::Agent(Agent &&other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), coalition(other.coalition) //move constructor
{
    other.mSelectionPolicy = nullptr;
}

Agent::~Agent() //destructor
{
    if (mSelectionPolicy)
        delete mSelectionPolicy; 
}

Agent &Agent::operator=(const Agent &other) //copy assignment operator
{   
    if(this != &other) {
        
        coalition = other.coalition;
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId; 
        if (mSelectionPolicy)
            delete mSelectionPolicy;
        mSelectionPolicy = other.mSelectionPolicy->clone();  
    }
    return *this;

}

Agent &Agent::operator=(Agent &&other) //move assignment operator
{
    coalition = other.coalition;
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId; 
    if(mSelectionPolicy){
         delete mSelectionPolicy;
     }
    mSelectionPolicy = other.mSelectionPolicy; 
    other.mSelectionPolicy = nullptr;
    return *this;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::setId(int id) 
{
    mAgentId = id;
}

void Agent::setPartyId(int party_id) 
{
    mPartyId = party_id;
}

void Agent::step(Simulation &sim)
{
    mSelectionPolicy->select(sim.accessGraph(), mPartyId ,coalition);
}



