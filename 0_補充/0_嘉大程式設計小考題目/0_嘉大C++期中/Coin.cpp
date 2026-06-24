/*
N元
用1,5,10,50,100組合
*/

#include<iostream>
using namespace std;

int main(){
    int num;
    cin >> num;
    int dp[num+1]={0};
    int coins[5]={1,5,10,50,100};
    dp[0]=1;
    for (int i=0;i<5;i++){
        for (int j=coins[i];j<=num;j++){
            dp[j] += dp[j-coins[i]];
        }
    }
    cout <<dp[num];
}