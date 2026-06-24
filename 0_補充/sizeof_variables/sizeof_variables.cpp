#include<iostream>
#include<string>
using namespace std;

int main(){
    cout << "sizeof of int : " << sizeof(int) << '\n';
    cout << "sizeof of long : " << sizeof(long) << '\n';
    cout << "sizeof of long long : " << sizeof(long long) << '\n';
    cout << "sizeof of unsigned  int : " << sizeof(unsigned int) << '\n';
    cout << "sizeof of unsigned long : " << sizeof(unsigned long) << '\n';
    cout << "sizeof of unsigned long long : " << sizeof(unsigned long long) << '\n';
    cout << "sizeof of float : " << sizeof(float) << '\n'; //no unsigned
    cout << "sizeof of double : " << sizeof(double) << '\n'; //no unsigned
    cout << "sizeof of long double : " << sizeof(long double) << '\n'; //no unsigned
    cout << "sizeof of char : " << sizeof(char) << '\n';
    cout << "sizeof of unsigned char : " << sizeof(unsigned char) << '\n';
    cout << "sizeof of bool : " << sizeof(bool) << '\n'; //no unsigned
    cout << "sizeof of string : " << sizeof(string) << '\n'; //no unsigned
    return 0;
}

/*
sizeof of int : 4
sizeof of long : 4
sizeof of long long : 8
sizeof of unsigned  int : 4
sizeof of unsigned long : 4
sizeof of unsigned long long : 8
sizeof of float : 4
sizeof of double : 8
sizeof of long double : 12
sizeof of char : 1
sizeof of unsigned char : 1
sizeof of bool : 1
sizeof of string : 24
*/

//本篇筆記為嘉義大學資訊工程學系許政穆教授的授課內容
//Create by B.J.Wang 2025/9/25