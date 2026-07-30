#include<utility>  // 需引入utility標頭檔才能使用pair

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

/*
前言: 什麼是pair?用途?

我們可以用pair來儲存兩個（可能不同型別）的值，將它們當成一個整體來使用
例如我想用一對pair來表達水果與編號
可以寫為
pair<int, string> p1 = {1, "apple"};
pair<int, string> p2 = {2, "banana"};

能更方便地處理數據
*/

int main(){
{
    //《1. pair的宣告》

    // 1. 預設建構（元素會初始化為預設值，即0,空字串,nullptr等）
    pair<int, string> p1;

    // 2. 直接初始化(大小括號皆可)
    pair<int, string> p2_1(1, "apple");
    pair<int, string> p2_2{2, "cherry"};

    // 3. 使用 make_pair函式（會自動推導型別）
    auto p3 = make_pair(3, "banana");
    // 需注意: 這裡的banana自動推導出的型別不是string，是PKc(即const char*)

    // 4. 使用 = 賦值（型別需相符或可轉換）
    pair<int, string> p4 = {4, "date"};

        /*
        補充: 何謂可轉換

        定義: 即使你提供的值型別跟 pair 宣告的型別不完全一樣，只要存在隱式轉換路徑，編譯器就會自動幫你轉換

        舉例:   pair<double, int> p = {4, 3.9};
                // 4    是 int    → 隱式轉換成 double → 4.0
                // 3.9  是 double → 隱式轉換成 int    → 3（小數被截斷，會有 warning）
                
                cout << p.first << " " << p.second << endl;
                // 輸出：4 3
        */

    // 5. 宣告二維pair
    pair<int, pair<int, int>> p5_1;
    pair<int, pair<int, int>> p5_2 = {1, {2,3}};
    
    auto p5_3 = make_pair(1, make_pair(2,3));

}
//===========================分隔線=========================
{

    //《2. 存取》
    // 每個pair都有兩個可以直接存取的公開的資料成員(public member) : first 與 second

    // 1. 存取一維pair
    pair<int, string> p1(10, "hello");
    cout << p1.first << " " << p1.second << endl;  //輸出: 10 hello

    p1.first = 20;       // 可以直接修改
    p1.second = "apple";

    auto [num, word] = p1;  // 這個語法只有 C++17（含）以後才能編譯
    cout << num << ' ' << word <<endl;  //輸出: 20 apple


    // 2. 存取二維pair
    pair<int ,pair<int, int>> p2 = {1, {2, 3}};
    cout<< p2.first << ' ' << p2.second.first << ' ' << p2.second.second <<endl;  //輸出: 1 2 3
    // 注意: 若想直接輸出p2.second，需要自己實作運算子多載(operator overloading)，詳情見補充一
}
cout<<("====================================\n");// 分隔線
{

    // 《3. 比較》
    //  pair 已經內建 == != < <= > >= 運算子，比較規則是先比較 first，若相同再比較 second

    //範例
    pair<int, int> p1={1,2}, p2={1,4};
    cout<< (p1==p2) <<endl;  //輸出: 0
    cout<< (p1!=p2) <<endl;  //輸出: 1
    cout<< (p1<p2)  <<endl;  //輸出: 1
    cout<< (p1<=p2) <<endl;  //輸出: 1
    cout<< (p1>p2)  <<endl;  //輸出: 0
    cout<< (p1>=p2) <<endl;  //輸出: 0


    //排序
    vector<pair<int,int>> v = {{2,1}, {1,100}, {1,2}};
    sort(v.begin(), v.end());
    for (auto i:v) cout<<'{'<<i.first<<','<<i.second<<"} ";
    // 輸出: {1,2} {1,100} {2,1} 
}
}


// 本篇筆記參考Claude (https://claude.ai/share/5e1cb6ef-360f-4c78-92dd-188d9349c780)
// 本篇筆記參考DSA紀錄坊 (https://hackmd.io/@DSArecorder/B1BKLKkq2)
// Created by B.J.Wang 2026/7/26