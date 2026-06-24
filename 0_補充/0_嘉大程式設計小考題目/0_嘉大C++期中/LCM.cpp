/*
題目解析:
找最小公倍數
*/

#include<iostream>
using namespace std;

int main(){
    int a,b;
    cin >> a >> b;
    if (a==0 || b==0){
        cout << 0;
        return 0;
    }

    int ans = b,count=1;
    while (!(ans%a==0 && ans%b==0))
        ans = b*++count;

    cout << ans;
}