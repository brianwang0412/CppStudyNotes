#include<map>  // 需引入<map>標頭檔

#include<iostream>
#include<string>
#include<stdexcept>
#include<utility>
using namespace std;

/*
前言: map的特性

1. 每個元素皆為pair鍵值對 pair<const Key, Value>
2. 依照 Key 自動排序（預設由小到大）
3. Key 不可重複
4. 插入、刪除、搜尋的時間複雜度皆為 O(log n)，底層邏輯為紅黑樹
*/

int main(){
{
    // 《1. map的宣告》

    // 建立空的map
    map<string, int> m1;

    // 初始化
    map<string, int> m2 = {{"water", 1}, {"soda", 20}};

    // 複製建構
    map<string, int> m3(m2);

    // 自訂排序方式 (改成以key值由大到小)
    map<string, int, greater<string> > m4 = {{"apple", 999}, {"banana", 1}};
    for (auto& i:m4) cout<<i.first<<' '<<i.second<<endl;
    /*
    輸出:
    banana 1
    apple 999
    */
}   

cout<<("======================\n");// 分隔線

{
    // 《2. 存取》
    // 只能用Key去找Value
    // 若想用Value找Key需要遍歷整個map

    map<string, int> mp = {{"apple", 5}, {"banana", 3}} ;

    // 使用 mp[Key] 來存取
    // 若Key不存在會自動建立並給予預設值，再賦值
    cout<< mp["apple"] <<endl;  // 輸出: 5
    mp["apple"] = 111;  // 修改{"apple", 5}的值
    cout<< mp["apple"] <<endl;  // 輸出: 111

    cout<< mp["cherry"] <<endl;  // 輸出: 0 （會自動建立 key="cherry", value=0）

    // 使用 mp.at(Key) 來存取
    // key 不存在時會拋出 std::out_of_range 例外，不會新增 key，較安全
    cout<< mp.at("banana") <<endl;  // 輸出: 3

    try{
        cout<< mp.at("egg") <<endl;
    }catch (const std::out_of_range& e){
        cout<< "error: " << e.what() <<endl;
    }
    // 輸出: error: map::at
    // 注意: 此訊息內容為 libstdc++(GCC) 的實作細節，並非C++標準規範，
    //       換到 MSVC 等其他編譯器可能會顯示不同文字

    // 使用 mp.find(Key) 來找到指定元素
    // 回傳指向該元素的 迭代器(iterator)，找不到則回傳 mp.end()
    // 不會新增 key，是最推薦的查詢方式
    map<string, int>::iterator it = mp.find("banana");  //banana存在，回傳指向{banana, 3}的iterator
    if (it != mp.end()){
        cout<< it->first << " : " << it->second <<endl;
    }
    // 輸出: banana : 3

    auto it_2 = mp.find("mango");  // mango不存在，回傳mp.end()
    if (it_2 == mp.end()){
        cout<< "mango does not exist" <<endl;
    }

    // 使用 mp.count(Key) 來取得該Key在mp中存在的個數
    // 由於map中Key不得重複，因此也可視作確認Key是否存在
    cout << mp.count("apple") << endl;   // 輸出: 1 (map中key不重複，只會是0或1)
    cout << mp.count("fruit") << endl;  // 輸出: 0
}

cout<<("======================\n");// 分隔線

{
    // 《3. 新增》

    map<string, int> mp;

    // 使用 mp[Key]=Value 來新增
    mp["apple"] = 1;  // 新增動作 : 此時mp內還沒有"apple"，所以新增{"apple", 1}
    mp["apple"] = 2;  // 修改動作 : 此時mp內已有{"apple", 1}，將其改為{"apple", 2}
    cout<< mp["apple"] <<endl;  // 輸出: 2


    // 使用 mp.insert( {Key, Value} ) 來新增
    // 不會覆蓋已存在的 key，回傳 pair<iterator, bool>，bool 表示是否新增成功
    auto result_1 = mp.insert({"banana", 123});
    cout<< mp["banana"] <<endl;  // 輸出: 123
    cout<< result_1.second <<endl;  //輸出: 1 (代表成功新增)

    auto result_2 = mp.insert({"banana", 999});
    cout<< mp["banana"] <<endl;  // 輸出: 123
    

    // 使用 mp.emplace(Key, Value) 來新增
    // 與insert同樣不會覆蓋已有元素
    // 理論上效率較insert高（省去臨時pair的複製/搬移），但差異在value為簡單型別時通常不明顯
    // 在value為複雜物件時效益較顯著
    mp.emplace("grape", 8);
    mp.emplace("grape", 99); // key 已存在，不會覆蓋

    cout << mp["grape"] << endl; // 輸出: 8
}

cout<<("======================\n");// 分隔線

{
    // 《4. 刪除》

    map<string, int> mp = {{"apple", 3}, {"banana", 5}, {"cherry", 7}, {"date", 9}};

    // 用 mp.erase(Key或iterator) 刪除指定元素

    // 依 key 刪除 (回傳刪除的數量)
    int Erase_num = mp.erase("apple");
    cout<< Erase_num <<endl;  // 輸出: 1 (表示成功刪除1個Key為"apple"的元素)
    // 剩下: banana=5, cherry=7, date=9

    // 依 iterator 刪除 (回傳刪除元素的後一個元素的迭代器)
    auto it = mp.find("banana");
    auto next = mp.erase(it);
    cout<< next->first <<':'<< next->second <<endl;
    // 輸出: cherry:7 (表示成功刪除，且下一個元素為{"cherry", 7})
    // 剩下: cherry=7, date=9

    // 範圍刪除（此例為全部刪除）
    /*
    參數：first 與 last 兩個迭代器，刪除區間 [first, last)
    回傳型態：iterator（指向最後被刪除元素之後的元素，即原先 last 指向的位置)
    */
    it = mp.erase(mp.begin(), mp.end());
    cout<< (it==mp.end()) <<endl;  // 輸出: 1 (表示it是mp.end())
    // 剩下: 空的


    // 用 mp.clear() 清空整個map

    mp = {{"apple", 3}, {"banana", 5}};
    mp.clear();                   // 清空整個 map
    cout << mp.size() << endl;    // 輸出: 0
}

cout<<("======================\n");// 分隔線

{
    // 《5. 遍歷》
    //  Tip: map內的元素是pair

    map<string, int> mp = {{"banana", 5}, {"apple", 3}, {"cherry", 7}};

    // 方法一：使用 迭代器iterator
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }cout<<endl;

    // 方法二：使用 range-based for statement
    for (const auto& p : mp) {
        cout << p.first << ": " << p.second << endl;
    }cout<<endl;

    // 方法三：C++17 結構化綁定
    for (const auto& [key, value] : mp) {
        cout << key << ": " << value << endl;
    }

    /*
    三個方法的輸出皆相同
    輸出（自動依 key 排序）:
    apple: 3
    banana: 5
    cherry: 7
    */
}

