/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>

using namespace std;
class Gene{
    private:
        int id;
        string name;
    public:
        Gene();
        ~Gene();
        Gene(const int geneId, const string geneName);
};