#include<iostream>
#include<stdexcept>
#include"MyTime.h"
using namespace std;

void displayTime(const string &message, const MyTime &time){
    cout<< message << "\nUniversal time: " << time.toUniversalString() << "\nStandard time: " << time.toStandardString() << "\n\n";
}


int main(){
    MyTime t;
    displayTime("Initial time:", t);
    t.setTime(13, 27 ,6);
    displayTime("After setTime:", t);
    
    try{
        t.setTime(99, 99, 99);
    }
    catch (invalid_argument &e){
        cout << "Exception: " << e.what() << "\n\n";
    }

    displayTime("After attempting to set invalid time:", t);
    return 0;
}