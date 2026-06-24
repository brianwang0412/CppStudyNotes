#include<iostream>
using namespace std;

/*
大寫 A 的 ASCII = 65
小寫 a 的 ASCII = 97 
*/

char upper(char letter){
    if (letter>='a') return letter-'a'+'A'; 
    else return letter;
}

int main(){
    cout<<"ASCII code:\nA : "<<int('A')<<" , a : "<<int('a')<<endl;
    /*
    ASCII code:
    A : 65 , a : 97
    */

    char word;
    cout<<"Enter a letter >>";
    cin >> word;

    cout<<"The uppercase of "<<word<<" is "<<upper(word)<<endl;
}

/*
輸入與輸出: 
範例一
輸入: b
輸出: The uppercase of b is B

範例二
輸入: Y
輸出: The uppercase of Y is Y
*/

//Created by B.J.Wang 2025/11/18