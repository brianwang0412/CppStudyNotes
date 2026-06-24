#include<iostream>
#include<iomanip>
using namespace std;

class MyDate{
    friend istream& operator>>(istream& input, MyDate& Date){
        input>>setw(4)>>Date.year;
        input.ignore();
        input>>setw(2)>>Date.month;
        input.ignore();
        input>>setw(2)>>Date.day;
        return input;
    }

    friend ostream& operator<<(ostream& output, const MyDate& Date){
        cout<<setfill('0');
        cout<<setw(4)<<Date.year<<'/';
        cout<<setw(2)<<Date.month<<'/';
        cout<<setw(2)<<Date.day;
        return output;
    }
    
    private:
        int year, month, day;
    public:
        MyDate(){}
        MyDate(int y, int m, int d)
            :year{y}, month{m}, day{d}{}
};

class MyTime{
    friend istream& operator>>(istream& input, MyTime& Time){
        input>>setw(2)>>Time.hour;
        input.ignore();
        input>>setw(2)>>Time.minute;
        input.ignore();
        input>>setw(2)>>Time.second;
        return input;
    }

    friend ostream& operator<<(ostream& output, const MyTime& Time){
        output<<setfill('0');
        output<<setw(2)<<Time.hour<<':';
        output<<setw(2)<<Time.minute<<':';
        output<<setw(2)<<Time.second;
        return output;
    }
    
    private:
        int hour, minute, second;
    public:
        MyTime(){}
        MyTime(int h, int m, int s)
            :hour{h}, minute{m}, second{s}{}
};

class DateTime{
    private:
        MyTime Time;
        MyDate Date;
    public:
        DateTime(){}
        DateTime(MyDate d, MyTime t)
            :Date{d}, Time{t}{}
        
        void setDate(MyDate d){Date=d;}
        void setTime(MyTime t){Time=t;}
        
        MyDate getDate(){return Date;}
        MyTime getTime(){return Time;}

        void displayDateTime(){
            cout<<Date<<' '<<Time<<endl;
        }
};

int main(){
    MyDate D;
    MyTime T;
    cin>>D;
    cin>>T;

    DateTime DT;
    DT.setDate(D);
    DT.setTime(T);
    cout<<"Date: "<<DT.getDate()<<endl;
    cout<<"Time: "<<DT.getTime()<<endl;
    DT.displayDateTime();
    return 0;
}

/*
測資1
輸入:
2026/04/29
10:03:30

輸出:
Date: 2026/04/29
Time: 10:03:30
2026/04/29 10:03:30
*/

//Created by B.J.Wang 20260429
//最後更新 20260504