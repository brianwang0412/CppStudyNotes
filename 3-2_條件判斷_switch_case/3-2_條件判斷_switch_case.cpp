#include<iostream>
using namespace std;

int main(){
    /*
    switch(你的變數){
        case 判斷值1:
            程式A
            break;
        case 判斷值2:
            程式B
            break;
        .
        .
        .
        default:
            程式C
    }

    當"你的變數"等於"判斷值1"時，就會執行程式A
    若是都沒有符合的判斷值，則跳到default，執行程式C
    此外case每一個case內都要寫一個break，這樣才能跳出switch
    若沒寫，會繼續跑下面case裡面的程式，直到遇到break或跑完default才會終止
    */
    int num1;
    cout << "1~3, choose a number.>> ";
    cin >> num1;
    switch (num1){
        case 1:
            cout << "You input 1, give you 1 hamburger.\n";
            break;
        case 2:
            cout << "You input 2, give you 2 cookies.\n";
            break;
        case 3:
            cout << "You input 3, give you 3 Coke Cola\n";
            break;
        default:
            cout << "Your input number not in 1~3\n";
    }    
    /*
    實際輸入與輸出
    1~3, choose a number.>> 2
    You input 2, give you 2 cookie.
    */

    cout<<"=================="<<'\n';//分隔線

    /*
    switch (你的變數){
        case 判斷值1: case 判斷值2:
            程式A;
            break;
        case 判斷值3: case 判斷值4:
            程式B;
            break;
        .
        .
        .
        default:
            程式C;
    }

    可以讓多個判斷值執行相同的程式
    如上，若你的變數等於判斷值1或判斷值2，則皆會執行程式A
    */

    int num2;
    cout << "1~10,choose a number.>> ";
    cin >> num2;
    switch (num2){
        case 1: case 3: case 5: case 7: case 9:
            cout << "Your number " << num2 << " is a odd number.\n"; //奇數
            break;
        case 2: case 4: case 6: case 8: case 10:
            cout << "Your number " << num2 << " is a even number.\n"; //偶數
            break;
        default:
            cout << "Your input number not in 1~10\n";
    }
    /*
    範例輸入與輸出
    1~10,choose a number.>> 9
    Your number 9 is a odd number.
    */
}

//本篇筆記參考《徹底研究最新C++物件導向程式設計實例》4-23~4-29
//Create by B.J.Wang 2025/9/25