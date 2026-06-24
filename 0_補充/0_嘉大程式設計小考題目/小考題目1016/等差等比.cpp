#include<iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    int a,b,c,d;
    for (int i=0;i<t;i++){
        cin >> a >> b >> c >> d;
        cout << a << " " << b << " " << c << " " << d << " "; 
        if (b-a == c-b) cout << d+(b-a) <<endl;
        else cout << d*(b/a) <<endl;
    }
    return 0;
}