cout<<("======================\n");// 分隔線

{
    // 《6. 常用函式》
    
    map<int ,string> mp = {{1, "one"}, {3, "three"}, {2, "two"}};
    map<int, string> mp2;

    // 1. 判斷 map 是否為空
    bool IsEmpty = mp.empty();
    cout<< IsEmpty <<endl;  // 輸出: 0 (表示非空)

    IsEmpty = mp2.empty();
    cout<< IsEmpty <<endl;  // 輸出: 1 (表示此map是空的)


    // 2. 取得 map 的大小(元素個數)
    int N = mp.size();
    cout<< N <<endl;  // 輸出: 3  (mp內含三個元素)

    N = mp2.size();
    cout<< N <<endl;  // 輸出: 0


    // 3. 邊界查詢 (lower_bound / upper_bound / equal_range)
    
    mp = {{1, "one"}, {3, "three"}, {5, "five"}, {7, "seven"}, {9, "nine"}};

    // mp.lower_bound(k) : 回傳第一個 Key值>= k 的元素，回傳指向該元素的iterator，若超出範圍則回傳mp.end()
    // 重點: 大於或等於(>=)
    auto lb = mp.lower_bound(4); 
    cout << (*lb).first << ':' << lb->second <<endl;   // 輸出: 5:five
    // ptr-> 等同於 (*ptr).
    
    // mp.upper_bound(k) : 回傳第一個 Key值> k 的元素，回傳指向該元素的iterator，若超出範圍則回傳mp.end()
    // 重點: 大於(>)
    auto ub = mp.upper_bound(5); // 第一個Key值 > 5 的元素
    cout << ub->first << ':' << (*ub).second << endl;   // 輸出: 7:seven

    // mp.equal_range(k) : 回傳 pair {lower_bound(k), upper_bound(k)}
    auto eq = mp.equal_range(3);  // {lower_bound(3), upper_bound(3)
    cout << eq.first->first << " " << eq.second->first << endl;  // 輸出: 3 5
}
}

/*
補充: 怎麼判斷什麼時候要用 dot(.) 跟 arrow(->)

以map為例
當我們使用range-based for statement時
此時 for (const auto& p:mp) 這裡的 p 存取 mp 中每一個元素，這些元素的型別為pair
因此此時 p 為 pair，我們可以直接用 dot(.) 來存取公開成員 first 與 second
例如 cout<< p.first << ':' << p.second <<endl;

而當我們使用 迭代器(iterator) 時
此時 auto it = mp.find("banana"); 我們可以將 it 視為指向 {"baanana", 3} 的pointer(指標) (假設該元素存在)
若想使用 it 需將其解參考(*) 後配合dot(*) 使用
即 cout<< (*it).first << ':' << (*it).second <<endl;
可以用 arrow(->) 來簡化程式碼
即寫為 cout<< it->first << ':' << it->second << endl;
*/


// 本篇筆記參考 ShengYu Talk - C++ std::map 用法與範例(https://shengyu7697.github.io/std-map/)
// 本篇筆記參考 Claude (https://claude.ai/share/d681640f-0e5f-47e2-8a02-4fab8fb724c4)
// Created by B.J.Wang 2026/8/4