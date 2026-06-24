#include<iostream>
#include<cmath>
using namespace std;

//解 n 層河內塔的最少步數為 2^n-1

int main(){
    int n;
    cout<<"How many layers? >>";
    cin >> n;
    cout<<"Total step = "<< pow(2,n)-1 <<endl;
}

/*
How many layers? >>3
Total step = 7
*/

//Created by B.J.Wang 2025/11/19