#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>

/*
核心觀念: 把力氣最小烏龜疊在最上方

我一開始也是想從下面往上疊，但每次疊都需要逐一檢查之前的烏龜是否過重
最後TLE

https://hackmd.io/@Ateto/r1iuEzd93
他的解法就不需要逐一檢查之前的烏龜
並在超重時踢掉目前疊的烏龜中最重的，如此雖然烏龜總數不變，但總重可能更少(或不變)，更有利

*/

bool cmp(pii& a, pii& b){
    if (a.second == b.second) return a.first < b.first;
    else return a.second < b.second;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<pii> v;
    priority_queue<pii> pq;
    int w,s,i,total=0;
    while (cin>>w>>s){
        v.push_back({w,s});
    }

    sort(v.begin(), v.end(), cmp);

    for (i=0; i<v.size(); ++i){
        pq.push(v[i]);
        total+=v[i].first;
        if (v[i].second < total){
            total -= pq.top().first;
            pq.pop();
        }
    }
    cout<< pq.size() <<'\n';
}

//參考 https://hackmd.io/@Ateto/r1iuEzd93