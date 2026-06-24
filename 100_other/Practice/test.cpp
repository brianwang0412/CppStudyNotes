#include<iostream>
#include<string>
using namespace std;

void PlusByValue(int num){ //這裡的num是區域變數，不會影響到main()裡的a
    num+=1;
}

void PlusByReference(int& num){ //這裡的num是位址，會直接修改main()裡的a的值
    num+=1;
}

int main(){
    int a=5;
    PlusByValue(a);
    cout<<"PlusByValue(a) = "<< a <<endl; //PlusByValue(a) = 5

    PlusByReference(a);
    cout<<"PlusByReference(a) = "<< a <<endl; //PlusByReference(a) = 6

    return 0;
}