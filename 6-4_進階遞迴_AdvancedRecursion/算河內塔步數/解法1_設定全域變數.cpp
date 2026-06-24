#include<iostream>
using namespace std;

int step=0;
//設定全域變數step，讓它在main()跟hanoi()內都可以被呼叫(存取)

void hanoi(int n, char A, char B, char C){
    if (n==1){
        //cout <<"Disk "<< n <<" from "<< A <<" to "<< C <<endl;
        step++; //移動第1個圓盤
    }
    else{
        hanoi(n-1,A,C,B);
        //cout <<"Disk "<< n <<" from "<< A <<" to "<< C <<endl;
        step++; //移動第n個圓盤
        hanoi(n-1,B,A,C);
    }
}

int main(){
    hanoi(3,'a','b','c');
    cout<<"Total step = "<<step<<endl; //輸出: Total step = 7
}

//Created by B.J.Wang 2025/11/19