/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#ifndef CUBICLE_
#define CUBICLE_

#include <iostream>
using namespace std;

class Cubicle{
    public:
        Cubicle();
        ~Cubicle();
        Cubicle(const int row, const int col, const int cubSatus);
        void addAdjacentCubicle(Cubicle* cub); //in adjacent order
        //void removeNearCubicle(const int row, const int col);
        string printNearCubicles();
        int getNearCubicleNum();
        Cubicle* findAdjacentCubicle(const int row, const int col);
        void orderList();
        bool isVisited();
        void setIsVisited(bool isVisited);
        //bool isAdjacent(Cubicle& otherCubicle);
        string printCubicle();
        int getX();
        int getY();
        int getStatus();
        Cubicle* getNext();
        void setNext(Cubicle* newCub);
        Cubicle* getNextStack();
        void setNextStack(Cubicle* nextStack);
        Cubicle* getAdjacentItem();
        void manageLastTraversedIndex();
        void resetLastTraversedIndex();
        bool operator==(const Cubicle& other) const;

    private:
        int x;
        int y;
        int status;
        int nearCubicleNum;
        int lastTraversedIndex;
        Cubicle* nextCubicle;
        Cubicle** nearCubicles;
        Cubicle* nextStack;
        bool isCubicleVisited;
};
#endif