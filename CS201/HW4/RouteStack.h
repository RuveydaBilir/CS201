/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#ifndef ROUTE_STACK_
#define ROUTE_STACK_

#include "Cubicle.h"

class RouteStack{
    public:
        RouteStack();
        ~RouteStack();
        bool isEmpty() const;
        void push(Cubicle* entry);
        Cubicle* pop();
        Cubicle* peek();
        string printStack();
    
    private:
        Cubicle* first;
        int size;
};
#endif