#include<iostream>
using namespace std;

void hanoi(int n, char A, char B, char C){
    if (n==1) cout<<"Move ring "<<n<<" from "<<A<<" to "<<C<<endl;
    else{
        hanoi(n-1,A,C,B);
        cout<<"Move ring "<<n<<" from "<<A<<" to "<<C<<endl;
        hanoi(n-1,B,A,C);
    }
}

int main(){
    int n;
    while (cin>>n){
        hanoi(n,'A','B','C');
        cout<<'\n';
    }
}

//Created by B.J.Wang 20260527