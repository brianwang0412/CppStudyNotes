#include<iostream>
using namespace std;

int main(){
    int N,T=0;
    cin >> N;
    while (N>=24){
        T += 400;
        cout << "收您400元，現在總金額為: " <<T<<endl;

        N -= 24;
        cout << "這裡是您的24瓶汽水，請拿好，你還需要買: " << N <<"瓶" <<endl;
    }
    T += N*20;
    cout << T;
}

int main(){
    int N;
    cout << ((N/24)*400) + ((N%24)*20);
}