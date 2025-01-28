/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "Gene.h"
using namespace std;

Gene::Gene(){}

Gene::~Gene(){}

Gene::Gene(const int geneId, const string geneName){
    id = geneId;
    name = geneName;
}
