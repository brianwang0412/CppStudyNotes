#include<iostream>
using namespace std;

class complex_num{
    friend complex_num operator+(complex_num& X, complex_num& Y);

    public:
        int rel, img;
        complex_num(){}
        complex_num(int A, int B): rel{A}, img{B}{}

};

complex_num operator+(complex_num& X, complex_num& Y){
    complex_num temp;
    temp.rel = X.rel + Y.rel;
    temp.img = X.img + Y.img;
    return temp;
}

int main(){
    int a,b;
    cin>>a>>b;
    complex_num X=complex_num(a,b);
    cin>>a>>b;
    complex_num Y=complex_num(a,b);
    complex_num Z=X+Y;
    cout<<Z.rel<<' '<<Z.img;
}

/*
測資1
輸入: 5 7 5 6
輸出: 10 13

測資2
輸入: 2 7 2 9
輸出: 4 16
*/

//Created by B.J.Wang 20260428最後修正