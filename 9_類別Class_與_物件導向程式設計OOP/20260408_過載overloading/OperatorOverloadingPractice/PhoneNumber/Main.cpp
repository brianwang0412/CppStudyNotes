#include<iostream>
#include "PhoneNumber.h"
using namespace std;

int main(){
    PhoneNumber phone;

    cout<< "Enter phone number in the form (123) 456-7890:"<<endl;

    cin>>phone;

    cout<<"\nThe phone number entered was:\n";
    cout<<phone<<endl;
}

/*
範例輸入與輸出:
Enter phone number in the form (123) 456-7890:
(123) 456-7890

The phone number entered was:
Area code: 123
Exchange: 456
Line: 7890
(123) 456-7890
*/