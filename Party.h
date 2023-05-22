#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *);
    Party(const Party &other);
    Party(Party &&other);
    virtual ~Party();
    Party &operator=(const Party &other);
    Party &operator=(Party &&other);


    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const; 
    bool didOffer(int coalition) const;
    void initialize_mOffers(int size);
    void receiveOffer(int coalition);

    private:
        int mId;
        string mName;
        int mMandates;
        JoinPolicy *mJoinPolicy;
        State mState;
        vector<int> mOffers;
        int iter_counter;
        int lastOffer_timer;
};
