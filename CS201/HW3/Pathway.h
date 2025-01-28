/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "Protein.h"
using namespace std;

class Pathway{
    public:
        Pathway();
        ~Pathway();
        bool removeAllProteins();
        Pathway(const int pathwayId, const string pathwayName);
        int getId();
        string getName();
        int getProteinNum();
        int getGeneNumInPathway();
        bool addProtein(const int proteinId);
        bool removeProtein(const int proteinId);
        LinkedList<Protein>* getProteinList();
        void printProteins();

    private:
        int id;
        string name;
        LinkedList<Protein>* proteinList;
        int size;
};