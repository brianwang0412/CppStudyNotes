/*
題目:
給你兩重疊方形，給定左下與右上角的座標，求重疊面積
*/


#include<iostream>
using namespace std;

int main(){
    int X[4],Y[4];
    for (int i=0;i<4;i++){
        cin >> X[i] >> Y[i];
    }

    int Ans[4];
    Ans[0]=max(X[0],X[2]);
    Ans[1]=max(Y[0],Y[2]);
    Ans[2]=min(X[1],X[3]);
    Ans[3]=min(Y[1],Y[3]);

    cout << (Ans[2]-Ans[0]) * (Ans[3]-Ans[1])<<endl;
    return 0;
}