/*
題目:
一開始有一隻不會死的母蜂
母蜂每年會生一隻公蜂，並死亡
公蜂每年會生一隻公蜂+一隻母蜂，並死亡
求公蜂數與總蜂數
*/

#include<iostream>
using namespace std;

int main(){
    int N;
    while (true){
        cin >> N;
        if (N == -1) break;
        
        int M_bee=0, Fe_bee=1, next_M, next_Fe;
        for (int i=0;i<N;i++){
            next_M = M_bee + Fe_bee; //只有新的公蜂會活下來
            next_Fe = M_bee + 1; //只有新的母蜂與「神奇母蜂」會活下來
            M_bee = next_M;
            Fe_bee = next_Fe;
        }

        cout << M_bee << ' ' << M_bee + Fe_bee <<endl;
    }
}