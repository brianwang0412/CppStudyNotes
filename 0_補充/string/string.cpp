#include<iostream>
#include<string>
using namespace std;

int main(){
    string sentense;
    cout << "Please input a sentense.>> ";
    getline(cin,sentense); 
    cout << "I get it, you just said: " << sentense << '\n';
    //getline可以儲存整串字串(包含空格)，例如輸入Very Good，G可以完整接收到Very Good
    //但是!getline不能跟cin混用，cin輸入結束後會暫存一個換行符號，getline檢測到換行符號會直接結束輸入

    /*
    範例輸入與輸出
    Please input a sentense.>> today is a sunny day.
    I get it, you just said: today is a sunny day.
    */
    return 0;
}

//Create by B.J.Wang 2025/9/25