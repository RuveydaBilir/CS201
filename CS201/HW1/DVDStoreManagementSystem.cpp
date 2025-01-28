/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "DVDStoreManagementSystem.h"

using namespace std;

DVDStoreManagementSystem::DVDStoreManagementSystem() {
    dvdArr = nullptr;
    customerArr = nullptr;
    actionArr = nullptr;
    dvdArrSize = 0;
    customerArrSize = 0;
    actionArrSize = 0;
}

DVDStoreManagementSystem::~DVDStoreManagementSystem() {
    delete[] dvdArr;
    delete[] customerArr;
    delete[] actionArr;
}

void DVDStoreManagementSystem::addDVD(const string serialNo, const string title, const string director) {
    DVD temp = DVD(serialNo,title,director);

    if(dvdArr == nullptr){
        dvdArr = new DVD[1];
        dvdArr[0] = temp;
        dvdArrSize++;
        cout<<"DVD with serial number "<< serialNo << " successfully added."<<endl;
    }
    else{
        if(findDVD(dvdArr,dvdArrSize,serialNo)==nullptr){
            DVD* tempArr = new DVD[dvdArrSize+1];
            for(int i=0; i<dvdArrSize; i++){
                tempArr[i]=dvdArr[i];
            }
            tempArr[dvdArrSize] = temp;
            delete[] dvdArr;
            dvdArr = tempArr;

            dvdArrSize++;
            cout<<"DVD with serial number "<< serialNo << " successfully added."<<endl;
        }
        else{
            cout<<"Cannot add DVD. DVD with serial number "<<serialNo<<" already exists."<<endl;
        }
    }
}

void DVDStoreManagementSystem::removeDVD(const string serialNo) {
    if(dvdArrSize==1){
        if(dvdArr[0].getSerialNum()==serialNo){
            if(dvdArr[0].getStatus()=="Available"){
                delete[] dvdArr;
                dvdArr = nullptr;
                dvdArrSize--;
                cout<<"DVD with serial number "<< serialNo << " successfully removed."<<endl;
            }
            else{
                cout<<"Cannot remove DVD. DVD with serial number "<<serialNo<<" is currently rented by a customer."<<endl;
            }
        }
        else{
            cout<<"Cannot remove DVD. DVD with serial number "<<serialNo<<" not found."<<endl;
        }
    }

    else if(dvdArr != nullptr){
        int index=-1;
    
        for(int i=0; i<dvdArrSize; i++){
            if(dvdArr[i].getSerialNum()==serialNo){
                index = i;
            }
        }
        if(index != -1){
            DVD* temp = dvdArr;
            if(dvdArr[index].getStatus()=="Available"){
                dvdArr = new DVD[dvdArrSize-1];
                for(int i=0; i< index; i++){
                    dvdArr[i]=temp[i];
                }
                for(int i = index+1; i< dvdArrSize; i++){
                    dvdArr[i-1] = temp[i];
                }
                dvdArrSize--;
                delete[] temp;
                cout<<"DVD with serial number "<< serialNo << " successfully removed."<<endl;
            }
            else{
                cout<<"Cannot remove DVD. DVD with serial number "<<serialNo<<" is currently rented by a customer."<<endl;
            }
        }
        else{
            cout<<"Cannot remove DVD. DVD with serial number "<<serialNo<<" not found."<<endl;
        }
    }
    else{
        cout<<"Cannot remove DVD. DVD with serial number "<<serialNo<<" not found."<<endl;
    }
}

void DVDStoreManagementSystem::addCustomer(const int customerID, const string name) {
    Customer temp = Customer(customerID, name);

    if(customerArr == 0){
        customerArr = new Customer[1];
        customerArr[0] = temp;
        customerArrSize++;
        cout<<"Customer with ID "<< customerID << " successfully added."<<endl;
    }
    else{
        if(findCustomer(customerArr, customerArrSize, customerID)==nullptr){
            Customer* tempArr = new Customer[customerArrSize+1];
            for(int i=0; i<customerArrSize; i++){
                tempArr[i] = customerArr[i];
            }
            tempArr[customerArrSize] = temp;
            delete[] customerArr;
            customerArr = tempArr;

            customerArrSize++;
            cout<<"Customer with ID "<< customerID << " successfully added."<<endl;
        }
        else{
            cout<<"Cannot add customer. Customer with ID "<< customerID <<" already exists."<<endl;
        }
    }

}

