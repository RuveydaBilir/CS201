/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#ifndef __CUSTOMER_H
#define __CUSTOMER_H

#include <string>
#include "DVD.h"
using namespace std;

class Customer{
public:
    Customer();
    Customer(int id, string name);
    ~Customer();
    DVD* getCustomerDvdArr();
    int getId();
    void rentDVD(DVD* dvd);
    void returnDVD(DVD* dvd);
    string getName();
    int getDvdNum();
    bool hasDVD(DVD* dvd);
    Customer& operator=(const Customer& right);

private:
    int id;
    string name;
    int dvdNum;
    DVD* customerDvd;
    int customerDVDSize; 
};
#endif