/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#ifndef __DVDSTOREMANAGEMENTSYSTEM_H
#define __DVDSTOREMANAGEMENTSYSTEM_H

#include <string>
#include "DVD.h"
#include "Customer.h"
#include "Transaction.h"

using namespace std;

class DVDStoreManagementSystem {

public:
    DVDStoreManagementSystem();
    ~DVDStoreManagementSystem();
    
    void addDVD( const string serialNo, const string title, const string director );
    void removeDVD( const string serialNo );
    void addCustomer( const int customerID, const string name );
    void removeCustomer( const int customerID );
    void rentDVD( const int customerID, const string serialNo );
    void returnDVD( const int customerID, const string serialNo );
    void showAllDVDs() const;
    void showAllCustomers() const;
    void showDVD( const string serialNo ) const;
    void showCustomer( const int customerID ) const;
    void showTransactionHistory() const;
    DVD* findDVD(DVD* dvdArr, const int arrSize, const string serialNo);
    Customer* findCustomer(Customer* customerArr,const int arrSize, const int id);
    void addTransaction(string type, int customerID, string dvdSerialNo);

private:
    int dvdArrSize;
    int customerArrSize;
    int actionArrSize;
    DVD* dvdArr; 
    Customer* customerArr;
    Transaction* actionArr;
};

#endif