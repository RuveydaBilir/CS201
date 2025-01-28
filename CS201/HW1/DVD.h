/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#ifndef __DVD_H
#define __DVD_H

#include <iostream>
using namespace std;

class DVD{
public:
    DVD();
    DVD(string, string, string);
    bool operator==(const DVD&) const; 
    string getSerialNum();   
    string getTitle();
    string getDirector();
    string getStatus();
    void setStatus(bool isRented);
private:
    string serialNum;
    string title;
    string director;
    string status;
};

#endif