#include<iomanip>
#include<iostream>
using namespace std;

class MyDate{
    private:
        int mYear,mMonth,mDay;
    public:
        MyDate():mYear{2000},mMonth{1},mDay{1}{};
        MyDate(int y, int m, int d):mYear{y},mMonth{m},mDay{d}{};
    
        void setYear(int y){mYear=y;}
        void setMonth(int m){mMonth=m;}
        void setDay(int d){mDay=d;}
    
        int getYear(){return mYear;}
        int getMonth(){return mMonth;}
        int getDay(){return mDay;}
};
    
class MyTime{
    private:
        int mHour,mMinute,mSecond;
    public:
        MyTime():mHour{0},mMinute{0},mSecond{0}{};
        MyTime(int h, int m, int s):mHour{h},mMinute{m},mSecond{s}{};

        void setHour(int h){mHour=h;}
        void setMinute(int m){mMinute=m;}
        void setSecond(int s){mSecond=s;}

        int getHour(){return mHour;}
        int getMinute(){return mMinute;}
        int getSecond(){return mSecond;}
};

class DateTime{
    private:
        MyDate mDate;
        MyTime mTime;
    public:
        DateTime(MyDate d, MyTime t):mDate{d},mTime{t}{};

        void setDate(MyDate d){mDate=d;}
        void setTime(MyTime t){mTime=t;}

        MyDate getDate(){return mDate;}
        MyTime getTime(){return mTime;}

        void DisplayDateInfo(){
            cout<<setfill('0')<<setw(4)<<mDate.getYear()<<'/'<<setw(2)<<mDate.getMonth()<<'/'<<setw(2)<<mDate.getDay()
                <<' '<<setw(2)<<mTime.getHour()<<':'<<setw(2)<<mTime.getMinute()<<':'<<setw(2)<<mTime.getSecond()<<endl;
        }
};