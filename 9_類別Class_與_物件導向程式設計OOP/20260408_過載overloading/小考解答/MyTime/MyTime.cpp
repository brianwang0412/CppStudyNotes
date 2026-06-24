#include<iostream>
#include<iomanip>
using namespace std;


class MyTime{
    private:
        int hour, minute, second;
    public:
        void setHour(int h){
            if (h>=0&&h<=23)
                hour=h;
            else
                hour=0;
        }
        void setMinute(int m){
            if (m>=0&&m<=59)
                minute=m;
            else
                minute=0;
        }
        void setSecond(int s){
            if (s>=0&&s<=59)
                second=s;
            else
                second=0;
        }

        int getHour(){ return hour; }
        int getMinute(){ return minute; }
        int getSecond(){ return second; }

        void show24Hour(){
            cout<<"24-hour format: "<<setfill('0')
                <<setw(2)<<hour<<':'
                <<setw(2)<<minute<<':'
                <<setw(2)<<second<<endl;
        }

        void show12Hour(){
            cout<<"12-hour format: "<<setfill('0')
                <<setw(2)<<(hour>12? hour-12:(hour==0?12:hour))<<':'
                <<setw(2)<<minute<<':'
                <<setw(2)<<second<<' '
                <<(hour<12? "AM":"PM")<<endl;
        }
};

//Created by B.J.Wang 0408