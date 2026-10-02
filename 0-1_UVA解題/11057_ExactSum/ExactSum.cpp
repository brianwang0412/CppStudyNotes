#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, money,now;
    while (cin>>n){
        vector<int> v(n);
        vector<int> ans={INT_MAX, 0};
        for (int i=0;i<n;i++) cin>>v[i];
        cin>>money;

        for (int i=0; i<n-1; i++){
            now=v[i];
            v[i]=-1;
            vector<int>::iterator it = find(v.begin(), v.end(), money-now);
            if (it!=v.end()){
                if (abs(now-(*it)) < abs(ans[0]-ans[1])) ans={now, *it};
            }
        }

        sort(ans.begin(), ans.end());
        cout<<"Peter should buy books whose prices are "<<ans[0]<<" and "<<ans[1]<<".\n\n";
    }

    return 0;
}