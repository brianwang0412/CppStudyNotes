#include "Date.h"
#include<iostream>
#include<string>
using namespace std;

const array<unsigned int, 13> Date::days{0,31,28,31,30,31,30,31,31,30,31,30,31};

Date::Date(int month, int day, int year){
    setDate(month, day, year);
}

void Date::setDate(int m, int d, int y){
    if (m>=1 && m<=12) month = m;
    else throw invalid_argument("Month must be 1-12");

    if (y>=1900 && y<=2100) year = y;
    else throw invalid_argument("Year must be >= 1900 and <= 2100");

    if ((month==2 && leapYear(year) && d>=1 && d<=29) || (d>=1 && d<=days[month])) day=d;
    else throw invalid_argument("Day us out of range for current month and year");
}

Date& Date::operator++(){
    helpIncrement();
    return *this;
}

Date Date::operator++(int){
    Date temp{*this};
    helpIncrement();
    return temp;
}

Date& Date::operator+=(unsigned int additionalDays){
    for (unsigned int i=0; i<additionalDays; ++i){
        helpIncrement();
    }
    return *this;
}

bool Date::leapYear(int testYear){
    //OR的優先級高於AND
    return ((testYear%400==0) || (testYear%4==0)&&(testYear%100!=0));
}

bool Date::endOfMonth(int testDay) const{
    if (month==2 && leapYear(year)) return testDay==29;
    else return testDay==days[month];
}

void Date::helpIncrement(){
    if (!endOfMonth(day)) ++day;
    else if (month<12){
        ++month;
        day = 1;
    }
    else{
        ++year;
        month=1;
        day=1;
    }
}

ostream& operator<<(ostream& output, const Date& d){
    static string monthName[13]{"", "January", "February", "March", "April", 
        "May", "June", "July", "August", "September", "October", "November", "December"};
    
    output<< monthName[d.month] << ' '<< d.day << ", " << d.year;
    return output;
}