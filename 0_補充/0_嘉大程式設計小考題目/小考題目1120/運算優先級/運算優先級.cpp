/*
給一個式子，如: A*((B+C)/D)+E
輸出每個變數(字母)的運算優先級
A:0
B:2
C:2
D:1
E:0

如何判斷:
以D為例，它前面有兩個'('跟一個')'
代表它被一個括弧包住，優先級為1
*/

#include<iostream>
#include<string>
using namespace std;

int main(){
    string s;
    getline(cin,s);

    int i=0,Len=s.size();
    while (i<Len){
        //先找到變數(不是符號)，即非( ) + - * / %的字符
        if (s[i]!='(' && s[i]!=')' && s[i]!='+' && s[i]!='-' && s[i]!='*' && s[i]!='/' && s[i]!='%'){
            int level=0;
            for (int j=0; j<i; j++){
                if (s[j]=='(') level++;
                if (s[j]==')') level--;
            }
            
            cout<< s[i] <<':'<< level <<endl;
        }

        i++;
    }
    return 0;
}

/*測資
輸入:
A*((B+C)/D)+E

輸出:
A:0
B:2
C:2
D:1
E:0
*/

//Created by B.J.Wang 2025/11/20