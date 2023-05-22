#pragma once
class Graph;

class SelectionPolicy {
    public:
        virtual void select(Graph &g, int partyId, int coalition)=0;
        virtual SelectionPolicy* clone ()=0;
        virtual ~SelectionPolicy() = default;
 };

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
        virtual void select(Graph &g, int partyId, int coalition);
        virtual SelectionPolicy* clone();
 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{
     public:
        virtual void select(Graph &g, int partyId, int coalition);
        virtual SelectionPolicy* clone();
 };


