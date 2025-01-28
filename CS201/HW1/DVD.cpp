/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#include <iostream>
#include "DVD.h"

using namespace std;

DVD::DVD(){
    status = "Available";
    serialNum = "default";
    title="default";
    director = "default";
}
DVD::DVD(string serialNo, string title, string director): serialNum(serialNo), title(title), director(director) {
    status = "Available";
}
bool DVD::operator==(const DVD& dvd) const{
    if(&dvd != this){
        if(dvd.serialNum == serialNum){
            return true;
        }
    }
    return false;
}
/*DVD& DVD::operator=(DVD& dvd){
    if(&dvd != this){
        serialNum = (dvd).getSerialNum();
        title = dvd.getTitle();
        status = dvd.getStatus();
        director = dvd.getDirector();
    }
    return *this;
}*/

string DVD::getSerialNum(){
    return serialNum;
}

string DVD::getTitle(){
    return title;
}

string DVD::getDirector(){
    return director;
}

string DVD::getStatus(){
    return status;
}

void DVD::setStatus(bool isRented){
    if(isRented){
        status = "Rented";
    }
    else{
        status = "Available";
    }
}
