/*
題目解析:
判斷兩時間段是否重疊
*/

#include<iostream>
using namespace std;

int main(){
    int N,a,b,c,d;
    int Wife[2],Meet[2];
    char colon;

    cin >> N;
    for (int i=0;i<N;i++){
        cin >> a >>colon>> b >> c >>colon>> d;
        //cin遇到不符合型別的字元會立即停止讀取
        //如輸入11:47 22:40，a只會讀到11，colon讀:，b讀到47

        //全部換成分鐘
        Wife[0]=a*60+b; //開始
        Wife[1]=c*60+d; //結束
        
        cin >> a >>colon>> b >> c >>colon>> d;
        Meet[0]=a*60+b;
        Meet[1]=c*60+d;

        cout << "Case " << i+1 <<": ";
        if ( (Wife[0]<=Meet[0] && Meet[0]<=Wife[1]) || (Meet[0]<=Wife[0] && Wife[0]<=Meet[1]) )
            cout << "Mrs Meeting"<<endl;
        else
            cout << "Hits Meeting"<<endl;
    }
}