#include<iostream> //.begin() & .end()
#include<string> //to_string() & stoi()
#include<algorithm> //reverse()
using namespace std;

int int_reverse(int num){
    string r_num = to_string(num); //將num從「int轉換成strin」存進r_num中
    reverse(r_num.begin(), r_num.end()); //將r_num前後反轉，使用.begin()與.end()來定位開頭與結尾
    num = stoi(r_num);
    return num;
     //將r_num從「string轉換成int」，並回傳
}

int main(){
    int num;
    cout<< "Enter a number>> ";
    cin >> num;
    cout<< int_reverse(num)<<endl;
}

/*
輸入與輸出: 
範例一
輸入: 012345
輸出: 54321

範例二
輸入: 33550336
輸出: 63305533
*/

//Created by B.J.Wang 2025/11/18