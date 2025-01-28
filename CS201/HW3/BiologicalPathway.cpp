/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include "BiologicalPathway.h"
#include <iostream>

using namespace std;

BiologicalPathway::BiologicalPathway(){
    size = 0;
    pathwayList = new LinkedList<Pathway>();
}

BiologicalPathway::~BiologicalPathway(){
    delete pathwayList;
}

void BiologicalPathway::addPathway(const int pathwayId, const string pathwayName){
    Node<Pathway>* newPathway = pathwayList->find(pathwayId);
    if(newPathway==nullptr){
        pathwayList->add(new Node<Pathway>(pathwayId,pathwayName));
        cout<<"Added pathway "<<pathwayId<<"."<<endl;
        return;
    }
    cout << "Cannot add pathway. There is already a pathway with ID " << pathwayId << "." << endl;
}

void BiologicalPathway::removePathway(const int pathwayId){
    bool isDeleted = pathwayList ->remove(pathwayId);
    if(isDeleted){
        cout<<"Removed pathway "<<pathwayId<<"."<<endl;
        return;
    }
    cout<<"Cannot remove pathway. There is no pathway with ID "<<pathwayId<<"."<<endl;
}

void BiologicalPathway::printPathways() const{
    if(pathwayList->getSize()==0){
        cout<<"There are no pathways to show."<<endl;
        return;
    }
    Node<Pathway>* cur;
    cout<<"Pathways in the system:"<<endl;
    for(int i=0; i<pathwayList->getSize(); i++){
        cur = pathwayList->getEntry(i);
        cout<<"Pathway "<<cur->getId()<<" : "<< cur->getName() <<" ("<<cur->getItem().getProteinNum()<<" Proteins)"<<" ("<<cur->getItem().getGeneNumInPathway()<<" Genes)"<<endl;
    }
}

void BiologicalPathway::addProtein(const int proteinId, const int pathwayId){
    Node<Pathway>* curPathway = pathwayList->find(pathwayId);
    Node<Protein>* curProtein;
    if(curPathway==nullptr){
        cout<<"Cannot add protein. There is no pathway with ID "<< pathwayId<<"."<<endl;
        return;
    }

    curProtein = findProtein(proteinId);
    if(curProtein!=nullptr){
        cout<<"Cannot add protein. There is a pathway having a protein with ID "<<proteinId<<"."<<endl;
        return;
    }
    curPathway->getItem().getProteinList()->add(new Node<Protein>(proteinId,""));
    cout<<"Added protein "<<proteinId<<" to pathway "<<curPathway->getId()<<"."<<endl;
}

void BiologicalPathway::removeProtein(const int proteinId, const int pathwayId){
    Node<Pathway>* curPathway = pathwayList->find(pathwayId);
    if(curPathway==nullptr){
        cout<<"Cannot remove protein. There is no pathway with ID "<< pathwayId<<"."<<endl;
        return;
    }
    bool isRemoved = curPathway->getItem().getProteinList()->remove(proteinId);
    if(!isRemoved){
        cout<<"Cannot remove protein. Pathway "<<curPathway->getId()<<" does not have a protein with ID "<<proteinId<<"."<<endl;
        return; 
    }
    cout<<"Removed protein "<<proteinId<<" from pathway "<<pathwayId<<"."<<endl;
}

void BiologicalPathway::printProteinsInPathway(const int pathwayId) const{
    Node<Pathway>* curPathway = pathwayList->getHeadPtr();
    if(pathwayList->getSize()>0){
        while(curPathway!=nullptr){
            if(curPathway->getId()==pathwayId){
                if(curPathway->getItem().getProteinNum()<=0){
                    cout<<"There are no proteins to show in pathway "<<pathwayId<<"."<<endl;
                    return;
                }
                cout<<"Proteins in pathway "<<pathwayId<<":"<<endl;
                curPathway->getItem().printProteins();
                return;
            }
            curPathway = curPathway->getNextNode();
        }
    }
    cout<<"Cannot print proteins. There is no pathway with ID "<<pathwayId<<"."<<endl;
}

void BiologicalPathway::addGene(const int geneID, const string geneName, const int proteinId){
    Node<Protein>* curProtein = findProtein(proteinId);
    Node<Gene>* curGene;
    if(curProtein==nullptr){
        cout<<"Cannot add gene. There is no protein with ID "<< proteinId<<"."<<endl;
        return;
    }

    curGene = findGene(geneID);
    if(curGene!=nullptr){
        cout<<"Cannot add gene. Gene "<<geneID<<" is already in use."<<endl;
        return;
    }
    curProtein->getItem().getGeneList()->add(new Node<Gene>(geneID,geneName));
    cout<<"Added gene "<<geneID<<" to protein "<<proteinId<<"."<<endl;


}

void BiologicalPathway::removeGene(const int geneID, const int proteinId){
    Node<Protein>* curProtein = findProtein(proteinId);
    if(curProtein==nullptr){
        cout<<"Cannot remove gene. There is no protein with ID "<< proteinId<<"."<<endl;
        return;
    }
    bool isDeleted = curProtein->getItem().getGeneList()->remove(geneID);
    if(!isDeleted){
        cout<<"Cannot remove gene. There is no gene "<<geneID<<" encoding protein "<<proteinId<<"."<<endl;
        return;
    }
    cout<<"Removed gene "<<geneID<<" from protein "<<proteinId<<"."<<endl;
}

void BiologicalPathway::printGenesOfProtein(const int proteinId) const{
    Node<Pathway>* cur;
    Node<Protein>* proteinCheck;
    if(pathwayList->getSize()>0){
        for(int i=0; i<pathwayList->getSize(); i++){
            cur = pathwayList->getEntry(i);
            proteinCheck = cur->getItem().getProteinList()->find(proteinId);
            if(proteinCheck!=nullptr){
                if(proteinCheck->getItem().getGeneNum()==0){
                    cout<<"There are no genes to show in protein "<<proteinId<<"."<<endl;
                    return;
                }
                cout<<"Genes in protein "<<proteinId<<":"<<endl;
                proteinCheck->getItem().printGenes();
                return;
            }
        }
    }
    cout<<"Cannot print genes. There is no protein with ID "<<proteinId<<"."<<endl;
}

Node<Protein> *BiologicalPathway::findProtein(const int proteinId){
    Node<Pathway>* cur;
    Node<Protein>* check;
    if(pathwayList->getSize()>0){
        for(int i=0; i<pathwayList->getSize(); i++){
            cur = pathwayList->getEntry(i);
            check = cur->getItem().getProteinList()->find(proteinId);
            if(check!=nullptr){
                return check;
            }
        }
    }
    return nullptr;
}

Node<Gene> *BiologicalPathway::findGene(const int geneId){
    Node<Pathway>* curPathway = pathwayList->getHeadPtr();
    Node<Protein>* curProtein;
    Node<Gene>* geneCheck;

    int curPathwaySize;
    if(pathwayList->getSize()>0){
        for(int pathNum=0; pathNum<pathwayList->getSize(); pathNum++){
            curPathway = pathwayList->getEntry(pathNum);
            curPathwaySize = curPathway->getItem().getProteinList()->getSize();
            curProtein = curPathway->getItem().getProteinList()->getHeadPtr();

            for(int i=0; i<curPathwaySize; i++){
                geneCheck = curProtein->getItem().getGeneList()->find(geneId);
                if(geneCheck!=nullptr){
                    return geneCheck;
                }
                curProtein = curProtein->getNextNode();
            }
        }
    }
    return nullptr;
}
