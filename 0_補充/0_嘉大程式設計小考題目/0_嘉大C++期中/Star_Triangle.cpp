/*
題目解析:
輸出N
畫大小為N的星星三角形
*
**
***
****
*/

#include<iostream>
#include<iomanip>
using namespace std;

int main(){
    int N;
    cin >> N;
    cout <<"N="<<N<<endl;
    for (int i=0;i<=N;i++)
        cout <<setw(i)<<setfill('*')<<""<<endl;
}