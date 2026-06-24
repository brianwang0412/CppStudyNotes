#include<iostream>
using namespace std;

int main(){
    //break: 立即跳出當前迴圈

    int num,sum=0; //宣告兩個整數變數，num用來接收輸入，sum用來儲存數字總和
    cout << "Enter 0 to quit\n"; 
    while (true){ //無限迴圈
        cout << "Please input a number>> ";
        cin >> num; //將輸入的數值存入num變數內
        if (num==0) break; //若num的數值為零，就跳出迴圈
        else sum = sum + num; //否則將sum與num相加，並將結果賦值給sum，達成將sum原本的值「加上」num的值
    }
    cout <<"Sum of number= "<< sum <<endl;
    /*
    範例輸入與輸出
    Enter 0 to quit
    Please input a number>> 1
    Please input a number>> 3 
    Please input a number>> 5
    Please input a number>> 0
    Sum of number= 9
    */
    /*
    程式功能
    這個程式會一用num直接收使用者輸入的數字
    接收到後先檢測num是否為0，若為0則跳出迴圈，否則將sum的值加上num的值
    最收輸出總和sum
    */

    //注意:若有兩層迴圈，則在第二層迴圈使用break只會回到第一層迴圈，不會直接跳出兩層迴圈

    cout<<"=================="<<'\n';//分隔線
    
    //continue: 跳過該次迴圈

    for (int Number=0;Number<10;Number++){
        if (Number%2==0) continue; //若Number餘除2==0(是2的倍數)，就跳過這次迴圈，進入下一次迴圈
        cout << Number << " ";
    }
    //輸出: 1 3 5 7 9
    /*
    程式功能
    這個程式會讓Number從0加到9，但若檢測到Number可以被2整除(是偶數)，就跳過這次迴圈
    達成輸出0~9的所有奇數的功能
    */
}
//Create by B.J.Wang 2025/10/3