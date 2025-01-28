/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include "BuildingMap.h"
#include "RouteStack.h"
#include <iostream>
#include <fstream>

BuildingMap::~BuildingMap(){
    Cubicle* cur = firstCubicle;
    Cubicle* temp;
    while(cur!=nullptr){
        temp = cur;
        cur = cur->getNext();
        delete temp;
    }
}

BuildingMap::BuildingMap(const string buildingMapFile){
    firstCubicle = new Cubicle(-1,-1,-1);
    string strRow;
    int status;
    Cubicle* temp;
    Cubicle* deleteThis;

    ifstream infile(buildingMapFile);

    infile>>rowNum>>colNum;
    size = rowNum*colNum;
    temp = firstCubicle;

    for(int x=0; x<rowNum; x++){
        infile>>strRow;
        for(int y=0; y<colNum;y++){
            status = strRow[y] - '0';
            temp->setNext(new Cubicle(x,y,status));
            temp = temp->getNext();
        }
    }
    deleteThis =  firstCubicle;
    firstCubicle = firstCubicle->getNext();
    delete deleteThis;
    setAdjacencyForAll();
    cout<<rowNum<<" rows and "<<colNum<<" columns have been read."<<endl;
}

void BuildingMap::setAdjacency(Cubicle* cub){
    int x = cub->getX();
    int y = cub->getY();
    int status = cub->getStatus();

    if(status==0){ // bottom - left open
        if(x<rowNum-1){ //add bottom
            cub->addAdjacentCubicle(findCubicle(x+1,y));
        }
        if(y>0){ //add left
            cub->addAdjacentCubicle(findCubicle(x,y-1));
        }
    }
    else if(status==1){ //bottom open
        if(x<rowNum-1){ //add bottom
            cub->addAdjacentCubicle(findCubicle(x+1,y));
        }
    }
    else if(status==2){ // left open (index-1)
        if(y>0){ //add left
            cub->addAdjacentCubicle(findCubicle(x,y-1));
        }
    }   

}

void BuildingMap::setAdjacencyForAll(){
    //cout<<"setAdjacencyForAll():"<<endl;
    Cubicle* temp = firstCubicle;
    while(temp!=nullptr){
        setAdjacency(temp);
        //cout<<"Addjacency is set for: "<<temp->printCubicle()<<endl;
        temp = temp->getNext();
    }
}

void BuildingMap::displayAllCubicles() const{
    cout<<"The cubicles in the building are:"<<endl;
    Cubicle* temp = firstCubicle;
    for(int x=0; x<rowNum; x++){
        for(int y=0; y<colNum;y++){
            cout<<temp->printCubicle();
            if(y!=colNum-1){
                cout<<",";
            }
            temp=temp->getNext();
        }
        cout<<endl;
    }
}

void BuildingMap::displayAdjacentCubicles(const int row, const int col) const{
    Cubicle* cub = findCubicle(row,col);
    cout<<"The cubicles adjacent to "<<cub->printCubicle()<<" are:"<<endl;
    cout<<cub->printNearCubicles()<<endl;
}

void BuildingMap::displayBuildingMap() const{
    cout<<"The building map is as follows:"<<endl;
    Cubicle* temp = firstCubicle;
    while(temp!=nullptr){
        cout<<temp->printNearCubicles()<<endl;
        temp = temp->getNext();
    }
}

void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol){
    Cubicle* startCub = findCubicle(startRow,startCol);
    Cubicle* endCub = findCubicle(endRow,endCol);

    cout<<"Paths from "<<startCub->printCubicle() <<" to "<<endCub->printCubicle()<<" are:"<<endl;
    findPathsHelper(startCub,endCub,nullptr);
}

void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol, const int avoidRow, const int avoidCol){
    Cubicle* startCub = findCubicle(startRow,startCol);
    Cubicle* endCub = findCubicle(endRow,endCol);
    Cubicle* avoidCub = findCubicle(avoidRow,avoidCol);

    if(avoidCub == nullptr){
        return;
    }
    cout<<"Paths from "<<startCub->printCubicle() <<" to "<<endCub->printCubicle()<<" avoiding "<<avoidCub->printCubicle()<<" are:"<<endl;

    if(avoidCub == startCub || avoidCub == endCub){
        cout<<"None"<<endl;
        return;
    }
    findPathsHelper(startCub,endCub,avoidCub);
}

void BuildingMap::findPathsHelper(Cubicle *startCub, Cubicle *endCub, Cubicle *avoidCub){
    Cubicle* curCub;
    Cubicle* adjCub;
    RouteStack stack = RouteStack();
    bool isPathFound = false;

    if(startCub==nullptr || endCub==nullptr){
        return;
    }

    stack.push(startCub);
    startCub->setIsVisited(true);

    if(startCub == endCub){
        cout<<stack.printStack()<<endl;
        return;
    }

    while(!stack.isEmpty()){
        curCub = stack.peek();
        if(curCub == endCub){ 
            cout<<stack.printStack()<<endl;
            isPathFound = true;
            endCub->setIsVisited(false);
            stack.pop();
            curCub = stack.peek();
        }
        adjCub = curCub->getAdjacentItem();
        if(adjCub != nullptr){
            if(adjCub != avoidCub){
                stack.push(adjCub);
            }
            adjCub->setIsVisited(true);
        }
        else{
            curCub->setIsVisited(false);
            stack.pop();
        }
    }
    if(!isPathFound){
        cout<<stack.printStack()<<endl;
    }
    setAllUnvisited();
}

Cubicle* BuildingMap::findCubicle(int row, int column) const{
    Cubicle* temp = firstCubicle;
    int tempX; 
    int tempY; 

    while(temp!=nullptr){
        tempX = temp->getX();
        tempY = temp->getY();
        if(tempX==row && tempY==column){
            return temp;
        }
        temp = temp->getNext();
    }
    return nullptr;
}

void BuildingMap::setAllUnvisited(){
    Cubicle* cur = firstCubicle;
    while(cur!=nullptr){
        cur->setIsVisited(false);
        cur->resetLastTraversedIndex();
        cur = cur->getNext();
    }
}

/*NOLUR NOLMAZ:
    Cubicle* startCub = findCubicle(startRow,startCol);
    Cubicle* endCub = findCubicle(endRow,endCol);
    Cubicle* curCub;
    Cubicle* adjCub;
    RouteStack stack = RouteStack();
    bool isPathFound = false;

    if(startCub==nullptr || endCub==nullptr){
        return;
    }

    stack.push(startCub);
    startCub->setIsVisited(true);

    cout<<"Paths from "<<startCub->printCubicle() <<" to "<<endCub->printCubicle()<<" are:"<<endl;

    while(!stack.isEmpty()){
        //cout<<"Current Stack: "<<stack.printStack()<<endl;
        curCub = stack.peek();
        //cout<<"Checking cubicle: "<<curCub->printCubicle()<<endl;
        if(curCub == endCub){ 
            cout<<stack.printStack()<<endl;
            isPathFound = true;
            //stack.clearStackUntil(startCub);
            //setAllUnvisited();
            endCub->setIsVisited(false);
            stack.pop();
            curCub = stack.peek();
        }
        adjCub = curCub->getAdjacentItem();
        if(adjCub != nullptr){
            stack.push(adjCub);
            adjCub->setIsVisited(true);
        }
        else{
            curCub->setIsVisited(false);
            stack.pop();
        }
    }
    //cout<<"Stack is empty"<<endl;
    if(!isPathFound){
        cout<<stack.printStack()<<endl;
    }
    setAllUnvisited();
*/
