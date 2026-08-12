#include<unordered_map>  // 需引入<unordered_map>標頭檔

#include<iostream>
#include<string>
#include<vector>
#include<utility>
using namespace std;

/*
前言: unordered_map的特性

1. 每個元素皆為pair鍵值對 pair<const Key, Value>，用法與map非常相似
2. 元素「不會」自動排序，順序取決於雜湊函式(hash function)的計算結果，順序不固定、不保證
3. Key 不可重複
4. 插入、刪除、搜尋的「平均」時間複雜度皆為 O(1)，最差情況(雜湊碰撞嚴重時)為 O(n)
   底層邏輯為雜湊表(hash table)，與map底層的紅黑樹不同

注意: 本篇筆記中「遍歷」相關的輸出結果，其元素順序取決於編譯器/標準函式庫的雜湊實作方式，
      並非C++標準規範保證的順序，換到不同編譯器或不同執行時間，順序都可能不同
      (本篇筆記的輸出結果皆為 GCC/libstdc++ 實際執行後的結果，僅供參考)
*/

int main(){
{
    // 《1. unordered_map的宣告》

    // 建立空的unordered_map
    unordered_map<string, int> m1;

    // 初始化
    unordered_map<string, int> m2 = {{"water", 1}, {"soda", 20}};

    // 複製建構
    unordered_map<string, int> m3(m2);

    // 用兩個iterator(迭代器)範圍建立unordered_map
    unordered_map<string, int> m4(m2.begin(), m2.end());

    // 可以在建構時指定「初始桶數(bucket數量)」，用於預先分配記憶體、減少rehash次數
    // (第二個參數為初始桶數的建議值，實際桶數會由標準函式庫調整為適合的質數或2的冪次，依實作而定)
    unordered_map<string, int> m5(10);
}   

cout<<("======================\n");// 分隔線

{
    // 《2. 存取》
    // 只能用Key去找Value
    // 若想用Value找Key需要遍歷整個unordered_map
    // 用法與map完全相同

    unordered_map<string, int> mp = {{"apple", 5}, {"banana", 3}};

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
    // 輸出: error: unordered_map::at
    // 注意: 此訊息內容為 libstdc++(GCC) 的實作細節，並非C++標準規範，
    //       換到 MSVC 等其他編譯器可能會顯示不同文字

    // 使用 mp.find(Key) 來找到指定元素
    // 回傳指向該元素的 迭代器(iterator)，找不到則回傳 mp.end()
    // 不會新增 key，是最推薦的查詢方式
    unordered_map<string, int>::iterator it = mp.find("banana");  //banana存在，回傳指向{banana, 3}的iterator
    if (it != mp.end()){
        cout<< it->first << " : " << it->second <<endl;
    }
    // 輸出: banana : 3

    auto it_2 = mp.find("mango");  // mango不存在，回傳mp.end()
    if (it_2 == mp.end()){
        cout<< "mango does not exist" <<endl;
    }

    // 使用 mp.count(Key) 來取得該Key在mp中存在的個數
    // 由於unordered_map中Key不得重複，因此也可視作確認Key是否存在
    cout << mp.count("apple") << endl;   // 輸出: 1 (key不重複，只會是0或1)
    cout << mp.count("fruit") << endl;  // 輸出: 0
}

cout<<("======================\n");// 分隔線

{
    // 《3. 新增》
    // 用法與map完全相同

    unordered_map<string, int> mp;

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
    cout<< mp["banana"] <<endl;  // 輸出: 123 (插入失敗，值未被覆蓋)

    // 使用 mp.emplace(Key, Value) 來新增
    // 與insert同樣不會覆蓋已有元素
    // 理論上效率較insert高（省去臨時pair的複製/搬移），value為複雜物件時效益較顯著
    mp.emplace("grape", 8);
    mp.emplace("grape", 99); // key 已存在，不會覆蓋

    cout << mp["grape"] << endl; // 輸出: 8
}

cout<<("======================\n");// 分隔線

{
    // 《4. 刪除》
    // 用法與map完全相同

    unordered_map<string, int> mp = {{"apple", 3}, {"banana", 5}, {"cherry", 7}, {"date", 9}};

    // 用 mp.erase(Key或iterator) 刪除指定元素

    // 依 key 刪除 (回傳刪除的數量)
    int Erase_num = mp.erase("apple");
    cout<< Erase_num <<endl;  // 輸出: 1 (表示成功刪除1個Key為"apple"的元素)
    // 剩下: banana=5, cherry=7, date=9

    // 依 iterator 刪除 (回傳刪除元素的後一個元素的迭代器)
    auto it = mp.find("banana");
    mp.erase(it);
    // 注意: 與map不同，unordered_map的「下一個元素」是依雜湊桶(bucket)順序決定，並非依Key排序
    //       若被刪除的元素剛好是目前雜湊順序的最後一個，回傳的迭代器就會是mp.end()
    //       因此這裡改用 size() 與 count() 驗證刪除結果，而不直接比較回傳的迭代器
    cout<< mp.size() <<endl;              // 輸出: 2 (剩下cherry與date兩個元素)
    cout<< mp.count("cherry") <<endl;     // 輸出: 1 (cherry仍存在)
    // 剩下: cherry=7, date=9 (兩者皆存在，僅剩餘順序不保證)

    // 範圍刪除（此例為全部刪除）
    /*
    參數：first 與 last 兩個迭代器，刪除區間 [first, last)
    回傳型態：iterator（指向最後被刪除元素之後的元素，即原先 last 指向的位置)
    */
    it = mp.erase(mp.begin(), mp.end());
    cout<< (it==mp.end()) <<endl;  // 輸出: 1 (表示it是mp.end())
    // 剩下: 空的

    // 用 mp.clear() 清空整個unordered_map
    mp = {{"apple", 3}, {"banana", 5}};
    mp.clear();                   // 清空整個 unordered_map
    cout << mp.size() << endl;    // 輸出: 0
}

cout<<("======================\n");// 分隔線

{
    // 《5. 遍歷》
    // Tip: unordered_map內的元素是pair，用法與map相同
    // 但「順序不保證」，以下輸出結果僅為此次GCC實際執行的結果，僅供參考

    unordered_map<string, int> mp = {{"banana", 5}, {"apple", 3}, {"cherry", 7}};

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
    三個方法的輸出皆相同(順序仍不保證，以下為此次實際執行的結果):
    cherry: 7
    apple: 3
    banana: 5

    重要提醒: 若需要「依Key排序」遍歷，unordered_map無法做到，須改用map
    */
}

cout<<("======================\n");// 分隔線

{
    // 《6. 常用函式》

    unordered_map<int, string> mp = {{1, "one"}, {3, "three"}, {2, "two"}};
    unordered_map<int, string> mp2;

    // 1. 判斷 unordered_map 是否為空
    bool IsEmpty = mp.empty();
    cout<< IsEmpty <<endl;  // 輸出: 0 (表示非空)

    IsEmpty = mp2.empty();
    cout<< IsEmpty <<endl;  // 輸出: 1 (表示此unordered_map是空的)


    // 2. 取得 unordered_map 的大小(元素個數)
    int N = mp.size();
    cout<< N <<endl;  // 輸出: 3  (mp內含三個元素)

    N = mp2.size();
    cout<< N <<endl;  // 輸出: 0


    // 3. 交換兩個unordered_map的內容
    unordered_map<int,string> a = {{1,"a"}}, b = {{2,"b"}, {3,"c"}};
    a.swap(b);
    cout<< a.size() <<endl;  // 輸出: 2 (交換後a變成原本b的內容)
    cout<< b.size() <<endl;  // 輸出: 1 (交換後b變成原本a的內容)


    cout<<("======================\n");// 分隔線


    // 4. 雜湊表(Hash Table)相關函式
    // 以下這些函式是unordered_map「特有」的，map沒有這些函式，用來觀察或調整底層雜湊表的狀態

    mp = {{1, "one"}, {3, "three"}, {2, "two"}};

    // mp.bucket_count()：取得目前「桶(bucket)」的總數量
    cout<< mp.bucket_count() <<endl;  // 輸出: 13 (此為GCC/libstdc++預設策略下，3個元素時實際分配的桶數，不同編譯器結果可能不同)

    // mp.bucket(Key)：回傳指定Key目前被分配到「第幾個桶」
    cout<< mp.bucket(1) <<endl;  // 輸出: 1 (依雜湊函式計算結果而定，不同編譯器/元素可能不同)

    // mp.bucket_size(n)：取得第n個桶內目前有幾個元素
    cout<< mp.bucket_size(mp.bucket(1)) <<endl;  // 輸出: 1 (代表key=1所在的桶內恰好只有1個元素，無雜湊碰撞)

    // mp.load_factor()：取得目前的負載係數 = 元素個數 / 桶數，數值越高代表雜湊表越擁擠
    cout<< mp.load_factor() <<endl;  // 輸出: 0.230769 (3個元素 / 13個桶 ≈ 0.230769)

    // mp.max_load_factor()：取得(或設定)最大負載係數，超過此係數會觸發自動rehash，預設通常為1.0
    cout<< mp.max_load_factor() <<endl;  // 輸出: 1

    // mp.rehash(n)：手動將桶數調整為至少能容納n個桶(通常會無條件進位到內部合適的桶數)
    mp.rehash(20);
    cout<< (mp.bucket_count() >= 20) <<endl;  // 輸出: 1 (代表rehash後桶數至少為20)

    // mp.reserve(n)：預留至少能容納n個元素「不會觸發rehash」所需的桶數，效果類似vector的reserve()
    // 若能預先知道大約會插入多少元素，建議在插入大量資料前先呼叫reserve()，可以減少rehash次數、提升效能
    unordered_map<int, int> mp3;
    mp3.reserve(1000);
    cout<< (mp3.bucket_count() >= 1000) <<endl;  // 輸出: 1
}
}

/*
補充: unordered_map 與 map 的差異

map          : 元素會依Key自動排序，底層為紅黑樹，插入/刪除/搜尋皆為 O(log n)
unordered_map: 元素「不會」排序(順序不固定)，底層為雜湊表(hash table)，
               插入/刪除/搜尋平均為 O(1)，最差情況(雜湊碰撞嚴重時)為 O(n)

如何選擇：
- 需要「依Key排序」的資料、或需要用 lower_bound/upper_bound 做範圍查詢 -> 使用 map
- 只需要「快速存取」、不在意順序 -> 優先使用 unordered_map，通常效能較佳

補充: unordered_map 與 unordered_set 的差異(對照set筆記)

unordered_map儲存的是pair<const Key, Value>鍵值對，用Key去找Value
unordered_set儲存的則是單一元素(元素本身同時是key也是value)
兩者底層皆為雜湊表，用法上的差異與 map/set 之間的差異相對應
*/


// 本篇筆記參考 cppreference std::unordered_map (https://en.cppreference.com/w/cpp/container/unordered_map)
// Created by B.J.Wang 2026/8/12