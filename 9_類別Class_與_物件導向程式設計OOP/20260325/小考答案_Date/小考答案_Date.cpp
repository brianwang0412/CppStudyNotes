#include<sstream>
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;
//OOP第一次小考參考答案_已AC

class Date{
private:
    int mYear, mMonth, mDay;

public:
    int MonthCount[13] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    Date() : mYear{2000}, mMonth{1}, mDay{1} {};
    Date(int y, int m, int d) : mYear{y}, mMonth{m}, mDay{d} {};

    void setYear(int y) { mYear = y; }
    void setMonth(int m) { mMonth = m; }
    void setDay(int d) { mDay = d; }

    int getYear() { return mYear; }
    int getMonth() { return mMonth; }
    int getDay() { return mDay; }

    void isLeapYear() {
        if (((mYear % 400 == 0) || ((mYear % 4 == 0) && (mYear % 100 != 0))))
            MonthCount[2] = 29;
        else
            MonthCount[2] = 28;
    }

    void addTool() {
        bool change = true;
        isLeapYear();
        while (change) {
            change = false;
            if (mDay > MonthCount[mMonth]) {
                mDay -= MonthCount[mMonth];
                mMonth++;
                change = true;
            }
            if (mMonth > 12) {
                mMonth -= 12;
                mYear++;
                change = true;
            }
        }
    }

    void addWeeks(int w) {
        mDay += w * 7;
        addTool();
    }

    void addDays(int d) {
        mDay += d;
        addTool();
    }

    void subTool() {
        bool change = true;
        isLeapYear();
        while (change) {
            change = false;
            if (mDay <= 0) {
                mDay += MonthCount[mMonth-1];
                mMonth--;
                change = true;
            }
            if (mMonth <= 0) {
                mMonth += 12;
                mYear--;
                change = true;
            }
        }
        if (mYear <= 0) {
            setYear(0);
            setMonth(0);
            setDay(0);
        }
    }

    void subWeeks(int w) {
        mDay -= w * 7;
        subTool();
    }

    void subDays(int d) {
        mDay -= d;
        subTool();
    }

    string displayDate() {
        stringstream output;
        output << setfill('0') << setw(4) << mYear << '/' 
               << setw(2) << mMonth << '/' << setw(2) << mDay;
        return output.str();
    }
};

//常錯地方: 第0年應被視為不正常，因此當mYaer<=0時，就該將年月日都設為0/0/0

//Created by B.J.Wang 20260406