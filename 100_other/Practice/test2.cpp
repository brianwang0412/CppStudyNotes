#include<iostream>
using namespace std;

int a=1;

int main(){
    int a=2;
    cout<<"a="<<a<<endl;
    cout<<"a="<<::a<<endl;
}