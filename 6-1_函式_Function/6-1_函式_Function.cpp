#include<iostream>
#include<string>
using namespace std;

/*
函式語法

回傳值的變數型別 自訂函式名稱(輸入值的變數型別 自訂變數名稱){
    程式;
    return 變數;
}

int Func(int num){
    program;
    return int;
}

void Func2(int[] Arr){
    program;
}

void代表不回傳值(不用寫retrun)
*/

int Add(int num1, int num2){
    int Result;
    Result = num1 + num2;
    return Result;
}
/*
建立一個函式Add，回傳值型別為int，代表最後要回傳一個數值
引入兩個參數num1,num2，皆為int
函式內宣告一個int變數Result
將num1+num2賦值給Result
回傳Result

這樣當我們執行A=Add(1,2);
A就會接收到回傳值的3
*/

void SayHi(string name){
    cout << "Hello " <<name<<endl;
}
/*
建立一個函式SayHi，回傳值型別為void，代表不會有回傳值
引入一個string參數 name
輸出 cout << "Hello " <<name<<endl;

這樣當我們執行SayHi("Lu Zi Qiang")
就會輸出: Hello Lu Zi Qiang
*/

int main(){
    int A=Add(100,99);
    cout<< A <<endl; //輸出: 199
    SayHi("Li Long Sheng"); //輸出: Hello Li Long Sheng
}

//Created by B.J.Wang 2025/11/6