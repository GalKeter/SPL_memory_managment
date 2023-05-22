#include "Party.h"
#include "JoinPolicy.h"
#include "Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mOffers(), iter_counter(0), lastOffer_timer(0)
{
}

Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), mOffers(other.mOffers), iter_counter(other.iter_counter), lastOffer_timer(other.lastOffer_timer) //copy constructor
 {
 }

Party::Party(Party &&other) :  mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), mOffers(std::move (other.mOffers)), iter_counter(other.iter_counter), lastOffer_timer(other.lastOffer_timer) //move constructor
{
    other.mJoinPolicy = nullptr; 
}

Party::~Party() //destructor
{
    if (mJoinPolicy)  
        delete mJoinPolicy;   
} 

Party &Party::operator=(const Party &other) //copy assignment operator
{   
    if(this!= &other)
    {
        mId=other.mId;
        mName=other.mName;
        mMandates=other.mMandates;
        mState=other.mState;
        iter_counter=other.iter_counter;
        lastOffer_timer=other.lastOffer_timer;
        mOffers = other.mOffers;
        if (mJoinPolicy)
            delete mJoinPolicy;
        mJoinPolicy = other.mJoinPolicy->clone();  
    }
    return *this;
}

Party &Party::operator=(Party &&other) //move assignment operator
{
    mId=other.mId;
    mName=other.mName;
    mMandates=other.mMandates;
    mState=other.mState;
    iter_counter=other.iter_counter;
    lastOffer_timer=other.lastOffer_timer;
    mOffers = std::move (other.mOffers);
    if (mJoinPolicy){
         delete mJoinPolicy;
    }
    mJoinPolicy = other.mJoinPolicy; //"steal"
    other.mJoinPolicy = nullptr; 
    return *this;
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    if(mState==CollectingOffers){
        if(iter_counter==3){
            int coalitionToJoin = mJoinPolicy->join(s, mOffers);
            s.addPartyToCoalition(mId, mMandates, coalitionToJoin);
            mState=Joined;
        }
        else
            iter_counter++;
    }
}

bool Party::didOffer(int coalition) const{ //check if coalition already made an offer to this party
    return mOffers[coalition]!=-1;
}

void Party::initialize_mOffers(int size){ //initialize mOffers vector to deafault value '-1' 
       for(int i=0; i<size; ++i)
     {
            mOffers.push_back(-1);
    } 
}

void Party::receiveOffer(int coalition){
    if (mState==Waiting){
        mState=CollectingOffers;
        iter_counter++;
    }
    mOffers[coalition]=lastOffer_timer;
    lastOffer_timer++;
}
