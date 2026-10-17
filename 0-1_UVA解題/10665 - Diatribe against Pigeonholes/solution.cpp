#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>

bool cmp(pii a, pii b){
    return a.second>b.second;
}

int main(){
    int m,n;
    cin>>m;
    string s;
    while (m--){
        cin>>n;
        cin>>s;

        vector<pii> v(n);
        for (int i=0; i<n; i++) v[i] = {i, 0};

        // count
        for (const char i:s){
            if (i=='#') break;
            if (i-'A' >= n) continue;
            v[i-'A'].second++;
        }

        // sort
        sort(v.begin(), v.end(), cmp);

        // get order
        vector<pii> order;
        for (int i=0; i<n; i++){
            order.push_back({v[i].second, v[i+1].second});
        }
        if (order.size()*2 != v.size()){ // n is odd
            order.push_back({v[n-1].second, -1});
        }
        
        // get answer
        map<pii, vector<pii>> store;
        vector<pii> ans;
        for (pii& p:order){
            vector<pii> temp;
            if (find(store.begin(), store.end(), p) != store.end()){
                temp = store[p];
            }
            else{
                for (int i=0; i<n; i++){
                    if (v[i].second==p.first || v[i].second==p.second){
                        temp.push_back(v[i]);
                    }
                }
                store[p] = temp;
            }
            
            sort(temp.begin(), temp.end());
            ans.push_back(temp[0]);
            

            v.erase(find(v.begin(),v.end(),temp[0]));

            if (p.first==temp[0].first) p.first=-1;
            else p.second=-1;

            store[p].erase(find(store[p].begin(), store[p].end(), temp[0]));
        }

        for (int i=0;i<n;i++){
            cout<<(char)('A'+ans[i].first);
            if (i!=n-1) cout<<' ';
        }
        cout<<'\n';
        for (int i=0;i<n;i++){
            cout<<ans[i].second;
            if (i!=n-1) cout<<' ';
        }
        cout<<'\n';

    }
}

// https://claude.ai/chat/635f2246-ecfa-4895-8a96-7deed716dffe