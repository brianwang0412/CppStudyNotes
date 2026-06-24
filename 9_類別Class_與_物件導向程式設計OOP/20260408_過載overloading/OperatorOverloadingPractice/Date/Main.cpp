#include "Date.h"
#include<iostream>
using namespace std;

int main(){
    Date d1{12, 27, 2010};
    Date d2;

    cout<< "d1 is " << d1<<endl;
    cout<< "d2 is " << d2<<endl;
    cout<< "d1 += 7 is " << (d1+=7) <<'\n'<<endl;

    d2.setDate(2,28,2008);
    cout<< "  d2 is " <<d2<<endl;
    cout<< "++d2 is " <<++d2<< " (leap year allows 29th)"<<'\n'<<endl;

    Date d3{7,13,2010};
    cout<< "Testing the prefix increment operator:"<<endl;
    cout<< "  d3 is " << d3 <<endl;
    cout<< "++d3 is " << ++d3 <<endl;
    cout<< "  d3 is " << d3 <<'\n'<<endl;

    cout<< "Testing the postfix increment operator:"<<endl;
    cout<< "d3 is " << d3 <<endl;
    cout<< "d3++ is " << d3++ <<endl;
    cout<< "d3 is " << d3 <<endl;


    /*
    d1 is December 27, 2010
    d2 is January 1, 1900
    d1 += 7 is January 3, 2011

    d2 is February 28, 2008
    ++d2 is February 29, 2008 (leap year allows 29th)

    Testing the prefix increment operator:
    d3 is July 13, 2010
    ++d3 is July 14, 2010
    d3 is July 14, 2010

    Testing the postfix increment operator:
    d3 is July 14, 2010
    d3++ is July 14, 2010
    d3 is July 15, 2010
    */
}