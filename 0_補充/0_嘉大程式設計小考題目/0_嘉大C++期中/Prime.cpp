/*
題目:
判斷兩數間有幾個質數
*/

#include<iostream>
using namespace std;

bool isPrime(int num){
    if (num<=1) return false;
    if (num==2) return true;
    for (int i=2;i<=num/2;i++){
        if (num%i==0) return false;
    }
    return true;
}

int main(){
    int A,B,count=0;
    cin >> A >> B;
    
    for (int i=A;i<=B;i++){
        if (isPrime(i)) count++;
    }
    cout << count;
}