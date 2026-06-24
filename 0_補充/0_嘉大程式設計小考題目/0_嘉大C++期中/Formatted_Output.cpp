/*
就輸出而已
*/

#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

int main(){
    cout << setw(10) << left << "Name"
        << setw(10) << right << "Price"
        << setw(10) << right << "Days"
        << setw(10) << right << "Total" <<endl;

    string name;
    double price;
    int days;
    
    for (int i=0;i<3;i++){
        cin >> name >> price >> days;
        
        cout << fixed << setprecision(2);
        cout << setw(10) << left << name
            << setw(10) << right << price
            << setw(10) << right << days
            << setw(10) << right << price*days <<endl;
    }
}