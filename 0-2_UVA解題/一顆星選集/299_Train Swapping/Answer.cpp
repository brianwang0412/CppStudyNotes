#include<iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t,n,count;
    cin>>t;
    while (t--){
        cin>>n;
        int *Num = new int[n];
        for (int i=0; i<n; ++i) cin>>Num[i];
        
        count=0;
        for (int i=0; i<n; ++i){
            for (int j=0; j<n-i-1; ++j){
                if (Num[j]>Num[j+1]){
                    swap(Num[j], Num[j+1]);
                    ++count;
                }
            }
        }
        cout << "Optimal train swapping takes " << count << " swaps.\n";
    }
}

// AC