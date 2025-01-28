/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "Transaction.h"

using namespace std;

Transaction::Transaction(){}
Transaction::Transaction(string type, int customerID, string dvdSerialNum):type(type),customerID(customerID),dvdSerialNum(dvdSerialNum){}
string Transaction::getTransaction(){
    return "Transaction: " + type + ", Customer: " + to_string(customerID) + ", DVD: " + dvdSerialNum;
}