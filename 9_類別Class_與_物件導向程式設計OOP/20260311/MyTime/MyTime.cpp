//MyTime.cpp : 這個Class「怎麼運作」

#include"MyTime.h"
#include<iomanip>
#include<stdexcept>
#include<sstream>
#include<string>

using namespace std;

void MyTime::setHour(int h){
    if (h >= 0 && h < 24){
        hour = h;
    }
    else{
        throw invalid_argument("hour was out of range");
    }
}
void MyTime::setMinute(int m){
    if (m >= 0 && m < 60){
        minute = m;
    }
    else{
        throw invalid_argument("minute was out of range");
    }
}
void MyTime::setSecond(int s){
    if (s >= 0 && s < 60){
        second = s;
    }
    else{
        throw invalid_argument("second was out of range");
    }
}
unsigned int MyTime::getHour() const{
    return hour;
}
unsigned int MyTime::getMinute() const{
    return minute;
}
unsigned int MyTime::getSecond() const{
    return second;
}


void MyTime::setTime(int h, int m, int s){
    setHour(h);
    setMinute(m);
    setSecond(s);
    /*
    if ( (h >= 0 && h < 24) && (m >= 0 && m < 60) && (s >= 0 && s < 60) ){
        hour = h;
        minute = m;
        second = s;
    }
    else{
        throw invalid_argument("hour, minute and/or second was out of range");
    }
    */
}

string MyTime::toUniversalString() const{
    ostringstream output;
    output << setfill('0') << setw(2) << hour << ":" << setw(2) << minute << ":" << setw(2) << second;
    return output.str();
}

string MyTime::toStandardString() const{
    ostringstream output;
    output<< ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":" << setw(2) << setfill('0') 
    << minute << ":" << setw(2) << second << (hour < 12 ? "AM" : "PM");
    return output.str();
}

//constructor
MyTime::MyTime(){};
MyTime::MyTime(int h, int m, int s){
    setTime(h, m, s);
}