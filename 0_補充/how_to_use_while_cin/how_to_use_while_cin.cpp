#include<iostream>
using namespace std;

int main(){
    int x;
    cout << "Start Input>> ";
    while (cin >> x){ 
    //cin輸入成功(正確輸入int)->true，執行迴圈內容
    //若cin輸入失敗(輸入的並非int，若終止輸入，若以讀取檔案結尾(EOF))->false，跳出while迴圈
        cout << "You Enter is " << x << '\n';
        cout << "Continue Input>> ";
    }
}

//Create by B.J.Wang 2025/9/19