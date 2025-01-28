/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/

#include <iostream>
#include "Customer.h"

using namespace std;
Customer::Customer(){
    customerDvd = nullptr;
    customerDVDSize = 0;
    name = "Default";
    id = 0;
}
Customer::Customer(int id, string name):id(id), name(name){
    customerDvd = nullptr;
    customerDVDSize = 0;
}
Customer::~Customer(){
    delete[] customerDvd;
    customerDvd = nullptr;
}
string Customer::getName(){
    return name;
}
int Customer::getDvdNum(){
    return customerDVDSize;
}
int Customer::getId(){
    return id;
}
DVD* Customer::getCustomerDvdArr(){
    return customerDvd;
}
void Customer::rentDVD(DVD* dvd){
    if(customerDvd == nullptr){
        customerDvd = new DVD[1];
        (*dvd).setStatus(true);
        customerDvd[0] = *dvd;
        customerDVDSize++;
    }
    else{
        DVD* tempArr = new DVD[customerDVDSize+1];
        for(int i=0; i<customerDVDSize; i++){
            tempArr[i] = customerDvd[i];
        }
        (*dvd).setStatus(true);
        tempArr[customerDVDSize] = *dvd;
        delete[] customerDvd;

        customerDvd = tempArr;
        customerDVDSize++;
    }
    
}

void Customer::returnDVD(DVD* dvd){
    string returnSerialNum = (*dvd).getSerialNum();
    if(customerDVDSize==1){
        if(customerDvd[0].getSerialNum()==returnSerialNum){
            delete[] customerDvd;
            customerDvd = nullptr;
            customerDVDSize--;
            (*dvd).setStatus(false);
            
        }
    }
    else if(customerDVDSize >1 ){
        int index = -1;
        bool isFound = false;
        for(int i=0; i<customerDVDSize && !isFound; i++){
            if(customerDvd[i].getSerialNum()==returnSerialNum){
                index=i;
                isFound = true;
            }
        }
        if(isFound){
            DVD* tempArr = customerDvd;
            customerDvd = new DVD[customerDVDSize-1];
            cout<<"INDEX: "<<index<<endl;
            
            for(int i=0; i<index; i++){
                customerDvd[i] = tempArr[i];
            }
            for(int i=index+1; i< customerDVDSize; i++){
                customerDvd[i-1] = tempArr[i];
            }
            
            customerDVDSize--;
            (*dvd).setStatus(false);
            delete[] tempArr;
        }
    }
}
bool Customer::hasDVD(DVD* dvd){
    if(dvd != nullptr){
        for(int i=0; i<customerDVDSize; i++){
            if((customerDvd[i]).getSerialNum()==(*dvd).getSerialNum()){
                return true;
            }
        }
    }
    return false;
}

Customer& Customer::operator=(const Customer& right){
    if(right.id != id){
        id=right.id;
        name=right.name;
        if(customerDVDSize != right.customerDVDSize){
            
            if(customerDVDSize>0){
                delete[] customerDvd;
            }
            customerDVDSize = right.customerDVDSize;
            if(customerDVDSize>0){
                customerDvd = new DVD[customerDVDSize];
                for(int i=0; i< customerDVDSize; i++){
                    customerDvd[i] = right.customerDvd[i];
                }
            }
            else{
                customerDvd = nullptr;
            }
        }
        else{
            for(int i=0; i< customerDVDSize; i++){
                customerDvd[i] = right.customerDvd[i];
            }
        }
        

    }
    return *this;
}