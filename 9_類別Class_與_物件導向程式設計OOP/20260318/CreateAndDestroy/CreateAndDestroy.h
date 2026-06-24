#include<string>
using namespace std;

#ifndef CREATEANDDESTROY_H
#define CREATEANDDESTROY_H

class CAD{    
public:
    CAD(int, string);
    ~CAD();
private:
    int objectID;
    string message;
    int count;
};

#endif