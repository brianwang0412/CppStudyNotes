#include<iostream>
using namespace std;

int main(){
    int M,h,m;
    cin >> M;
    h = M/60;
    m = M%60;
    cout << h << ":" << m;
}

int main(){
    int M;
    cin >> M;
    cout << M/60 << ':' << M%60;
}