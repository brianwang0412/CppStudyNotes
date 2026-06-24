/*
題目:
蝸牛爬C公尺大樓
早上往上爬A公尺
晚上下滑B公尺
要爬幾天(或它是Fail Snail)
*/

#include<iostream>
using namespace std;

int main(){
    int A,B,C,height=0,days=0;
    cin >> A >> B >> C;

    while (true){
        height+=A;
        days++;
        if (height>=C) break;
        if (B>=A){
            cout<<"Fail Snail";
            return 0;
        }
        height-=B;
    }

    cout<<days;
    return 0;
}