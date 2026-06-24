// d260. 11455 - Behold my quadrangle
// https://zerojudge.tw/ShowProblem?problemid=d260

#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int n,a[4];
    cin>>n;
    while (n--){
        for (int i=0;i<4;i++) cin>>a[i];

        sort(a,a+4);

        if (a[0]+a[1]+a[2]+a[3] == 4*a[0]) cout<<"square"<<endl;
        else if (a[0]==a[1] && a[2]==a[3]) cout<<"rectangle"<<endl;
        else if (a[0]+a[1]+a[2]>a[3]) cout<<"quadrangle"<<endl;
        else cout<<"banana"<<endl;
    }

    return 0;
}

//Created by B.J.Wang 20260325