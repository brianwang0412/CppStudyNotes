#include<iostream>
#include<string> //非常好用的字串
using namespace std;

int main(){
    //《string的宣告》

    string S1="abcde"; //建立一個字串S1，資料型別為string，初始值為"abcde"
    //★可以將S1視為一個「陣列」{'a','b','c','d','e'}
    //此時，S1[0]即為S1中的第一個元素'a'
    //同理，S1[5]的值為'e'

    string S2(S1,1,4); //建立一個字串S2，資料型別為string，初始值為S1[1]~S1[4]
    //即S2={S1[1],S1[2],S1[3],S1[4]}
    //也就是S2={'b','c','d','e'}

    string S3(6,'a'); //建立一個字串S3，資料型別為string，初始值為6個'a'組合起來
    //即S3={'a','a','a','a','a','a'}

    cout << "S1 = " << S1 <<endl; //輸出: S1 = abcde
    cout << "S2 = " << S2 <<endl; //輸出: S2 = bcde
    cout << "S3 = " << S3 <<endl; //輸出: S3 = aaaaaa

    cout<<"=================="<<'\n';//分隔線
/*
    //《getline輸入》
    string A;
    cout << "Say something>> ";
    getline(cin,A); //輸入: I love C++
    cout << A <<endl; //輸出: I love C++
    //getline會將一整行的輸入(包括空格)全部存進變數內
    //不像cin遇到空格就結束

    cout<<"=================="<<'\n';//分隔線


    //《用迴圈存取string & 取得string的長度》
    string B="HZelZlo ZWorZld";
    //我在"Hello World"中參雜了許多Z
    //輸出的時候要判斷該字元是否非Z
    for (int i=0;i<B.size();i++){ //用 變數.size() 來取得字串的長度
        if (B[i]!='Z') cout<<B[i];
    }
    //輸出: Hello World
*/
    cout<<"=================="<<'\n';//分隔線

    string C="Hello World";
    cout<<C.length();
}

//Created by B.J.Wang 2025/11/6