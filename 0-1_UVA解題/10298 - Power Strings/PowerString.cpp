#include<bits/stdc++.h>
using namespace std;
int main(){
    string s,now,sub;
    while (cin>>s && s!="."){
        int ss=s.size(),n,i;
        bool get=0;
        for (n=1; n<=ss; ++n){
            if (s.size()%n!=0) continue;
            get=1;
            now=s.substr(0,n);
            for (i=0; i<ss; i+=n){
                sub=s.substr(i,n);
                if (now!=sub){
                    get=0;
                    break;
                }
            }
            if (get){
                cout<< ss/n <<'\n';
                break;
            }

        }
    }
}