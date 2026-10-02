#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int Y, P;
    while (cin>>Y>>P){
        vector<int> v(P);
        for (int i=0;i<P;i++) cin>>v[i];

        int left=0, right=0, count=0;
        vector<int> ans(3,0);
        for (right=0; right<P; right++){
            count++;
            while (v[right]-v[left] >= Y){
                left++;
                count--;
            }

            if (count > ans[0]){
                ans[0]=count;
                ans[1]=left;
                ans[2]=right;
            }
        }

        cout<<ans[0]<<' '<<v[ans[1]]<<' '<<v[ans[2]]<<'\n';
    }

    return 0;
}