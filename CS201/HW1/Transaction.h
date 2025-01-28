/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#ifndef __TRANSACTION_H
#define __TRANSACTION_H

#include <string>
using namespace std;

class Transaction{
    public:
        Transaction();
        Transaction(string type, int customerID, string dvdSerialNum);
        string getTransaction();
    private:
        string type;
        int customerID;
        string dvdSerialNum;
};

#endif