#include<iostream>
#include<vector>
#include<map>
using namespace std;

/*
前言: iterator(迭代器)的簡介與作用

iterator(迭代器)是一種類指標（pointer-like）的物件，指向 STL container 的元素
與pointer(指標)不同的是，iterator(迭代器)能夠處理非連續記憶體的容器(如: map, list, unordered_set)

我們可以使用迭代器來「以相同/統一的方式存取」各種容器
不論是「連續記憶體」還是「不連續記憶體」都可以

你可以試著想想該如何遍歷一個鍵值對(key-value)的容器(如map，即Python中的Dictionary)
*/

int main(){
{cout<<"《使用 iterator 走訪 vector (連續記憶體容器)》"<<endl;
    
    //《使用 iterator 走訪 vector (連續記憶體容器)》

    vector <int> v = {1, 2, 3, 4, 5};

    {// 1. 宣告迭代器
    vector<int>::iterator it = v.begin();
    // 也可以寫為 auto it = v.begin();
    

    // 2. 基本走訪操作

    // 〈 *it 〉	取出目前位置的元素。
    // 〈 ++it 〉	移動到下一個元素。

    cout << *it <<endl;  // 輸出: 1 (v.begin()位置的元素，即第一個元素)
    ++it; // 移動到下一個位置
    cout << *it <<endl;  // 輸出: 2 (第二個元素)

    // 〈 it1==it2 〉 比較兩個迭代器是否指向同一位置
    auto it1 = v.begin();
    auto it2 = v.begin();

    cout<< (it1==it2) <<endl;  // 輸出: 1 (表示兩者指向相同位置)
    ++it1;
    it1++;   // 通過兩次移動讓 it1 指向第三個位置
    cout<< (it1==it2) <<endl;  // 輸出: 0 (表示兩者指向不同位置)
    ++++it2; // 通過兩次移動讓 it2 指向第三個位置
    cout<< (it1==it2) <<endl;  // 輸出: 1 (表示兩者指向相同位置)
    
    // 用 iterator 與 for迴圈 遍歷 vector
    for (vector<int>::iterator it=v.begin() ; it!=v.end() ; ++it){
        cout<< *it << ' ';
    }
    cout<<endl;
    // 輸出: 1 2 3 4 5 

    // 補充: 唯讀迭代器(const iterator)
    // 只能讀取，無法修改
    for (vector<int>::const_iterator cit=v.cbegin(); cit!=v.cend(); ++cit){
        cout<< *cit << ' ';
    }
    cout<<endl;
    //輸出: 1 2 3 4 5
}
cout<<("====================================\n");// 分隔線

    // 隨機存取迭代器(Random Access Iterator)
    // 這是連續記憶體容器的典型迭代器，特色是不需要逐格走訪，可以跳著走(it+n / it-n)

    v = {1,2,3,4,5,6,7,8,9};
    vector<int>::iterator it=v.begin();
    cout<< *it     <<endl;  //輸出: 1
    cout<< *(it+3) <<endl;  //輸出: 4
    
    // 可以一次前進五格
    it += 5;
    cout<< *it <<endl;  //輸出: 6

    // 可以用 operator[] 來存取(以當前指向的元素位置作為 it[0])
    cout<< it[0] <<endl;  //輸出: 6
    cout<< it[1] <<endl;  //輸出: 7
    cout<< it[-1] <<endl; //輸出: 5

    vector<int> v2 = {5,4,3,2,1};
    auto it1=v2.begin();
    auto it2=v2.end()-1;

    cout << (it1<it2) <<endl;  //輸出: 1  (表示it1在it2之前)
    //這裡比的是迭代器所指向的「位置」在序列中的先後順序(即it1是否在it2之前)，與元素值無關

    // 計算兩個iterator間的距離
    cout<< v2.end() - v2.begin() <<endl;  //輸出: 5  (表示v2有五個元素)

cout<<("====================================\n");// 分隔線

    // 3. 反向走訪

    v = {1,2,3,4,5,6,7,8,9};

    // 宣告反向迭代器
    vector<int>::reverse_iterator rit = v.rbegin();
    // 也可以寫為 auto rit = v.rbegin();

    // 用 反向迭代器 與 for迴圈 反向遍歷
    for (rit=v.rbegin(); rit!=v.rend(); rit++){
        cout<< *rit <<' ';
    }cout<<endl;
    // 輸出: 9 8 7 6 5 4 3 2 1 
    
    // 用 一般迭代器 與 for迴圈 反向遍歷
    for (auto it_2=v.end(); it_2!=v.begin(); ){
        --it_2;
        cout<< *it_2 <<' ';
    }cout<<endl;
    // 輸出: 9 8 7 6 5 4 3 2 1


}
cout<<("====================================================\n");// 分隔線
{cout<<"《使用 iterator 走訪 map (不連續記憶體容器)》" <<endl;

    //《使用 iterator 走訪 map (不連續記憶體容器)》
    // 關鍵限制：不支援 it + n、it[n]、it < other 等 Random Access 操作。
    map<string,int> m = {{"Alice",85},{"Bob",70},{"Carol",92},{"David",60},{"Eve",78}};

    {// 1. 宣告迭代器
    map<string,int>::iterator it = m.begin();
    // 也可以寫為 auto it = m.begin();

    // 2. 基本走訪操作

    // 〈 *it 〉    取出目前位置的元素，型別是 pair<const string,int>
    // 〈 it->first / it->second 〉  分別取出 key 與 value
    // 〈 ++it 〉    移動到下一個元素(注意：是依照key排序後的下一個，不是插入順序)

    cout << it->first << ":" << it->second << endl;  // 輸出: Alice:85 (m.begin()位置的元素，key排序後最小的)
    ++it; // 移動到下一個位置
    cout << it->first << ":" << it->second << endl;  // 輸出: Bob:70 (key排序後第二小的)

    // 〈 it1==it2 〉 比較兩個迭代器是否指向同一位置
    auto it1 = m.begin();
    auto it2 = m.begin();

    cout<< (it1==it2) <<endl;  // 輸出: 1 (表示兩者指向相同位置)
    ++it1;
    it1++;   // 通過兩次移動讓 it1 指向第三個位置(依key排序)
    cout<< (it1==it2) <<endl;  // 輸出: 0 (表示兩者指向不同位置)
    ++++it2; // 通過兩次移動讓 it2 指向第三個位置
    cout<< (it1==it2) <<endl;  // 輸出: 1 (表示兩者指向相同位置)

    // 用 iterator 與 for迴圈 遍歷 map
    for (map<string,int>::iterator it=m.begin() ; it!=m.end() ; ++it){
        cout<< it->first << ":" << it->second << ' ';
    }
    cout<<endl;
    // 輸出: Alice:85 Bob:70 Carol:92 David:60 Eve:78
    // 注意：這個順序是"key的字母排序"，並非原本 {"Alice",85},{"Bob",70},... 的插入順序
    //       (雖然本例恰好插入順序與字母序相同，但這只是巧合)
    }

cout<<("====================================\n");// 分隔線

    // 雙向迭代器(Bidirectional Iterator)
    // 這是不連續記憶體容器的典型迭代器，特色是"只能"逐格走訪(++it / --it)，不能跳著走

    map<string,int>::iterator it = m.begin();
    cout<< it->first <<endl;  //輸出: Alice

    // it = it + 3; 是不合法的
    // map::iterator 沒有定義 operator+，因為紅黑樹節點記憶體不連續，無法用位址運算跳躍

    // 想要"前進n步"，必須用 std::advance，內部會逐格呼叫 ++it，時間複雜度 O(n)
    advance(it, 3);
    cout<< it->first <<endl;  //輸出: David (從Alice往前數3步：Alice→Bob→Carol→David)

    // 也可以用advance搭配負數"後退"n步(因為map是Bidirectional，支援--it)
    advance(it, -1);
    cout<< it->first <<endl;  //輸出: Carol

    // map沒有 operator[](int) 這種"依相對位移存取"的用法
    // 但注意：map本身另有自己的 operator[](const Key&)，是依"key值"存取，意義完全不同
    cout<< m["Bob"] <<endl;  //輸出: 70  (這是map容器自己的operator[]，不是iterator的)

    map<string,int>::iterator itA = m.begin();
    map<string,int>::iterator itB = m.begin();
    advance(itB, 2);

    // cout << (itA < itB) <<endl; 是不合法的
    // map::iterator 沒有定義 operator<，只能用 == 或 != 判斷是否指向同一位置

    cout<< (itA != itB) <<endl;  //輸出: 1  (只能用!=判斷是否為不同位置，無法比較先後大小)

    // 計算兩個iterator間的距離：map也沒有直接相減的operator-
    // 想知道距離，一樣得用std::distance，內部逐格++走過去計算，時間複雜度 O(n)
    cout<< distance(m.begin(), m.end()) <<endl;  //輸出: 5  (表示m有五個元素)

cout<<("====================================\n");// 分隔線

    // 3. 反向走訪

    // 宣告反向迭代器
    map<string,int>::reverse_iterator rit_1 = m.rbegin();
    // 也可以寫為 auto rit = m.rbegin();

    // 用 反向迭代器 與 for迴圈 反向遍歷
    for (auto rit_2=m.rbegin(); rit_2!=m.rend(); rit_2++){
        cout<< rit_2->first << ":" << rit_2->second << ' ';
    }cout<<endl;
    // 輸出: Eve:78 David:60 Carol:92 Bob:70 Alice:85
    // (依key由大到小，也就是字母的反向排序)

    // 用 一般迭代器 與 for迴圈 反向遍歷
    for (auto it_2=m.end(); it_2!=m.begin(); ){
        --it_2;
        cout<< it_2->first << ":" << it_2->second << ' ';
    }cout<<endl;
    // 輸出: Eve:78 David:60 Carol:92 Bob:70 Alice:85
}
}

// 本篇筆記參考 Claude (https://claude.ai/share/04ed6895-e42d-4309-a5a8-df932c34f439)
// 本篇筆記參考: Luke Tseng 【C++筆記】Iterator（迭代器）(https://hackmd.io/@LukeTseng/BkLL3USVex)
// Created by B.J.Wang 2026/7/29