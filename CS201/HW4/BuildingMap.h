/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "Cubicle.h"
using namespace std;

class BuildingMap {
    public:
        BuildingMap(const string buildingMapFile);
        ~BuildingMap();
        void displayAllCubicles() const;
        void displayAdjacentCubicles(const int row, const int col) const;
        void displayBuildingMap() const;
        void findPaths(const int startRow, const int startCol, const int endRow, const int endCol);
        void findPaths(const int startRow, const int startCol, const int endRow, const int endCol,
                        const int avoidRow, const int avoidCol);
        Cubicle* findCubicle(int row, int column) const;
        void findPathsHelper(Cubicle* startCub, Cubicle* endCub, Cubicle* avoidCub);
        void setAllUnvisited();
        void setAdjacency(Cubicle* cub);
        void setAdjacencyForAll();
    
    private:
        Cubicle* firstCubicle;
        int rowNum;
        int colNum;
        int size;
};
