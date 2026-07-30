#include<vector>  //需引入vector標頭檔

#include<iostream>
#include<algorithm>
#include<numeric>
#include <stdexcept>  // std::out_of_range 定義在 <stdexcept> 標頭檔中
using namespace std;

// 我使用Traversal_v來表示遍歷vector v的輸出結果
#define Traversal_v for (const int& i:v) cout<<i<<' '; cout<<endl;
// 我使用Traversal_vv來表示遍歷vector vv(即二維vector陣列)的輸出結果
#define Traversal_vv for (const auto i:vv){for (const int j:i)cout<<j<<' ';cout<<endl;}

/*
前言: vector的特色、用途

相較於必須在宣告時就「確定陣列大小」的傳統陣列(如 int Array[5];)
vector是一個動態陣列，可以在執行期「自動調整大小」，比傳統陣列更安全、更方便
*/


int main(){
{
    // 《1. vector的宣告》
    
    // 建立空的vector，可以用於儲存整數(int)，名稱為v1
    vector<int> v1;
    
    // 建立可容納五個整數的 vector， 每個元素值預設是 0
    vector<int> v2(5);  // {0, 0, 0, 0, 0}

    // 建立可容納五個整數的 vector， 每個元素值預設是 10
    vector<int> v3(5, 10);  // {10, 10, 10, 10, 10}

    // 初始化包含元素的 vector，自動設定陣列長度
    vector<int> v4 = {1, 2, 3, 4};  //v4的長度為 4
    
    // 複製建構，v4與v5會互相獨立
    vector<int> v5(v4);  //v5為{1, 2, 3, 4}

    // 建立 3x2 的二維vector，每個內層vector初始化為 {1, 2}
    vector<vector<int>> v6(3, vector<int>{1,2});  // {{1,2}, {1,2}, {1,2}}
    // 這裡的vector<int>{1,2}，代表一個臨時創建的一維vector，並且包含 1,2 兩個元素
    /* 同理，也可以改為vector<int>(3,0)，代表一個臨時創建的一維vector，包含3個元素且初始值皆為0
       那麼v6就會變成 {{0,0,0}, {0,0,0}, {0,0,0}} */


    // 也可以直接初始化二維vector
    vector<vector<int>> v7 = {{1,2}, {3,4,5}, {6,7,8,9}};
}
//===============================分隔線===============================
{
    // 《2. vector的新增、存取與刪除》

    vector<int> v;  // 建立一個空的vector

    // 1. 新增 (push_back與insert)

    // v.push_back(x) 在vector的尾端新增元素
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    Traversal_v // 遍歷輸出: 1 2 3
    

    // v.insert(pos, x) 在vector的指定位置插入元素
    v.insert(v.begin(), 123);  //在開頭插入元素
    Traversal_v // 輸出: 123 1 2 3 
    
    v.insert(v.begin()+1, 456);  //在開頭的下一個位置插入元素
    Traversal_v // 輸出: 123 456 1 2 3 


    {// 二維陣列中新增元素
    vector<vector<int>> vv;
    vv.push_back(vector<int>{1,2,3});
    vv.push_back(vector<int>{4,5,6});
    for (const auto& i : vv){
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

    // 使用 v[i] 來存取
    v[0] = 999;  //將index=0位置的元素改為999
    cout<< v[0] <<endl;  // 輸出: 999


    // 使用 v.at(i) 來存取
    // .at(i) 會先做邊界檢查
    v.at(1) = 111;
    cout<< v.at(1) <<endl;  // 輸出: 111

    // 邊界檢查範例
    try {
        cout << v.at(99) << endl;  // 超出範圍
    } catch (const std::out_of_range &e) {
        cout << "錯誤：" << e.what() << endl;
        // 輸出: 錯誤：vector::_M_range_check: __n (which is 99) >= this->size() (which is 5)
    }


    // 使用 v.front()與v.back() 來存取
    v.front() = 2026; //取第一個元素，等同於存取v[0]
    cout<< v.front() <<endl;  // 輸出: 2026

    v.back() = 1234;  //取最後一個元素
    cout<< v.back() <<endl;  // 輸出: 1234

    Traversal_v // 遍歷輸出: 2026 111 1 2 1234 

    cout<<("======================\n");// 分隔線

    // 3. 刪除

    // 現在vector v中有5個元素 {2026, 111, 1, 2, 1234}

    // 用 v.erase(pos) 刪除指定位置的元素
    v.erase(v.begin()+1);  // 刪除第二個元素(111)
    Traversal_v // 輸出: 2026 1 2 1234

    v.erase(v.begin(), v.begin()+2); // 刪除第一到第三個元素(不含第三個)
    Traversal_v // 輸出: 2 1234

    // 用 v.pop_back() 刪除最後一個元素
    v.pop_back();
    Traversal_v // 輸出: 2

    // 用 v.clear() 清空 vector
    v.clear();
    Traversal_v // 輸出:     (沒有元素，清空了)


    {// 二維vector的刪除
    vector<vector<int>> vv = {{1,2}, {3,4}, {5,6}};

    vv.erase(vv.begin()); //刪除第一列 {1,2}
    Traversal_vv 
    /*
    輸出:
    3 4 
    5 6 
    */

    vv[0].erase(vv[0].begin()); //刪除第一列的第一個元素 3
    Traversal_vv
    /*
    輸出:
    4
    5 6
    */

    vv.clear();
    Traversal_vv // 輸出:     (沒有元素，清空了)

    }
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 遍歷》

    vector<int> v = {1,2,3,4,5};

    // 1. 基本for迴圈
    for (int i=0; i<v.size(); i++){
        cout<< v[i] << ' ';
    }
    cout<<endl;
    // 輸出: 1 2 3 4 5


    // 2. 使用「以範圍為基礎的 for 語句」（Range-based for Statement）
    //    亦可稱為「for-each loop」
    for (int element : v){
        cout<< element << ' ';
    }
    cout<<endl;
    // 輸出: 1 2 3 4 5
    /*
    語句解釋:
    在這個for迴圈中，我宣告一個整數變數element，用來儲存目前遍歷到的元素
    並在每一輪迴圈中輸出目前讀取到的元素值

    如果你學過Python，你也可以把 for(int element : v) 看成 for element in v
    
    逐步解析:
    在第一輪迴圈中，我從vector v中的第一個元素開始讀取，並將v[0]的值複製給element
    接著輸出element的值(即v[0]的值)

    在第二輪迴圈中，我接著讀取v[1]的值，並將其複製給element
    ...
    直到讀取完vector v 中的最後一個元素，迴圈結束
    */


    // 3. 在for-each loop的基礎之上，若想更進一步修改元素值，可以改為用element作為vector v 中的元素的參考(reference)
    for (int& element : v){
        element += 1;
    }
    Traversal_v  // 輸出: 2 3 4 5 6
    /*
    語句解釋:
    在這個迴圈中，我宣告一個整數的「參考變數」element，用來儲存目前遍歷到的元素的參考
    並在每一輪的迴圈中利用element間接修改vector v 中對應元素的值
    */
}
cout<<("====================================\n");// 分隔線
{
    //《4. 常用功能》
    
    vector<int> v = {1,2,3,4};

    // 取得陣列長度(元素個數)
    int n = v.size();
    cout<< n <<endl;  // 輸出: 4

    // 取得陣列容量(目前配置的記憶體大小)
    vector<int> Nums;
    for (int i=0; i<10; i++){
        cout<< Nums.capacity() << ' ';
        Nums.push_back(1);
    }cout<<endl;
    // 輸出:         0 1 2 4 4 8 8 8 8 16 
    // 對應元素個數:  0 1 2 3 4 5 6 7 8 9
    // 此輸出結果僅適用於 GCC/libstdc++，不同編譯器（如 MSVC）的成長策略不同，結果可能不同

    // 判斷陣列是否為空
    cout<< v.empty() <<endl;  // 輸出: 0 (表示非空)

    // 交換兩個陣列的內容
    vector<int> v1={1,2,3}, v2={7,8,9};
    v1.swap(v2);
    cout<<"v1: ";
    for (const int& i:v1) cout<<i<<' ';cout<<endl;  //輸出: v1: 7 8 9

    cout<<"v2: ";
    for (const int& i:v2) cout<<i<<' ';cout<<endl;  //輸出: v2: 1 2 3

    



    // 搭配 <algorithm> 使用

    // 交換單個陣列中的兩個元素的位置
    v = {1,2,3,4,5};
    swap(v[0],v[4]);
    Traversal_v  //輸出: 5 2 3 4 1

    // 排序
    v = {5,4,3,2,1};
    sort(v.begin(), v.end());  // 由小到大排序
    Traversal_v  //輸出: 1 2 3 4 5

    sort(v.begin(), v.end(), greater<int>());  //由大到小排序
    // 也可以改用Lambda表達式: [](int a, int b) { return a > b; }
    Traversal_v  //輸出: 5 4 3 2 1

    // 反轉
    v = {1,3,5,7,9};
    reverse(v.begin(), v.end());
    Traversal_v  //輸出: 9 7 5 3 1

    // 尋找元素的位置
    v = {1,3,5,7,9};
    auto it = find(v.begin(), v.end(), 5);  // it 為指向該元素的迭代器(iterator)
    //若沒找到會回傳 v.end()
    if (it != v.end()){
        cout<<"Found "<< *it <<endl;
        cout<<"It's at index "<< distance(v.begin(), it) <<endl;
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
    v = {1,1,1,2};
    int cnt = count(v.begin(), v.end(), 1);
    cout<< cnt <<endl;  //輸出: 3


    // 搭配 <numeric> 使用

    v = {10,20,30};

    // 加總
    int sum = accumulate(v.begin(), v.end(), 0); // 最後的0代表初始值為0
    cout<< sum <<endl;  //輸出: 60

    // 連乘
    int product = accumulate(v.begin(), v.end(), 1, [](int a, int b){return a*b;});
    cout<< product <<endl;  //輸出: 6000
}
}


// 本篇筆記參考Claude (https://claude.ai/share/9d11481c-8a88-4443-94ab-67d5b45b3226)
// 本篇筆記參考Luke Tseng 【C++ 筆記】vector - part 16 (https://hackmd.io/@LukeTseng/H1ZqX9RHkl)
// Created by B.J.Wang 2026/7/28