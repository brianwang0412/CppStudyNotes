#include<set>  // 需引入<set>標頭檔

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>  // inserter、back_inserter，搭配 <algorithm> 的集合運算使用
using namespace std;

/*
前言: set的特性

1. set(集合)會自動將元素依照大小「排序」（預設由小到大）
2. 元素「不可重複」（若插入重複元素，插入動作會失敗，且不會有任何效果）
3. 插入、刪除、搜尋的時間複雜度皆為 O(log n)，底層邏輯為紅黑樹（與map相同）
4. set中的元素本身「同時是key也是value」，且元素為const，無法直接透過iterator修改
   （若想修改，必須先刪除舊元素，再插入新元素）
*/

int main(){
{
    // 《1. set的宣告》

    // 建立空的set
    set<int> s1;

    // 初始化
    set<int> s2 = {3, 1, 4, 1, 5, 9};  // 重複的元素(1)只會保留一個
    for (int i : s2) cout<< i <<' '; cout<<endl;
    // 輸出: 1 3 4 5 9   （自動排序、自動去重）

    // 複製建構
    set<int> s3(s2);

    // 用兩個iterator(迭代器)範圍建立set
    vector<int> v = {7, 2, 8, 2};
    set<int> s4(v.begin(), v.end());
    for (int i : s4) cout<< i <<' '; cout<<endl;
    // 輸出: 2 7 8

    // 自訂排序方式 (改成由大到小)
    set<int, greater<int>> s5 = {3, 1, 4, 1, 5};
    for (int i : s5) cout<< i <<' '; cout<<endl;
    // 輸出: 5 4 3 1

    // 建立元素型別為string的set
    set<string> s6 = {"banana", "apple", "cherry"};
    for (const string& i : s6) cout<< i <<' '; cout<<endl;
    // 輸出: apple banana cherry  （字串依字典順序排序）

    // set的元素也可以是pair或其他有支援 < 運算子的型別
    set<pair<int,int>> s7 = {{2,1}, {1,3}, {1,2}};
    for (const auto& p : s7) cout<<'{'<<p.first<<','<<p.second<<"} "; cout<<endl;
    // 輸出: {1,2} {1,3} {2,1}   （比較規則: 先比較first，再比較second，與pair筆記中的比較規則相同）
}
//===============================分隔線===============================
{
    // 《2. set的新增》

    set<int> s;

    // 使用 s.insert(x) 新增元素
    // 回傳 pair<iterator, bool>，first為指向該元素的iterator，second表示是否新增成功
    auto result1 = s.insert(10);
    cout<< result1.second <<endl;  // 輸出: 1 (代表成功新增)

    auto result2 = s.insert(10);  // 10已存在，新增失敗
    cout<< result2.second <<endl;  // 輸出: 0 (代表新增失敗)

    s.insert(30);
    s.insert(20);
    for (int i : s) cout<< i <<' '; cout<<endl;
    // 輸出: 10 20 30

    // 使用 s.insert(first, last) 一次插入一段範圍的元素(常搭配另一個容器使用)
    vector<int> v = {5, 15, 25};
    s.insert(v.begin(), v.end());
    for (int i : s) cout<< i <<' '; cout<<endl;
    // 輸出: 5 10 15 20 25 30

    // 使用 s.emplace(x) 新增元素
    // 與insert同樣不會覆蓋已有元素，理論上效率較insert高（省去臨時物件的複製/搬移）
    s.emplace(40);
    s.emplace(10);  // 10已存在，新增失敗
    for (int i : s) cout<< i <<' '; cout<<endl;
    // 輸出: 5 10 15 20 25 30 40


    cout<<("======================\n");// 分隔線


    // 《3. set的存取》
    // 注意: set沒有像vector或map那樣可以用[i]或[Key]直接存取元素
    // 只能透過 find() 搜尋，或用iterator遍歷來間接「讀取」元素(且元素為const，不能修改)

    // 使用 s.find(x) 搜尋元素
    // 回傳指向該元素的iterator，找不到則回傳 s.end()
    set<int>::iterator it = s.find(20);
    if (it != s.end()){
        cout<< *it <<endl;  // 輸出: 20
    }

    auto it2 = s.find(999);  // 999不存在
    if (it2 == s.end()){
        cout<<"999 does not exist"<<endl;
    }
    // 輸出: 999 does not exist

    // 使用 s.count(x) 判斷元素是否存在
    // 由於set中元素不得重複，因此回傳值只會是0或1
    cout<< s.count(10) <<endl;  // 輸出: 1
    cout<< s.count(999) <<endl;  // 輸出: 0
}
cout<<("====================================\n");// 分隔線
{
    // 《4. 刪除》

    set<int> s = {10, 20, 30, 40, 50};

    // 用 s.erase(x) 依「元素值」刪除 (回傳刪除的數量，只會是0或1)
    int Erase_num = s.erase(20);
    cout<< Erase_num <<endl;  // 輸出: 1 (表示成功刪除元素20)
    for (int i : s) cout<< i <<' '; cout<<endl;
    // 輸出: 10 30 40 50

    // 用 s.erase(iterator) 依「迭代器」刪除 (回傳刪除元素的後一個元素的迭代器)
    auto it = s.find(30);
    auto next = s.erase(it);
    cout<< *next <<endl;  // 輸出: 40 (表示成功刪除30，且下一個元素為40)
    for (int i : s) cout<< i <<' '; cout<<endl;
    // 輸出: 10 40 50

    // 範圍刪除
    /*
    參數：first 與 last 兩個迭代器，刪除區間 [first, last)
    回傳型態：iterator（指向最後被刪除元素之後的元素，即原先 last 指向的位置）
    */
    s = {10, 20, 30, 40, 50};
    it = s.erase(s.begin(), s.find(30));  // 刪除[begin, 30)，即刪除10與20
    cout<< *it <<endl;  // 輸出: 30 (代表it指向30)
    for (int i : s) cout<< i <<' '; cout<<endl;
    // 輸出: 30 40 50

    // 用 s.clear() 清空整個set
    s.clear();
    cout<< s.size() <<endl;  // 輸出: 0
}
cout<<("====================================\n");// 分隔線
{
    // 《5. 遍歷》

    set<int> s = {30, 10, 20};

    // 方法一：使用 迭代器iterator
    for (set<int>::iterator it = s.begin(); it != s.end(); ++it){
        cout<< *it << ' ';
    }
    cout<<endl;
    // 輸出: 10 20 30

    // 方法二：使用 range-based for statement
    for (const int& i : s){
        cout<< i << ' ';
    }
    cout<<endl;
    // 輸出: 10 20 30

    /*
    補充: 為什麼要用 const int& 而不是 int&？
    因為set中的元素本身同時是排序依據的key，若允許直接修改元素值，
    可能會破壞set內部的排序結構，因此set的iterator是「const_iterator」，
    元素本身無法透過遍歷來修改（編譯時就會直接報錯）
    */

    // 方法三：使用 反向迭代器(reverse_iterator) 由大到小遍歷
    for (auto rit = s.rbegin(); rit != s.rend(); ++rit){
        cout<< *rit << ' ';
    }
    cout<<endl;
    // 輸出: 30 20 10
}
cout<<("====================================\n");// 分隔線
{
    //《6. 常用函式》

    set<int> s = {1, 3, 5, 7, 9};
    set<int> s2;

    // 1. 判斷 set 是否為空
    bool IsEmpty = s.empty();
    cout<< IsEmpty <<endl;  // 輸出: 0 (表示非空)

    IsEmpty = s2.empty();
    cout<< IsEmpty <<endl;  // 輸出: 1 (表示此set是空的)


    // 2. 取得 set 的大小(元素個數)
    int N = s.size();
    cout<< N <<endl;  // 輸出: 5

    N = s2.size();
    cout<< N <<endl;  // 輸出: 0


    // 3. 邊界查詢 (lower_bound / upper_bound / equal_range)
    // 用法與map完全相同(見map筆記《6.常用函式》)

    // s.lower_bound(x)：回傳第一個「元素值>= x」的iterator，重點: 大於或等於(>=)
    auto lb = s.lower_bound(4);
    cout<< *lb <<endl;  // 輸出: 5

    // s.upper_bound(x)：回傳第一個「元素值> x」的iterator，重點: 大於(>)
    auto ub = s.upper_bound(5);
    cout<< *ub <<endl;  // 輸出: 7

    // s.equal_range(x)：回傳 pair {lower_bound(x), upper_bound(x)}
    auto eq = s.equal_range(5);
    cout<< *eq.first << ' ' << *eq.second <<endl;  // 輸出: 5 7


    // 4. 交換兩個set的內容
    set<int> a = {1,2,3}, b = {7,8,9};
    a.swap(b);
    cout<<"a: "; for (int i:a) cout<<i<<' '; cout<<endl;  // 輸出: a: 7 8 9
    cout<<"b: "; for (int i:b) cout<<i<<' '; cout<<endl;  // 輸出: b: 1 2 3


    cout<<("======================\n");// 分隔線


    // 5. 集合運算 (搭配 <algorithm> 使用)
    // 這些函式都需要「已排序」的容器作為輸入，set本身自動排序，非常適合搭配使用
    // 輸出結果需存放到另一個容器中，常搭配 inserter() 使用

    set<int> setA = {1, 2, 3, 4, 5};
    set<int> setB = {3, 4, 5, 6, 7};

    // 聯集 (union): 兩個集合的所有元素(重複的只保留一個)
    set<int> unionResult;
    set_union(setA.begin(), setA.end(), setB.begin(), setB.end(),
              inserter(unionResult, unionResult.begin()));
    cout<<"聯集: "; for (int i : unionResult) cout<< i <<' '; cout<<endl;
    // 輸出: 聯集: 1 2 3 4 5 6 7

    // 交集 (intersection): 兩個集合中「都存在」的元素
    set<int> interResult;
    set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(),
                      inserter(interResult, interResult.begin()));
    cout<<"交集: "; for (int i : interResult) cout<< i <<' '; cout<<endl;
    // 輸出: 交集: 3 4 5

    // 差集 (difference): 存在於setA但「不存在」於setB的元素
    set<int> diffResult;
    set_difference(setA.begin(), setA.end(), setB.begin(), setB.end(),
                    inserter(diffResult, diffResult.begin()));
    cout<<"差集(A-B): "; for (int i : diffResult) cout<< i <<' '; cout<<endl;
    // 輸出: 差集(A-B): 1 2

    // 對稱差集 (symmetric difference): 只存在於「其中一個」集合，不同時存在於兩者的元素
    set<int> symDiffResult;
    set_symmetric_difference(setA.begin(), setA.end(), setB.begin(), setB.end(),
                              inserter(symDiffResult, symDiffResult.begin()));
    cout<<"對稱差集: "; for (int i : symDiffResult) cout<< i <<' '; cout<<endl;
    // 輸出: 對稱差集: 1 2 6 7

    // 判斷setA是否為setB的子集合: includes(容器B的範圍, 容器A的範圍) -> 判斷A是否被B包含
    set<int> small = {3, 4};
    bool isSub = includes(setA.begin(), setA.end(), small.begin(), small.end());
    cout<< isSub <<endl;  // 輸出: 1 (表示{3,4}是setA的子集合)
}
}


/*
補充一: set 與 multiset 的差異

set   : 元素「不可」重複，插入重複元素時insert會失敗(回傳的pair.second為false)
multiset: 元素「可以」重複，插入重複元素時一樣會成功新增
用法幾乎與set完全相同，只差在是否允許重複元素
宣告方式: multiset<int> ms = {1, 1, 2, 3};  // {1, 1, 2, 3} 皆會保留

補充二: set 與 unordered_set 的差異

set         : 元素會自動排序，底層為紅黑樹，插入/刪除/搜尋皆為 O(log n)
unordered_set: 元素「不會」排序(順序不固定)，底層為雜湊表(hash table)，
               插入/刪除/搜尋平均為 O(1)，最差情況(雜湊碰撞嚴重時)為 O(n)
若不需要排序，只需要快速判斷元素是否存在，通常會優先選用unordered_set以換取更好的效能
*/


// 本篇筆記參考 cppreference std::set (https://en.cppreference.com/w/cpp/container/set)
// Generated by Claude 20260812