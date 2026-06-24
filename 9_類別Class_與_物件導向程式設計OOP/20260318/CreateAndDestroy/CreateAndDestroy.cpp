#include"CreateAndDestroy.h"
#include<string>
#include<iostream>
using namespace std;

//用class的name
CAD::CAD(int id, string msg):objectID(id), message(msg){
    count++;
    cout<< "Object "<<objectID<<"   constructor runs   "<<message<<endl;
}

CAD::~CAD(){
    cout<< (objectID == 1 || objectID == 6 ? "\n" : "");
    cout<< "Object "<<objectID<<"   destructor runs   "<<message<<endl;
}