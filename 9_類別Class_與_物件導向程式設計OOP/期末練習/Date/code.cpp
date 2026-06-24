#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

//作答區開始
class Date{
    private:
        int mYear, mMonth, mDay;
    public:
        Date(){
            mYear=2000;
            mMonth=1;
            mDay=1;
        }
        Date(int year, int month, int day) : mYear(year), mMonth(month), mDay(day){}
        
        void setYear(int y){mYear=y;}
        void setMonth(int m){mMonth=m;}
        void setDay(int d){mDay=d;}
        
        int getYear(){return mYear;}
        int getMonth(){return mMonth;}
        int getDay(){return mDay;}
        
        int M[13]={31,31,28,31,30,31,30,31,31,30,31,30,31};
        void leap(){
            if ((mYear%400==0) || (mYear%4==0 && mYear%100!=0))
                M[2]=29;
            else
                M[2]=28;
        }
        
        void addTool(){
            bool change=true;
            while (change){
                leap();
                change=false;
                if (mDay>M[mMonth]){
                    mDay-=M[mMonth];
                    mMonth+=1;
                    change=true;
                }
                if (mMonth==13){
                    mMonth=1;
                    mYear+=1;
                    change=true;
                }
            }
        }
        
        void addWeeks(int w){
            mDay+=w*7;
            addTool();
        }
        void addDays(int d){
            mDay+=d;
            addTool();
        }
        
        void subTool(){
            bool change=true;
            while (change){
                change=false;
                leap();
                if (mDay<=0){
                    mDay+=M[mMonth-1];
                    mMonth-=1;
                    change=true;
                }
                if (mMonth==0){
                    mMonth=12;
                    mYear-=1;
                    change=true;
                }
                if (mYear<=0){
                    mYear=0;
                    mMonth=0;
                    mDay=0;
                    break;
                }
            }
        }
        void subWeeks(int w){
            mDay-=w*7;
            subTool();
        }
        void subDays(int d){
            mDay-=d;
            subTool();
        }
        
        string displayDate(){
            stringstream output;    
            output<<setfill('0')
                <<setw(4)<<mYear<<'/'
                <<setw(2)<<mMonth<<'/'
                <<setw(2)<<mDay;
            return output.str();
        }
};
//作答區結束

int main() {
    int y1, m1, d1v;
    int y2, m2, d2v;
    int addW, addD, subW, subD;

    cin >> y1 >> m1 >> d1v >> y2 >> m2 >> d2v >> addW >> addD >> subW >> subD;

    Date d1;
    d1.setYear(y1);
    d1.setMonth(m1);
    d1.setDay(d1v);

    Date d2(y2, m2, d2v);

    cout << "Date 1: " << d1.displayDate() << endl;
    cout << "Date 2: " << d2.displayDate() <<  endl;

    d2.addWeeks(addW);
    cout << "After addWeeks: " << d2.displayDate() << endl;

    d2.addDays(addD);
    cout << "After addDays: " << d2.displayDate() << endl;

    d2.subWeeks(subW);
    cout << "After subWeeks: " << d2.displayDate() << endl;

    d2.subDays(subD);
    cout << "After subDays: " << d2.displayDate() << endl;

    return 0;
}

// 本篇筆記為嘉義大學資訊工程學系物件導向程式設計之課堂題目
// //Created by B.J.Wang 20260609