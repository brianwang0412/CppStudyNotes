#include<iostream>
#include<map>
#include<string>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // 1.
    map<string, int> mp;
    int n;
    cin>>n;

    string s;
    int score;
    for (int i=0;i<n;++i){
        cin>>s>>score;
        mp[s]=score;  //使用operator[] 可做新增與修改
    }

    // 2. map會自動以Key值由小至大排列
    for (const auto& p:mp){
        cout<< p.first << ':' << p.second <<'\n';
    }

    // 3.
    for (int i=0; i<2; i++){
        cin>>s;
        auto it = mp.find(s);
        if (it != mp.end()){
            cout<<it->second<<'\n';
        }
        else{
            cout<< "查無此人" <<endl;
        }
    }

    // 4. 
    for (int i=0; i<2; i++){
        cin>>s;
        int result = mp.erase(s);  // 直接用Key去erase，回傳刪除的數量
        if (result==1) cout<<"刪除成功"<<'\n';
        else cout<<"刪除失敗"<<'\n';
    }

    // 5. 
    int count=0;
    for (const auto& p:mp){
        if (p.second >= 60) count++;
    }
    cout<< count <<'\n';

    // 6. 
    cout << mp.size() <<'\n';
}

/*
範例輸入:
5
Alice 85
Bob 45
Charlie 90
Bob 70
David 55
Charlie
Eve
Bob
Frank

範例輸出:
Alice:85
Bob:70
Charlie:90
David:55
90
查無此人
刪除成功
刪除失敗
2
3
*/

// Created by B.J.Wang 2026/8/4