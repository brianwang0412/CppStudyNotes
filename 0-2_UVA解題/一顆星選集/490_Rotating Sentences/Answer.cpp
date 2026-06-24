#include<iostream>
#include<string>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sentence=0,Max_len=0;
    string s[105];

    while (getline(cin, s[sentence])){
        Max_len = max(Max_len, (int)s[sentence].size());
        ++sentence;
    }
    for (int i=0; i<Max_len; ++i){
        for (int j=sentence-1;  j>=0; --j){
            if (i<=((int)s[j].size()-1)){
                cout<<s[j][i];
            }
            else cout<<' ';
        }
        cout<<'\n';
    }
}


// 本篇筆記參考 https://yuihuang.com/zj-c045/
// AC