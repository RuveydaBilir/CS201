/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
using namespace std;
#include "Pathway.h"
#include "LinkedList.h"

class BiologicalPathway {
    public:
        BiologicalPathway();
        ~BiologicalPathway();

        void addPathway( const int pathwayId, const string pathwayName );
        void removePathway( const int pathwayId );
        void printPathways() const;

        void addProtein( const int proteinId, const int pathwayId );
        void removeProtein( const int proteinId, const int pathwayId );
        void printProteinsInPathway( const int pathwayId ) const;

        void addGene( const int geneID, const string geneName, const int proteinId );
        void removeGene( const int geneID, const int proteinId );
        void printGenesOfProtein( const int proteinId ) const;

        Node<Protein>* findProtein(const int proteinId);
        Node<Gene>* findGene(const int geneId);
    
    private:
        LinkedList<Pathway>* pathwayList;
        int size;
};