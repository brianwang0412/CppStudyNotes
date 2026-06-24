#include<iostream>
using namespace std;


int main(){
    /*
    C++中唯一的三元運算子:
    變數 = 條件判斷式 ? 成立時要回傳的值 : 不成立時要回傳的值
    */
    //範例
    int a;
    bool Comp;
    cout << "Please input a number.>> ";
    cin >> a;
    Comp = a>6 ? 1 : 0; //如果a>6，就回傳1，否則回傳0
    cout << Comp << '\n';



    //簡易終極密碼小遊戲
    int Ans=9,input;
    cout << "Game start.\n";
    while (true){
        cout << "1~10,guess which is the answer.>> ";
        cin >> input;
        if (input==Ans? true:false){ //如果input==Ans，則回傳true，否則回傳false
            cout << "Good Job, the answer is "<<Ans<<'\n';
            break;
        }
        else cout << "Wrong, answer is not " << input <<'\n';
    }
    cout << "Game over.\n";
}

//本篇筆記參考《徹底研究最新C++物件導向程式設計實例》3-18~3-20
//Create by B.J.Wang 2025/9/25