void DVDStoreManagementSystem::removeCustomer(const int customerID) {
    if(customerArrSize==1){
        if(customerArr[0].getId()==customerID){
            if(customerArr[0].getDvdNum()==0){    
                delete[] customerArr;
                customerArr = nullptr;
                customerArrSize--;
                cout<<"Customer with ID "<< customerID << " successfully removed."<<endl;
            }
            else{
                cout<<"Cannot remove customer. Customer with ID "<<customerID<<" has rented DVDs."<<endl;
            }
        }
        else{
            cout<<"Cannot remove customer. Customer with ID "<<customerID<<" not found."<<endl;
        }
    }
    else if(customerArr != nullptr){
        int index=-1;

        for(int i=0; i<customerArrSize; i++){
            if(customerArr[i].getId()==customerID){
                index=i;
            }
        }
        if(index !=-1){
            Customer* tempArr = customerArr;
            if(customerArr[index].getDvdNum()==0){
                customerArr = new Customer[customerArrSize-1];
                for(int i=0; i<index; i++){
                    customerArr[i]=tempArr[i]; //TODO: operator = eklee
                }
                for(int i= index+1; i<customerArrSize; i++){
                    customerArr[i-1] = tempArr[i];
                }
                delete[] tempArr;
                customerArrSize --;
                cout<<"Customer with ID "<< customerID << " successfully removed."<<endl;
            }
            else{
                cout<<"Cannot remove customer. Customer with ID "<<customerID<<" has rented DVDs."<<endl;
            }    
        }
        else{
            cout<<"Cannot remove customer. Customer with ID "<<customerID<<" not found."<<endl;
        }
   
    }
    else{
        cout<<"Cannot remove customer. Customer with ID "<<customerID<<" not found."<<endl;
    }
}

void DVDStoreManagementSystem::rentDVD(const int customerID, const string serialNo) {
    Customer* cust = findCustomer(customerArr,customerArrSize,customerID);
    DVD* dvd = findDVD(dvdArr,dvdArrSize,serialNo);

    if(cust != nullptr && dvd != nullptr){
        if((*dvd).getStatus() == "Available"){
            (*cust).rentDVD(dvd);
            cout<<"DVD with serial number "<<serialNo<< " successfully rented by customer with ID "<< customerID <<"."<<endl;
            addTransaction("Rental",customerID,serialNo);

        }
        else{
            cout<<"Cannot rent DVD. DVD with serial number "<<serialNo<<" is not available."<<endl;
        }
        
    }
    else if(cust==nullptr && dvd != nullptr){
        cout<<"Cannot rent DVD. Customer with ID "<<customerID<<" not found."<<endl;
    }
    else if(dvd==nullptr && cust != nullptr){
        cout<<"Cannot rent DVD. DVD with serial number "<<serialNo<<" not found."<<endl;
    }
    else{
        cout<<"Cannot rent DVD. Customer with ID "<<customerID<< " and DVD with serial number "<<serialNo<<" not found."<<endl;

    }
}

void DVDStoreManagementSystem::returnDVD(const int customerID, const string serialNo) {
    Customer* cust = findCustomer(customerArr,customerArrSize,customerID);
    DVD* dvd = findDVD(dvdArr,dvdArrSize,serialNo);

    if(cust != nullptr && dvd != nullptr){
        if((*dvd).getStatus()=="Rented"){
            if((*cust).hasDVD(dvd)){
                (*cust).returnDVD(dvd);
                cout<<"DVD with serial number "<<serialNo<<" successfully returned by customer with ID "<<customerID<<"."<<endl;
                addTransaction("Return",customerID,serialNo);
            }
            else{
                cout<<"Cannot return DVD. DVD with serial number "<<serialNo<<" not rented by customer with ID "<<customerID<<"."<<endl;
            }
        }
    }
    else if(cust == nullptr && dvd != nullptr){
        cout<<"Cannot return DVD. Customer with ID "<<customerID<<" not found."<<endl;
    }
    else if(cust != nullptr && dvd == nullptr){
        cout<<"Cannot return DVD. DVD with serial number "<<serialNo<<" not found."<<endl;
    }
    else{
        cout<<"Cannot return DVD. Customer with ID "<<customerID<<" and DVD with serial number "<<serialNo<<" not found."<<endl;
    }
}

