#include<deque>  //需引入deque標頭檔

#include<iostream>
#include<algorithm>
#include<numeric>
#include<stdexcept>  // std::out_of_range 定義在 <stdexcept> 標頭檔中
using namespace std;

// 使用Traversal_dq來表示遍歷deque dq的輸出結果
#define Traversal_dq for (const int& i:dq) cout<<i<<' '; cout<<endl;
// 使用Traversal_dd來表示遍歷deque dd(即二維deque陣列)的輸出結果
#define Traversal_dd for (const auto i:dd){for (const int j:i)cout<<j<<' ';cout<<endl;}

/*
前言: deque的特色、用途

deque (double-ended queue，雙向佇列) 是一種可以在「頭尾兩端」都能快速新增/刪除元素的動態陣列

相較於 vector 只能在尾端快速操作 (push_back / pop_back)
deque 額外提供了 push_front / pop_front，時間複雜度同樣是 O(1)

deque 的底層通常實作為「多個固定大小的區塊 (chunk)」，並用一個中控陣列去管理這些區塊
因此它「不保證記憶體連續」(這點與vector不同)，所以 deque 沒有 data() 函式，也沒有 capacity() / reserve() 函式
但 deque 仍然支援隨機存取 (operator[]、at())，時間複雜度為 O(1)，且支援隨機存取迭代器，可搭配<algorithm>的sort等函式使用
*/


