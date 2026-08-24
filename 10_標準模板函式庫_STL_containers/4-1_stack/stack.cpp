#include<stack>  // 需引入<stack>標頭檔

#include<iostream>
#include<vector>
#include<deque>
#include<list>
#include<string>
using namespace std;

/*
前言: stack的特性

1. stack是一種「容器配接器 (Container Adapter)」，本身不是獨立的容器，
   而是將底層容器(預設為 deque)包裝成「後進先出 (LIFO, Last In First Out)」的資料結構
2. 只能從同一端(稱為"頂端"/top)進行新增(push)與刪除(pop)，
   不能任意存取中間或底部的元素，也「沒有」iterator，因此無法用range-based for遍歷
3. 底層容器預設為 deque，也可以改用 vector 或 list（但不能用 array 或 forward_list，
   因為它們沒有實作 stack 所需的 push_back / pop_back / back 等操作）
4. push、pop、top、empty、size 的時間複雜度皆為 O(1)
*/

int main(){
{
    // 《1. stack的宣告》

    // 建立空的stack，底層容器預設為deque，可以用於儲存整數(int)
    stack<int> s1;

    // 明確指定底層容器為 vector
    stack<int, vector<int>> s2;

    // 明確指定底層容器為 list
    stack<int, list<int>> s3;

    // 用「已存在的容器」來初始化stack（stack本身沒有initializer-list建構子）
    deque<int> d = {1, 2, 3};
    stack<int> s4(d);  // s4的內容(由底至頂): 1 2 3，此時s4.top()為3
    cout<< s4.top() <<endl;  // 輸出: 3

    vector<int> vec = {4, 5, 6};
    stack<int, vector<int>> s5(vec);  // s5.top()為6
    cout<< s5.top() <<endl;  // 輸出: 6

    // 複製建構，s4與s6會互相獨立
    stack<int> s6(s4);
    cout<< s6.top() <<endl;  // 輸出: 3
}
cout<<("====================================\n");// 分隔線
{
    // 《2. stack的新增、存取與刪除》

    stack<int> s;  // 建立一個空的stack

    // 1. 新增 (push 與 emplace)

    // s.push(x) 將元素x推入stack頂端
    s.push(1);
    s.push(2);
    s.push(3);
    cout<< s.top() <<endl;  // 輸出: 3 (目前頂端元素為最後推入的3)

    // s.emplace(x) 效果與push相同，但是直接在stack內部原地建構元素，
    // 省去建立臨時物件再複製/搬移的過程，元素為複雜物件(如struct/class)時效率較高
    s.emplace(4);
    cout<< s.top() <<endl;  // 輸出: 4


    // 2. 存取 (top)

    // s.top() 回傳「頂端元素的參考(reference)」，可讀也可寫
    // 注意: stack只能存取頂端元素，無法像vector一樣用[i]或.at(i)存取任意位置
    cout<< s.top() <<endl;  // 輸出: 4

    s.top() = 999;  // 直接修改頂端元素的值
    cout<< s.top() <<endl;  // 輸出: 999


    // 3. 刪除 (pop)

    // s.pop() 刪除頂端元素，「沒有回傳值」
    // 注意: 若想要取得被刪除的值，務必先用s.top()記錄下來，再呼叫s.pop()
    int removed = s.top();  // 先記錄頂端元素的值 (999)
    s.pop();                // 再刪除頂端元素
    cout<< removed <<endl;  // 輸出: 999
    cout<< s.top() <<endl;  // 輸出: 3 (刪除999後，新的頂端元素變成3)

    // 對空的stack呼叫top()或pop()會導致「未定義行為(Undefined Behavior)」，
    // 不會像vector.at()或map.at()一樣拋出例外，因此使用前務必先用empty()檢查
    // 錯誤示範(請勿執行): stack<int> empty_s; empty_s.pop(); // UB，可能直接當掉
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 遍歷》

    // stack「沒有」iterator，也沒有begin()/end()，
    // 因此無法使用一般for迴圈、range-based for，或搭配<algorithm>的函式(如sort、find)
    // 若想要遍歷全部元素，只能不斷讀取並彈出頂端元素，直到stack清空為止
    // (這樣做會破壞原本的stack，如果之後還要用到，記得先複製一份再操作)

    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);  // s(由底至頂): 1 2 3

    stack<int> s_copy(s);  // 複製一份，避免破壞原本的s

    cout<<"由頂到底輸出: ";
    while (!s_copy.empty()){
        cout<< s_copy.top() << ' ';
        s_copy.pop();
    }
    cout<<endl;
    // 輸出: 由頂到底輸出: 3 2 1
    // (因為stack是LIFO，最後push進去的3最先被pop出來)
}
cout<<("====================================\n");// 分隔線
{
    // 《4. 常用功能》

    stack<int> s;

    // 判斷stack是否為空
    cout<< s.empty() <<endl;  // 輸出: 1 (表示是空的)

    s.push(10);
    s.push(20);
    cout<< s.empty() <<endl;  // 輸出: 0 (表示非空)

    // 取得stack內的元素個數
    cout<< s.size() <<endl;  // 輸出: 2


    // 交換兩個stack的內容(底層容器需相同型別)
    stack<int> s1, s2;
    s1.push(1); s1.push(2); s1.push(3);  // s1(由底至頂): 1 2 3
    s2.push(7); s2.push(8);              // s2(由底至頂): 7 8

    s1.swap(s2);
    cout<<"s1.top(): "<< s1.top() <<", s1.size(): "<< s1.size() <<endl;
    // 輸出: s1.top(): 8, s1.size(): 2
    cout<<"s2.top(): "<< s2.top() <<", s2.size(): "<< s2.size() <<endl;
    // 輸出: s2.top(): 3, s2.size(): 3

    // 也可以使用非成員函式 std::swap(s1, s2)，效果相同
    std::swap(s1, s2);
    cout<<"交換回來後 s1.top(): "<< s1.top() <<endl;  // 輸出: 交換回來後 s1.top(): 3


    // stack「沒有」clear()函式，若想清空，常見做法有兩種:

    // 做法一: 迴圈不斷pop直到empty
    stack<int> s3;
    s3.push(1); s3.push(2); s3.push(3);
    while (!s3.empty()) s3.pop();
    cout<< s3.empty() <<endl;  // 輸出: 1 (已清空)

    // 做法二: 直接賦值一個新的空stack(較簡潔，C++11後可用)
    stack<int> s4;
    s4.push(1); s4.push(2);
    s4 = stack<int>();
    cout<< s4.empty() <<endl;  // 輸出: 1 (已清空)


    // 比較運算子 (== != < <= > >=)
    // 比較規則: 逐一比較底層容器內「由底至頂」的對應元素(類似字典序比較)
    stack<int> a, b;
    a.push(1); a.push(2); a.push(3);  // a(由底至頂): 1 2 3
    b.push(1); b.push(2); b.push(4);  // b(由底至頂): 1 2 4

    cout<< (a==b) <<endl;  // 輸出: 0
    cout<< (a!=b) <<endl;  // 輸出: 1
    cout<< (a< b) <<endl;  // 輸出: 1 (因為在第三個元素比較時 3 < 4)
    cout<< (a<=b) <<endl;  // 輸出: 1
    cout<< (a> b) <<endl;  // 輸出: 0
    cout<< (a>=b) <<endl;  // 輸出: 0
}
}


// 本篇筆記參考Claude (https://claude.ai)
// Created by B.J.Wang 2026/8/17
