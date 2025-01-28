/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "Pathway.h"
#include "LinkedList.h"
using namespace std;

Pathway::Pathway(){
    size = 0;
    proteinList = new LinkedList<Protein>();
}
Pathway::~Pathway(){
    delete proteinList;
}

bool Pathway::removeAllProteins(){
    return false;
}

Pathway::Pathway(const int pathwayId, const string pathwayName){
    id = pathwayId;
    name = pathwayName;
    size = 0;
    proteinList = new LinkedList<Protein>();
}
int Pathway::getId(){
    return id;
}

string Pathway::getName(){
    return name;
}

int Pathway::getProteinNum(){
    return proteinList->getSize();
}
int Pathway::getGeneNumInPathway(){
    Node<Protein>* cur = proteinList->getHeadPtr();
    int total = 0;

    while(cur!=nullptr){
        total+=cur->getItem().getGeneNum();
        cur = cur->getNextNode();
    }
    
    return total;
}

bool Pathway::addProtein(const int proteinId){
    Node<Protein>* newProtein = new Node<Protein>(id,"");
    bool isAdded = proteinList->add(newProtein);
    if(isAdded){
        size++;
    }
    return isAdded;
}
bool Pathway::removeProtein(const int proteinId){
    bool isDeleted = proteinList->remove(proteinId);
    if(isDeleted){
        size--;
    }
    return isDeleted;
}

LinkedList<Protein> *Pathway::getProteinList(){
    return proteinList;
}

void Pathway::printProteins(){
    if(proteinList->getSize()>0){
        Node<Protein>* cur;
        for(int i=0; i<proteinList->getSize();i++){
            cur = proteinList->getEntry(i);
            cout<<"Protein ID : "<<cur->getId()<<", Gene IDs : "<<cur->getItem().getGeneIDs()<<endl;
        }
    }
    
}
