#include<iostream>
using namespace std;

//遞迴: 透過「函式內再次呼叫自己」來解決問題的演算法
//寫遞迴時，我們需要先找到「最小的問題」，以及「遞迴關係式」(如何將大問題拆成小問題)


//範例一: 階乘(n!=1*2*3*...*n-1*n)
//最小問題: 1!=1
//將大問題拆成小問題: n!=n*(n-1)!

int Fac(int num){ //Factorial
    if (num==1) return 1;
    else return num*Fac(num-1);
}

/*
程式運行
來算5的階乘，呼叫Fac(5)
由於5不等於1，回傳5*Fac(5-1)
Fac(4)回傳4*Fac(4-1)
Fac(3)回傳3*Fac(3-1)
Fac(2)回傳2*Fac(2-1)
Fac(1)是我設定的最小問題，不回傳1*Fac(1-1)，而是直接回傳1

然後就一路推回去
Fac(2)=2*1=2
Fac(3)=3*2=6
Fac(4)=4*6=24
Fac(5)=5*24=120
最終得到Fac(5)=120，回傳120
*/


//===========================================================================

//範例二: 經典的費撥那契數列(1,1,2,3,5,8,13...)
//最小問題: Fib(0)=1, Fib(1)=1
//將大問題拆成小問題: Fib(n)=Fib(n-1)+Fib(n-2)

int Fib(int num){
    if (num==0 || num==1) return 1;
    else return Fib(num-1)+Fib(num-2);
}

/*
程式運行
當我們呼叫Fib(5)，由於5不等於0或1，函式會return(回傳)Fib(4)+Fib(3)
Fib(4)會回傳Fib(3)+Fib(2)
Fib(3)會回傳Fib(2)+Fib(1)
Fib(2)會回傳Fib(1)+Fib(0)
此時，Fib(1)跟Fib(0)是我設定的「最小問題」，他們不會再回傳Fib(-1)...，而是直接回傳1

然後就一路推回去
Fib(2)=2
Fib(3)=2+1=3
Fib(4)=3+2=5
Fib(5)=5+3=8
最終得到Fib(5)=8，回傳8
*/



int main(){
    cout << Fac(5) <<endl; //輸出: 120
    cout << Fib(5) <<endl; //輸出: 8
}

//Created by B.J.Wang 2025/11/7