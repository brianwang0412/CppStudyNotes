#include<iostream>
using namespace std;

int main(){
    int N;
    cin>>N;
    long long *List = new long long[N];
    for (int i=0;i<N;++i) cin>>List[i];
    
    bool finish=false;
    for (int i=0; i<N; ++i){
        for (int j=i+1; j<N; ++j){
            if (List[i]==List[j]){
                cout<<List[i];
                finish=true;
                break;
            }
        }
        if (finish) break;
    }
}

// 本篇筆記為嘉義大學資訊工程學系物件導向程式設計之課堂題目
// //Created by B.J.Wang 20260609