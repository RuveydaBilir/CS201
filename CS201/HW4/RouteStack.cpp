/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "RouteStack.h"
#include "Cubicle.h"

RouteStack::RouteStack(){
    first = nullptr;
    size = 0;
}

RouteStack::~RouteStack(){
    while(!isEmpty()){
        pop();
    }
}

bool RouteStack::isEmpty() const{
    return first==nullptr;
}

void RouteStack::push(Cubicle* entry){
    //cout<<entry->printCubicle()<<" is pushed."<<endl;
    entry->setNextStack(first);
    first = entry;
    size++;
}

Cubicle* RouteStack::pop(){
    Cubicle* popCub;
    if(!isEmpty()){
        popCub = first;
        first = first->getNextStack();
        popCub->setNextStack(nullptr);

        //cout<<popCub->printCubicle()<<" is popped"<<endl;
        return popCub;
    }
    return nullptr;
}

Cubicle* RouteStack::peek(){
    return first;
}

string RouteStack::printStack(){
    //cout<<"Print stack"<<endl;
    string str = "";
    RouteStack tempStack;
    if(isEmpty()){
        str = "None";
        return str;
    }

    Cubicle* cur = first;
    str = cur->printCubicle();
    cur = cur->getNextStack();
    while (cur != nullptr) {
        str = cur->printCubicle() + " -> " + str;
        cur = cur->getNextStack();
    }
    return str;
}
