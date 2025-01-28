/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "LinkedList.h"
#include "Protein.h"

using namespace std;
Protein::Protein(){
    size = 0;
    geneList = new LinkedList<Gene>();
}

Protein::~Protein(){
    delete geneList;
}

Protein::Protein(const int proteinId){
    id = proteinId;
    size = 0;
    geneList = new LinkedList<Gene>();
}

int Protein::getId(){
    return id;
}

int Protein::getGeneNum(){
    return geneList->getSize();
}

bool Protein::addGene(const int geneId, const string geneName){
    Node<Gene>* newGene = new Node<Gene>(geneId,geneName);
    bool isAdded = geneList->add(newGene);
    if(isAdded){
        size++;
    }
    return isAdded;
}

bool Protein::removeGene(const int geneId){
    bool isDeleted = geneList->remove(geneId);
    if(isDeleted){
        size--;
    }
    return isDeleted;
}

void Protein::printGenes(){
    Node<Gene>* cur = geneList->getHeadPtr();
    while(cur!=nullptr){
        cout<<"GENE "<<cur->getId()<<" : "<<cur->getName()<<endl;
        cur = cur->getNextNode();
    }
}

string Protein::getGeneIDs(){
    string geneIDs = "[";
    Node<Gene>* cur = geneList->getHeadPtr();
    if(cur==nullptr){
        return "None";
    }
    while(cur!=nullptr){
        geneIDs+=to_string(cur->getId());
        if(cur->getNextNode()!=nullptr){
            geneIDs+=", ";
        }
        cur = cur->getNextNode();
    }
    geneIDs += "]";
    return geneIDs;
}

LinkedList<Gene> *Protein::getGeneList(){
    return geneList;
}