void DVDStoreManagementSystem::showAllDVDs() const{
    cout<<"DVDs in the system:"<<endl;
    if(dvdArrSize > 0 ){
        for(int i=0; i<dvdArrSize; i++){
            showDVD((dvdArr[i]).getSerialNum());
        }
    }
    else{
        cout<<"None"<<endl;
    }
}

void DVDStoreManagementSystem::showAllCustomers() const{
    cout<<"Customers in the system:"<<endl;
    if(customerArrSize> 0 ){
        for(int i=0; i<customerArrSize; i++){
            showCustomer((customerArr[i]).getId());
        }
    }
    else{
        cout<<"None"<<endl;
    }
}

void DVDStoreManagementSystem::showDVD( const string serialNo ) const{
    bool isFound=false;
    for(int i=0; i<dvdArrSize && !isFound; i++){
        if(dvdArr[i].getSerialNum() == serialNo){
            DVD* dvd = (dvdArr+i);
            cout<<"DVD: "<< (*dvd).getSerialNum() << ", Title: " << (*dvd).getTitle() << ", Director: "<<(*dvd).getDirector()<<", "<<(*dvd).getStatus()<<endl;
            isFound=true;
        }
    }
    if(!isFound){
        cout<<"DVD with serial number "<<serialNo<<" not found."<<endl;
    }
}

void DVDStoreManagementSystem::showCustomer( const int customerID ) const{
    bool isFound=false;
    for(int i=0; i<customerArrSize && !isFound; i++){
        if(customerArr[i].getId()== customerID){
            Customer* customer = (customerArr+i);
            cout<<"Customer: "<< (*customer).getId()<<", Name: "<<(*customer).getName()<<", DVDs Rented: "<< (*customer).getDvdNum()<<endl;
            isFound=true;
        }
    }
    if(!isFound){
        cout<<"Customer with ID "<<customerID<<" not found."<<endl;
    }
    
}

void DVDStoreManagementSystem::showTransactionHistory() const{
    cout<<"Transactions in the system:"<<endl;
    if(actionArr!=nullptr){
        for(int i=0; i< actionArrSize; i++){
            cout << actionArr[i].getTransaction() << endl;
        }
    }
    else{
        cout<<"None"<<endl;
    }
}

DVD* DVDStoreManagementSystem::findDVD(DVD* dvdArr, const int arrSize, const string serialNo){
    if(dvdArr != nullptr){
        for(int i=0; i< arrSize; i++){
            if((*(dvdArr+i)).getSerialNum() == serialNo){
                return &(dvdArr[i]);
            }
        }
    }
    return nullptr;
}

Customer* DVDStoreManagementSystem::findCustomer(Customer* customerArr,const int arrSize, const int id){
    if(customerArr != nullptr){
        for(int i=0; i<arrSize; i++){
            if((*(customerArr+i)).getId() == id){
                return &(customerArr[i]);
            }
        }
    }
    return nullptr;
}

void DVDStoreManagementSystem::addTransaction(string type, int customerID, string dvdSerialNo){
    Transaction action = Transaction(type, customerID, dvdSerialNo); 
    if(actionArr==nullptr){
        actionArr = new Transaction[1];
        actionArr[0] = action;
        actionArrSize++;
    }
    else{
        Transaction* tempArr = new Transaction[actionArrSize+1];
        for(int i=0; i<actionArrSize; i++){
            tempArr[i]=actionArr[i];
        }
        tempArr[actionArrSize] = action;
        delete[] actionArr;
        actionArr = tempArr;
        actionArrSize++;
    }
}


