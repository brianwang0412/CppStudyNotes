/*
題目:
輸出字串的每個英文字個數
*/

#include<iostream>
#include<string>
using namespace std;

int main(){
    char A[27]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    char a[27]={"abcdefghijklmnopqrstuvwxyz"};
    int count[26]={0};
    string S;

    cin >> S;
    for (int i=0;i<S.size();i++){
        for (int j=0;j<26;j++){
            if (S[i]==A[j] || S[i]==a[j]){
                count[j]++;
                break;
            }
        }
    }

    for (int i=0;i<26;i++)
        cout << A[i] << " : " << count[i] <<endl;
}