#include<bits/stdc++.h>
using namespace std;

template <typename T> //宣告一個類別模板T

class MinStack{
    private:
        stack<T> S;
        stack<T> Min;
    public:
        MinStack(){}

        void push(T x){
            S.push(x);

            // 可以用.empty()來判斷Min是否為空
            if (Min.empty() || x < Min.top()){
                Min.push(x);
            }

            //修正
            else{
                Min.push(Min.top());
            }
        }

        void pop(){
            S.pop();
            Min.pop(); //修正
        }

        T top(){
            return S.top();
        }

        T getMin(){
            return Min.top();
        }

        bool empty(){
            return S.empty();
        }

        int size(){
            return S.size();
        }

};

int main(){
    // ---------- 測試 MinStack ----------
    cout<<"===== 測試 MinStack =====\n";

    MinStack<int> ms;
    cout<< ms.empty() <<endl;  // 輸出: 1 (目前是空的)

    ms.push(5);
    ms.push(3);
    ms.push(7);
    ms.push(1);
    // 目前ms(由底至頂): 5 3 7 1
    // 對應的minS(由底至頂): 5 3 3 1

    cout<< ms.top() <<endl;     // 輸出: 1  (頂端元素)
    cout<< ms.getMin() <<endl;  // 輸出: 1  (目前最小值)
    cout<< ms.size() <<endl;    // 輸出: 4

    ms.pop();  // 彈出1，ms(由底至頂): 5 3 7
    cout<< ms.top() <<endl;     // 輸出: 7
    cout<< ms.getMin() <<endl;  // 輸出: 3  (1被彈出後，最小值變回3)

    ms.pop();  // 彈出7，ms(由底至頂): 5 3
    ms.pop();  // 彈出3，ms(由底至頂): 5
    cout<< ms.getMin() <<endl;  // 輸出: 5  (最小值變回5)
    cout<< ms.size() <<endl;    // 輸出: 1
    cout<< ms.empty() <<endl;   // 輸出: 0 (還有一個元素，非空)


}

/*
範例輸出:
1
1
1
4
7
3
5
1
0
*/

// Created by B.J.Wang 20260824