int main(){
{
    // 《1. deque的宣告》

    // 建立空的deque，可以用於儲存整數(int)，名稱為dq1
    deque<int> dq1;

    // 建立可容納五個整數的 deque， 每個元素值預設是 0
    deque<int> dq2(5);  // {0, 0, 0, 0, 0}

    // 建立可容納五個整數的 deque， 每個元素值預設是 10
    deque<int> dq3(5, 10);  // {10, 10, 10, 10, 10}

    // 初始化包含元素的 deque，自動設定陣列長度
    deque<int> dq4 = {1, 2, 3, 4};  //dq4的長度為 4

    // 複製建構，dq4與dq5會互相獨立
    deque<int> dq5(dq4);  //dq5為{1, 2, 3, 4}

    // 也可以用兩個iterator(迭代器)範圍來初始化
    deque<int> dq6(dq4.begin(), dq4.begin()+2);  // {1, 2}

    // 建立 3x2 的二維deque，每個內層deque初始化為 {1, 2}
    deque<deque<int>> dd1(3, deque<int>{1,2});  // {{1,2}, {1,2}, {1,2}}
    // 這裡的deque<int>{1,2}，代表一個臨時創建的一維deque，並且包含 1,2 兩個元素

    // 也可以直接初始化二維deque
    deque<deque<int>> dd2 = {{1,2}, {3,4,5}, {6,7,8,9}};

    // 利用 dq.assign() 清空並重新填入deque的內容
    // 這裡介紹填入n個相同的值
    deque<int> dq7(100,1);
    cout<<dq7.size()<<endl; // 長度為100

    dq7.assign(10, 77);
    cout<<dq7.size()<<endl; // 長度為10
}
cout<<("====================================\n");// 分隔線
{
    // 《2. deque的新增、存取與刪除》

    deque<int> dq;  // 建立一個空的deque

    // 1. 新增 (push_back、push_front與insert)

    // dq.push_back(x) 在deque的尾端新增元素
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    Traversal_dq // 遍歷輸出: 1 2 3

    // dq.push_front(x) 在deque的開頭新增元素 (vector沒有這個函式)
    dq.push_front(0);
    dq.push_front(-1);
    Traversal_dq // 輸出: -1 0 1 2 3

    // dq.insert(pos, x) 在deque的指定位置插入元素
    dq.insert(dq.begin()+2, 999);  //在index=2的位置插入元素
    Traversal_dq // 輸出: -1 0 999 1 2 3


    {// 二維陣列中新增元素
    deque<deque<int>> dd;
    dd.push_back(deque<int>{1,2,3});
    dd.push_back(deque<int>{4,5,6});
    for (const auto& i : dd){
        for (const int& j : i) cout<<j<<' ';
        cout<<endl;
    }
    /*
    輸出:
    1 2 3
    4 5 6
    */}


    cout<<("======================\n");// 分隔線


    // 2. 存取 ([i] .at(i) .front() .back())
    // 注意: deque沒有 data() 函式(因為底層記憶體不連續，無法回傳單一連續陣列的指標)

    dq = {1,2,3,4,5};

    // 使用 dq[i] 來存取
    dq[0] = 999;  //將index=0位置的元素改為999
    cout<< dq[0] <<endl;  // 輸出: 999

    // 使用 dq.at(i) 來存取
    // .at(i) 會先做邊界檢查
    dq.at(1) = 111;
    cout<< dq.at(1) <<endl;  // 輸出: 111

    // 邊界檢查範例
    try {
        cout << dq.at(99) << endl;  // 超出範圍
    } catch (const std::out_of_range &e) {
        cout << "錯誤：" << e.what() << endl;
        // 輸出: 錯誤：deque::_M_range_check: __n (which is 99)>= this->size() (which is 5)
        // 注意: 此訊息內容為 libstdc++(GCC) 的實作細節，並非C++標準規範(這裡"99)"與">="之間甚至沒有空格，
        //       是libstdc++原始碼格式字串的寫法，並非筆誤)，換到 MSVC 等其他編譯器可能會顯示不同文字
    }

    // 使用 dq.front()與dq.back() 來存取
    dq.front() = 2026; //取第一個元素，等同於存取dq[0]
    cout<< dq.front() <<endl;  // 輸出: 2026

    dq.back() = 1234;  //取最後一個元素
    cout<< dq.back() <<endl;  // 輸出: 1234

    Traversal_dq // 遍歷輸出: 2026 111 3 4 1234

    cout<<("======================\n");// 分隔線

    // 3. 刪除

    // 現在deque dq中有5個元素 {2026, 111, 3, 4, 1234}

    // 用 dq.erase(pos) 刪除指定位置的元素
    dq.erase(dq.begin()+1);  // 刪除第二個元素(111)
    Traversal_dq // 輸出: 2026 3 4 1234

    dq.erase(dq.begin(), dq.begin()+2); // 刪除第一到第二個元素(不含第三個)
    Traversal_dq // 輸出: 4 1234

    // 用 dq.pop_back() 刪除最後一個元素
    dq.pop_back();
    Traversal_dq // 輸出: 4

    // 用 dq.pop_front() 刪除第一個元素 (vector沒有這個函式)
    dq.push_front(100);
    Traversal_dq // 輸出: 100 4
    dq.pop_front();
    Traversal_dq // 輸出: 4

    // 用 dq.clear() 清空 deque
    dq.clear();
    Traversal_dq // 輸出:     (沒有元素，清空了)

    // 刪除指定元素
    dq = {1,2,3,4,5};
    dq.erase(find(dq.begin(), dq.end(), 3));
    Traversal_dq  // 輸出: 1 2 4 5


    {// 二維deque的刪除
    deque<deque<int>> dd = {{1,2}, {3,4}, {5,6}};

    dd.erase(dd.begin()); //刪除第一列 {1,2}
    Traversal_dd
    /*
    輸出:
    3 4
    5 6
    */

    dd[0].erase(dd[0].begin()); //刪除第一列的第一個元素 3
    Traversal_dd
    /*
    輸出:
    4
    5 6
    */

    dd.clear();
    Traversal_dd // 輸出:     (沒有元素，清空了)

    }
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 遍歷》

    deque<int> dq = {1,2,3,4,5};

    // 1. 基本for迴圈
    for (int i=0; i<dq.size(); i++){
        cout<< dq[i] << ' ';
    }
    cout<<endl;
    // 輸出: 1 2 3 4 5


    // 2. 使用「以範圍為基礎的 for 語句」（Range-based for Statement）
    for (int element : dq){
        cout<< element << ' ';
    }
    cout<<endl;
    // 輸出: 1 2 3 4 5


    // 3. 若想更進一步修改元素值，可以改為用element作為deque dq 中的元素的參考(reference)
    for (int& element : dq){
        element += 1;
    }
    Traversal_dq  // 輸出: 2 3 4 5 6


    // 4. 使用迭代器(iterator)遍歷
    // deque的iterator屬於「隨機存取迭代器 (Random Access Iterator)」，與vector相同，支援it+n、it1-it2等運算
    for (deque<int>::iterator it = dq.begin(); it != dq.end(); it++){
        cout<< *it << ' ';
    }
    cout<<endl;
    // 輸出: 2 3 4 5 6
}
cout<<("====================================\n");// 分隔線
{
    //《4. 常用功能》

    deque<int> dq = {1,2,3,4};

    // 取得陣列長度(元素個數)
    int n = dq.size();
    cout<< n <<endl;  // 輸出: 4

    // 注意: deque「沒有」capacity()與reserve()函式
    // 原因: deque底層由多個區塊(chunk)組成，並非單一連續記憶體，因此沒有vector那種「容量」概念

    // 判斷陣列是否為空
    cout<< dq.empty() <<endl;  // 輸出: 0 (表示非空)

    // 調整大小: dq.resize(n) 或 dq.resize(n, val)
    dq.resize(6);       // 長度不足時，用預設值0補齊
    Traversal_dq // 輸出: 1 2 3 4 0 0

    dq.resize(8, 9);     // 長度不足時，用指定值9補齊
    Traversal_dq // 輸出: 1 2 3 4 0 0 9 9

    dq.resize(3);        // 長度超過時，直接從尾端截斷
    Traversal_dq // 輸出: 1 2 3

    // 交換兩個陣列的內容
    deque<int> dq1={1,2,3}, dq2={7,8,9};
    dq1.swap(dq2);
    cout<<"dq1: ";
    for (const int& i:dq1) cout<<i<<' ';cout<<endl;  //輸出: dq1: 7 8 9

    cout<<"dq2: ";
    for (const int& i:dq2) cout<<i<<' ';cout<<endl;  //輸出: dq2: 1 2 3



    // 搭配 <algorithm> 使用 (deque支援隨機存取迭代器，因此sort/reverse等演算法皆可正常使用)

    // 交換單個陣列中的兩個元素的位置
    dq = {1,2,3,4,5};
    swap(dq[0],dq[4]);
    Traversal_dq  //輸出: 5 2 3 4 1

    // 排序
    dq = {5,4,3,2,1};
    sort(dq.begin(), dq.end());  // 由小到大排序
    Traversal_dq  //輸出: 1 2 3 4 5

    sort(dq.begin(), dq.end(), greater<int>());  //由大到小排序
    // 也可以改用Lambda表達式: [](int a, int b) { return a > b; }
    Traversal_dq  //輸出: 5 4 3 2 1

    // 反轉
    dq = {1,3,5,7,9};
    reverse(dq.begin(), dq.end());
    Traversal_dq  //輸出: 9 7 5 3 1

    // 尋找元素的位置
    dq = {1,3,5,7,9};
    auto it = find(dq.begin(), dq.end(), 5);  // it 為指向該元素的迭代器(iterator)
    //若沒找到會回傳 dq.end()
    if (it != dq.end()){
        cout<<"Found "<< *it <<endl;
        cout<<"It's at index "<< distance(dq.begin(), it) <<endl;
    }
    else{
        cout<<"Not found"<<endl;
    }
    /*
    輸出:
    Found 5
    It's at index 2
    */

    // 計算某值的出現次數
    dq = {1,1,1,2};
    int cnt = count(dq.begin(), dq.end(), 1);
    cout<< cnt <<endl;  //輸出: 3


    // 搭配 <numeric> 使用

    dq = {10,20,30};

    // 加總
    int sum = accumulate(dq.begin(), dq.end(), 0); // 最後的0代表初始值為0
    cout<< sum <<endl;  //輸出: 60

    // 連乘
    int product = accumulate(dq.begin(), dq.end(), 1, [](int a, int b){return a*b;});
    cout<< product <<endl;  //輸出: 6000


    cout<<("======================\n");// 分隔線


    // emplace系列: emplace_back / emplace_front / emplace
    // 功能與push_back / push_front / insert類似，但是「直接在容器內部建構元素」，可省去一次額外的複製或搬移
    dq = {1,2,3};
    dq.emplace_back(4);              // 相當於 dq.push_back(4)
    dq.emplace_front(0);             // 相當於 dq.push_front(0)
    dq.emplace(dq.begin()+2, 999);   // 相當於 dq.insert(dq.begin()+2, 999)
    Traversal_dq // 輸出: 0 1 999 2 3 4


    cout<<("======================\n");// 分隔線


    // shrink_to_fit(): 要求釋放多餘的記憶體空間 (僅為「請求」，實際是否釋放由編譯器/標準函式庫實作決定)
    dq = {1,2,3,4,5};
    dq.shrink_to_fit();
    Traversal_dq  // 輸出: 1 2 3 4 5 (內容不變，僅嘗試釋放多餘記憶體，不影響元素)
}
}


// Generated by Claude 20260824 (https://claude.ai/share/9daf8235-5316-48fa-b7cc-7d9e24cede12)