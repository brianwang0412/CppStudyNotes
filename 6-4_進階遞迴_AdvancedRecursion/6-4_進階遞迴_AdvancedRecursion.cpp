#include<iostream>
using namespace std;

//進階遞迴
//請先看過6-3_遞迴_Recursion

//範例一: GCD(最大公因數)_遞迴解

/* 數學概念: 輾轉相除
步驟一：準備兩個正整數 a 和 b
步驟二：計算 a 除以 b 的餘數 r。
步驟三：檢查餘數 r。如果 r=0，那麼 b 就是這兩個數的最大公因數。
如果 r!=0，則令 a 變成原本的 b，並令 b 變成餘數 r，然後重複步驟二。 
(本段筆記由Gemini生成)
*/

/* 來看個例子__求15跟10的GCD
15%10=5，餘數不為零(15%10 != 0)，繼續做10%5
10%5=0，餘數為零(10%5==0)，得到[除數 5]就是15跟10的GCD
*/

/* 程式:
先輸入兩個整數a,b
運行GCD(a,b);

先做a%b
當a%b==0時，代表b是a,b的GCD(最大公因數)
回傳 b

否則回傳GCD(b, a%b);
*/

int GCD(int a, int b){
    if (a%b == 0) return b;
    else return GCD(b, a%b);
}

/*
最小問題: 餘數為0時回傳b -> if (a%b==0) return b;
將大問題拆成小問題: 若餘數不為0，則用除數與餘數繼續求GCD -> else return GCD(b, a%b);
*/


//===========================================================================


//範例二: 河內塔(Hanoi Tower)

/* 
什麼是河內塔?
河內塔是一種由三根柱子和多個不同大小的圓盤組成的益智遊戲（或數學問題）。
所有圓盤一開始按照大小排序，由大到小堆在同一根柱子上。

你的任務是：
把整疊圓盤移到另一根柱子上，保持原來的大小順序(由上到下為: 1~n，1是最小的圓盤，n是最大的圓盤)。

玩法規則：
1. 一次只能移動一個盤子。
2. 盤子只能從某根柱子的最上面移出。
3. 不能把大盤子放在小盤子上。

如何用遞迴解決?
要移動 n 層盤子，你必須：
1. 先將 第1~n−1層 移動到暫存柱
2. 移動 第n層 盤子到目標柱
3. 再把 第1~n−1層 移動到目標柱
(本段筆記由ChatGPT生成)
*/


//記得最小的盤子是n=1
//目的: 將n個圓盤從A柱移動到C柱
void hanoi(int n, char A, char B, char C){
/*參數代表的意義
有n個圓盤(由小到大為1~n)與A,B,C三個柱子
n: 要移動的是第1個~第n個圓盤(1最小,最上面，n最大,最下面)

注意!! 參數char A, char B, char C代表的不是固定的柱子，而是
A: 起始柱 (要移動的圓盤「現在在哪個柱子」)
B: 暫存柱 (用來「暫時存放」圓盤的柱子)
C: 目標柱 (要移動的圓盤「要移去哪個柱子」)
*/
    if (n==1){
        cout <<"Disk "<< n <<" from "<< A <<" to "<< C <<endl;
        //當n==1時，代表現在要移動的是第一個圓盤(第1~n個,在這裡是第1~1個,即1)，它上面不可能會有別的圓盤，我們可以直接將它移動到目標柱(A->C)
    }
    else{
        //當n!=1時，想要將n個圓盤從(起始柱A)移動到(目標柱C):
        //我們需要先把(起始柱A)上的 [第n個圓盤(最下面、最大的圓盤)] 上面的 [n-1個圓盤] 從(起始柱A)移動到(暫存柱B)
        hanoi(n-1,A,C,B);

        //現在第n個圓盤上方是空的(第1~n-1個已經被移到(暫存柱B)上了)，我們可以直接把它從(起始柱A)移動到(目標柱C)
        cout <<"Disk "<< n <<" from "<< A <<" to "<< C <<endl;

        //最後再把(暫存柱B)上的第1~n-1個圓盤移動到(目標柱C)上
        hanoi(n-1,B,A,C);
    }
}

/* hanoi(3,'a','b','c') 輸出
Disk 1 from a to c
Disk 2 from a to b
Disk 1 from c to b
Disk 3 from a to c
Disk 1 from b to a
Disk 2 from b to c
Disk 1 from a to c
*/

/*河內塔遞迴結果解析 hanoi(3,'a','b','c');

hanoi(3,A,B,C)-> 將三層圓盤從(起始柱A)(n=3)移動到(目標柱C)(n=3)
{

hanoi(2,A,C,B)-> 先將第1,2層從(起始柱A)(n=3)移動到(暫存柱B)(n=3)
[
要移動第1,2層到暫存柱B(n=3)，需要先將第1層移動到暫存柱B(n=2)

!!注意: 暫存柱B(此時n==3) 跟 暫存柱B(此時n==2) 不一樣!!
!!暫存柱B代表「不是」中間的那根柱子b，並且每層的暫存柱B實際代表的柱子也不一定會是同一根(可能是a,b或c)!!
!!起始柱A 跟 目標柱C 也是如此!!

Disk 1 from a to c -> hanoi(1,A,C,B) -> 移動第1層 起始柱A(n=2)->暫存柱B(n=2)

Disk 2 from a to b -> 移動第2層 起始柱A(n=2)->目標柱C(n=2)

Disk 1 from c to b -> hanoi(1,B,A,C) -> 移動第1層 暫存柱B(n=2)->目標柱C(n=2)

]

Disk 3 from a to c -> 移動第3層 起始柱A(n=3)->目標柱C(n=3)

hanoi(2,B,A,C)-> 最後將第1,2層從(暫存柱B)(n=3)移動到(目標柱C)(n=3)
[

Disk 1 from b to a -> hanoi(1,A,C,B) -> 移動第1層 起始柱A(n=2)->暫存柱B(n=2)

Disk 2 from b to c -> 移動第2層 起始柱A(n=2)->目標柱C(n=2)

Disk 1 from a to c -> hanoi(1,B,A,C) -> 移動第1層 暫存柱B(n=2)->目標柱C(n=2)

]

}
結束
*/

//移動n個盤子的最少步數是: (2**n)-1

/* hanoi tower code only
程式碼在這裡

void hanoi(int n, char A, char B, char C){
    if (n==1){
        cout <<"Disk "<< n <<" from "<< A <<" to "<< C <<endl;
    }
    else{
        hanoi(n-1,A,C,B);
        cout <<"Disk "<< n <<" from "<< A <<" to "<< C <<endl;
        hanoi(n-1,B,A,C);
    }
}

*/

int main(){
    cout<<"GCD(27,15) = "<<GCD(27,15)<<endl;

    cout<<"\nThe smallest disk is 1"<<endl;
    cout<<"The biggest disk is 3"<<endl;
    hanoi(3,'a','b','c');
}

/*
輸出:
GCD(27,15) = 3

The smallest disk is 1
The biggest disk is 3
Disk 1 from a to c
Disk 2 from a to b
Disk 1 from c to b
Disk 3 from a to c
Disk 1 from b to a
Disk 2 from b to c
Disk 1 from a to c
*/

//Created by B.J.Wang 2025/11/17