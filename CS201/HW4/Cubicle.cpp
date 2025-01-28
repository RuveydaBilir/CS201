/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include "Cubicle.h"
#include <iostream>
using namespace std;

Cubicle::Cubicle(){
    nextCubicle = nullptr;
    nextStack = nullptr;
    isCubicleVisited = false;
}

Cubicle::~Cubicle(){
    delete[] nearCubicles;
}

Cubicle::Cubicle(const int row, const int col, const int cubSatus){
    x=row;
    y=col;
    status=cubSatus;
    nextCubicle = nullptr;
    nextStack = nullptr;
    nearCubicles = new Cubicle*[3]; 
    nearCubicleNum = 0;
    lastTraversedIndex = -1;
    isCubicleVisited = false;
}

void Cubicle::addAdjacentCubicle(Cubicle *cub){
    if(nearCubicleNum >= 3){ 
        return;
    }
    nearCubicles[nearCubicleNum] = cub;
    nearCubicleNum++;

    if(cub->findAdjacentCubicle(getX(), getY()) == nullptr){
        cub->addAdjacentCubicle(this);
    }
    orderList();
}

string Cubicle::printNearCubicles(){
    string str = printCubicle()+ " -> ";
    for(int i=0; i<nearCubicleNum; i++){
        str+=nearCubicles[i]->printCubicle();
        if(i<nearCubicleNum-1){
            str+=",";
        }
    }
    return str;
}

int Cubicle::getNearCubicleNum(){
    return nearCubicleNum;
}

Cubicle *Cubicle::findAdjacentCubicle(const int row, const int col){
    Cubicle* temp;
    int tempX;
    int tempY;
    for(int i=0; i<nearCubicleNum; i++){
        temp = nearCubicles[i];
        tempX = temp->getX();
        tempY = temp->getY();
        if(tempX==row && tempY==col){
            return temp;
        }
    }
    return nullptr;
}

void Cubicle::orderList(){
    Cubicle* temp;
    for(int i=1; i<nearCubicleNum; i++){
        if((nearCubicles[i-1]->getX() > nearCubicles[i]->getX()) 
            || ((nearCubicles[i-1]->getX() == nearCubicles[i]->getX()) && (nearCubicles[i-1]->getY() > nearCubicles[i]->getY()))){
            temp = nearCubicles[i-1];
            nearCubicles[i-1] = nearCubicles[i];
            nearCubicles[i] = temp;
        }
    }

}

bool Cubicle::isVisited(){
    return isCubicleVisited;
}

void Cubicle::setIsVisited(bool isVisited){
    isCubicleVisited = isVisited;
    if(!isVisited){
        lastTraversedIndex = -1;
    }
}

string Cubicle::printCubicle(){
    return "("+to_string(x)+","+to_string(y)+")";
}

int Cubicle::getX(){
    return x;
}

int Cubicle::getY(){
    return y;
}

int Cubicle::getStatus(){
    return status;
}

Cubicle *Cubicle::getNext(){
    return nextCubicle;
}

void Cubicle::setNext(Cubicle* newCub){
    nextCubicle = newCub;
}

Cubicle *Cubicle::getNextStack(){
    return nextStack;
}

void Cubicle::setNextStack(Cubicle *newNextStack){
    nextStack = newNextStack;
}

Cubicle *Cubicle::getAdjacentItem(){
    Cubicle* cur;
    for(int i=0; i<nearCubicleNum; i++){
        cur = nearCubicles[i];
        if(lastTraversedIndex<nearCubicleNum){
            if(i>lastTraversedIndex && cur->isVisited()==false){
                lastTraversedIndex = i;
                //cout<<"Getting adjacent index of: "<<printCubicle()<<": "<< lastTraversedIndex<<endl;
                manageLastTraversedIndex();
                return cur;
            }
        }
    }
    return nullptr;
}

void Cubicle::manageLastTraversedIndex(){
    if(lastTraversedIndex>nearCubicleNum){
        lastTraversedIndex = -1;
    }
}

void Cubicle::resetLastTraversedIndex(){
    lastTraversedIndex = -1;
}

bool Cubicle::operator==(const Cubicle &other) const{
    return (x==other.x) && (y==other.y);
}
