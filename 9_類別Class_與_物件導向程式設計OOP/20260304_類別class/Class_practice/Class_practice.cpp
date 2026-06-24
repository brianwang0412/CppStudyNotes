//C++ How to program P141 3-12

#include<iostream>
using namespace std;

class Date{
    private:
        int month;
        int day;
        int year;
    
    public:
        Date(){}
        Date(int Ini_month, int Ini_day, int Ini_year){
            if (Ini_month>=1 && Ini_month<=12)
                month = Ini_month;
            else 
                month = 1;
            day = Ini_day;
            year = Ini_year;
        }
        
        /*
        Date(int Ini_month, int Ini_day, int Ini_year)
            :month{(Ini_month>=1 && Ini_month<=12) ? Ini_month : 1},
             day{Ini_day},
             year{Ini_year}{}
        */

        void setMonth(int Month){
            if (Month>=1 && Month<=12)
                month = Month;
            else
                month = 1;
            
            //month = (Month>=1 && Month<=12) ? Month : 1;
        }
        void setDay(int Day){
            day = Day;
        }
        void setYear(int Year){
            year = Year;
        }

        int getMonth() const{
            return month;
        }
        int getDay() const{
            return day;
        }
        int getYear() const{
            return year;
        }

        void displayDate() const{
            cout<<month<<'/'<<day<<'/'<<year<<endl;
        }

};


int main(){
    Date MyBirth{99,12,2007};
    MyBirth.displayDate(); //輸出: 1/12/2007


    Date ADay;
    ADay.setMonth(999);
    ADay.setDay(21);
    ADay.setYear(2006);
    int a=ADay.getMonth(), b=ADay.getDay(), c=ADay.getYear();
    cout<< a <<' '<<b<<' '<<c<<endl; //輸出: 1 21 2006
    ADay.displayDate(); //輸出: 1/21/2006

    Date ADay2{10,21,2006};
    ADay2.displayDate(); //輸出: 10/21/2006

}

//Created by B.J.Wang 2026/3/9