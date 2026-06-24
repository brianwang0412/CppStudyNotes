#include<iostream>
using namespace std;

template <typename T1, typename T2, typename T3>

T1 MAX(T1 var1, T2 var2, T3 var3){
    T1 max_var=var1;
    if (var2>max_var) max_var=var2;
    if (var3>max_var) max_var=var3;
    return max_var;
}

int main(){
    //cout<< MAX(1,2,3) <<endl;
    //cout<< MAX(1.5, 199.99, 13.57)<<endl;
    //cout<< MAX('C','B','A')<<endl;
    cout<< MAX(93,3355.0336,"P")<<endl;
}