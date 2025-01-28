/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "Gene.h"
#include "LinkedList.h"

using namespace std;
class Protein{
private:
    int id;
    int size;
    LinkedList<Gene>* geneList;

public:
    Protein();
    ~Protein();
    Protein(const int proteinId);
    int getId();
    int getGeneNum();
    bool addGene(const int geneId, const string geneName);
    bool removeGene(const int geneId);
    void printGenes();
    string getGeneIDs();
    LinkedList<Gene>* getGeneList();
    //Gene* findGeneInProtein(const int geneId);
    //Gene* getFirstGene();
};

