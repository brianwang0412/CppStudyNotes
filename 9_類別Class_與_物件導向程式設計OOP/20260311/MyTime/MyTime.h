//MyTime.h : 這個Class「可以做什麼」

#include<string>
using namespace std;

#ifndef MYTIME_H

#define MYTIME_H

class MyTime{
    private:
        unsigned int hour = 0;
        unsigned int minute = 0;
        unsigned int second = 0;
    public:
        MyTime();
        MyTime(int h, int m, int s);

        void setTime(int ,int ,int);
        std::string toUniversalString() const;
        std::string toStandardString() const;
        void setHour(int);
        void setMinute(int);
        void setSecond(int);
        unsigned int getHour() const;
        unsigned int getMinute() const;
        unsigned int getSecond() const; 
};

#endif