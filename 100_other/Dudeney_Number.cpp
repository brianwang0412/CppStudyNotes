//課本P315 6.28 Dudeney Numbers
//Dudeney Number是一個完全立方正整數，它的各位數字和等於它的立方根。

#include<iostream>
#include<cmath>
using namespace std;

bool f(double n){
    double CR=cbrt(n); //cbrt(n)代表取n的立方根，而 CR^3=n
    int N=n,sum=0;

    //取所有位數之和
    while (N!=0){
        sum+=N%10;
        N/=10;
    }

    if (CR==(double)sum) return true;
    else return false;
}

int main(){
    double i=0;
    int count=0;
    while (count<7){
        if (f(i)){
            count++;
            cout<<i<<endl;
        }
        i++;
    }
}

/*
輸出:
0
1
512
4913
5832
17576
19683
*/