#include<iostream>
#include<string>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    bool visited=false;  // 是否已經過"

    while (getline(cin, s)){
        for (int i=0; i<s.size(); ++i){
            if (s[i]=='\"'){
                if (!visited){
                    cout<<"``";
                    visited=true;
                }
                else{
                    cout<<"''";
                    visited=false;
                }
            }
            else cout<<s[i];
        }
        cout<<'\n';
    }
}

//本題參考 https://yuihuang.com/zj-c007/
// AC