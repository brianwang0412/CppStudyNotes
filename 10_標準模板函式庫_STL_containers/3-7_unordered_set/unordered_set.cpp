#include<unordered_set>  //需引入unordered_set標頭檔

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

/*
前言: unordered_set的特色、用途

unordered_set 是一種「元素不可重複」的容器，與set功能類似(皆儲存不重複的值)，
但底層實作完全不同:
  - set底層是紅黑樹，元素「永遠自動排序」，操作時間複雜度為 O(log n)
  - unordered_set底層是「雜湊表(hash table)」，元素「不保證任何順序」
    (遍歷順序取決於雜湊函式與桶(bucket)的內部排列方式，與插入順序、數值大小都無關)
    平均時間複雜度為 O(1)，但最壞情況(大量雜湊碰撞)會退化為 O(n)

因此unordered_set的優缺點恰好與set互補:
  - 優點: 平均插入/刪除/搜尋速度比set快(O(1) vs O(log n))
  - 缺點: 不能排序、不支援lower_bound()/upper_bound()這類「有序」才能使用的操作、
         不支援反向迭代器(reverse_iterator)，迭代器也只是「前向迭代器(Forward Iterator)」，
         甚至連it++都只能往單一方向走，不能it--

適合的使用情境: 只在意「某個值是否存在」、不在乎順序、且追求效能的場合
(例如: 快速判斷資料是否重複、快速查找某個值是否出現過...等)

【非常重要的提醒】
本篇筆記中所有「遍歷順序」的輸出結果，皆是在特定編譯環境下
(g++ 13.3.0, libstdc++, x86-64 Linux)實際測試所得到的結果。
C++標準「並未規定」unordered_set的遍歷順序，只保證：
  1. 元素不會重複
  2. 只要容器內容、雜湊函式、bucket數量不變，同一支程式「重複執行」的結果會一致
但換一台電腦、換一個編譯器、甚至只是換一個標準函式庫版本，順序都可能不同，
所以「不可以」在程式邏輯中依賴unordered_set的遍歷順序，若需要有序的結果，請改用set。
*/


int main(){
{
    // 《1. unordered_set的宣告》

    // 建立空的unordered_set，可以用於儲存整數(int)，名稱為us1
    unordered_set<int> us1;

    // 初始化包含元素的 unordered_set，重複的值只會保留一個(這點與set相同)
    unordered_set<int> us2 = {5, 3, 8, 3, 1, 8};
    cout<<"us2: ";
    for (const int& x : us2) cout<<x<<' ';
    cout<<endl;
    // 輸出: us2: 1 8 3 5
    // 說明: 重複的3和8都只保留一個；但順序「不是」1,3,5,8這種排序結果，
    //      而是依照雜湊表內部的桶(bucket)排列方式決定，不可預期

    // 複製建構，us2與us3會互相獨立
    unordered_set<int> us3(us2);

    // 也可以用兩個iterator(迭代器)範圍來初始化
    unordered_set<int> us4(us2.begin(), us2.end());

    // 建構時可以額外指定「初始的bucket數量」，用於效能調校(若預期元素很多，
    // 可以一開始就給足夠的bucket，減少後續rehash重新雜湊的次數)
    unordered_set<int> us5(20);  // 初始至少準備20個bucket
    cout<<"us5一開始的bucket數量: "<< us5.bucket_count() <<endl;
    // 輸出: us5一開始的bucket數量: 23
    // 說明: 實作上通常會取「不小於指定值的質數」作為實際bucket數量(libstdc++的常見作法)，
    //      這是實作細節，不同編譯器/版本結果可能不同


    cout<<("======================\n");// 分隔線


    // 自訂雜湊函式與相等比較函式(進階用法): 若要將「自訂型別(struct/class)」放入
    // unordered_set，由於編譯器不知道如何計算該型別的雜湊值，須自行提供雜湊函式

    struct Point{
        int x, y;
        bool operator==(const Point& other) const {  // 須自行定義相等比較(==)
            return x == other.x && y == other.y;
        }
    };
    struct PointHash{  // 自訂雜湊函式物件(functor)
        size_t operator()(const Point& p) const {
            // 一種常見的組合雜湊寫法: 利用hash<int>分別計算x、y的雜湊值後互斥或(XOR)組合
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
    unordered_set<Point, PointHash> pointSet;  // 第二個樣板參數指定雜湊函式物件的型別
    pointSet.insert({1, 2});
    pointSet.insert({3, 4});
    pointSet.insert({1, 2});  // 重複的點，不會再新增
    cout<<"pointSet的元素個數: "<< pointSet.size() <<endl;
    // 輸出: pointSet的元素個數: 2
}
cout<<("====================================\n");// 分隔線
{
    // 《2. unordered_set的新增、存取與刪除》
    // 注意: unordered_set「沒有」operator[]與at()，理由與set相同——元素本身就是key，
    //      並非一組key-value，因此也沒有「索引」或「鍵值」可以用來直接存取

    unordered_set<int> us;  // 建立一個空的unordered_set

    // 1. 新增 (insert與emplace)

    // us.insert(x) 新增元素x；若x已存在，則插入失敗(不會新增，容器內容不變)
    us.insert(10);
    us.insert(20);
    us.insert(10);  // 10已存在，這次插入會失敗
    cout<<"us的元素個數: "<< us.size() <<endl;  // 輸出: us的元素個數: 2

    // insert()會回傳一個pair<iterator, bool>，bool表示「是否插入成功」
    auto result = us.insert(30);
    cout<<"插入30是否成功: "<< result.second <<endl;  // 輸出: 插入30是否成功: 1

    auto result2 = us.insert(30);  // 再插入一次重複的30
    cout<<"再次插入30是否成功: "<< result2.second <<endl;  // 輸出: 再次插入30是否成功: 0

    // us.emplace(x): 功能與insert類似，但「直接在容器內部建構元素」，可省去一次額外的複製或搬移
    us.emplace(40);
    cout<<"us的元素個數: "<< us.size() <<endl;  // 輸出: us的元素個數: 4


    cout<<("======================\n");// 分隔線


    // 2. 存取
    // unordered_set沒有operator[]/at()，元素也不能被修改(const)，只能透過以下方式「查詢」是否存在

    // 2-1. 用find()判斷元素是否存在，存在則回傳指向該元素的迭代器，否則回傳end()
    auto it = us.find(20);
    if (it != us.end()){
        cout<<"找到: "<< *it <<endl;
    }
    else{
        cout<<"Not found"<<endl;
    }
    // 輸出: 找到: 20

    auto itNotFound = us.find(999);
    if (itNotFound == us.end()){
        cout<<"999 不存在"<<endl;
    }
    // 輸出: 999 不存在

    // 2-2. 用count(x)判斷元素是否存在：因為unordered_set元素不可重複，count()結果只會是0或1
    cout<< us.count(20) <<endl;   // 輸出: 1 (存在)
    cout<< us.count(999) <<endl;  // 輸出: 0 (不存在)

    // 2-3. contains(x): C++20新增，語意比count()>0更直覺，直接回傳bool
    // 若編譯環境只到C++17，須改用 us.count(x) > 0 或 us.find(x)!=us.end()
    cout<< (us.count(20) > 0) <<endl;  // 輸出: 1 (C++17相容寫法)
    // 若為C++20環境，也可以直接寫成: cout<< us.contains(20) <<endl;  // 輸出: 1

    // 注意: unordered_set的元素是const，不能透過迭代器修改！以下寫法「不合法」:
    // *it = 999;  // 編譯錯誤: 無法對const int賦值
    // 若要「修改」某個元素，須先erase()刪除舊值，再insert()新值(與multiset相同的作法)


    cout<<("======================\n");// 分隔線


    // 3. 刪除

    // 現在unordered_set us中有4個元素: {10, 20, 30, 40}(實際印出順序不保證)

    // 用 us.erase(value) 刪除指定「值」的元素，回傳實際刪除的元素個數(0或1)
    int removedCount = us.erase(20);
    cout<< removedCount <<endl;  // 輸出: 1
    cout<<"us的元素個數: "<< us.size() <<endl;  // 輸出: us的元素個數: 3

    int removedCount2 = us.erase(999);  // 刪除不存在的元素
    cout<< removedCount2 <<endl;  // 輸出: 0 (因為999本來就不存在，沒有任何元素被刪除)

    // 用 us.erase(iterator) 刪除指定位置(單一元素)的元素
    auto it10 = us.find(10);
    if (it10 != us.end()){
        us.erase(it10);
    }
    cout<<"us的元素個數: "<< us.size() <<endl;  // 輸出: us的元素個數: 2

    // 用 us.erase(first, last) 刪除一個迭代器範圍內的所有元素
    us = {1,2,3,4,5};
    auto itBegin = us.begin();
    auto itThird = next(us.begin(), 3);  // 範圍迭代器仍可用next()移動(屬於前向迭代器，支援++)
    us.erase(itBegin, itThird);  // 刪除「前3個被遍歷到」的元素(實際是哪3個值，依雜湊順序而定)
    cout<<"刪除範圍後剩餘元素個數: "<< us.size() <<endl;
    // 輸出: 刪除範圍後剩餘元素個數: 2

    // 用 us.clear() 清空整個unordered_set
    us.clear();
    cout<<"清空後元素個數: "<< us.size() <<endl;  // 輸出: 清空後元素個數: 0
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 遍歷》
    // unordered_set的元素「不保證任何順序」，且元素本身為const，不可透過迭代器修改

    unordered_set<int> us = {5, 3, 8, 1, 9};

    // 1. 使用「以範圍為基礎的 for 語句」（Range-based for Statement）
    for (int x : us){
        cout<< x << ' ';
    }
    cout<<endl;
    // 輸出: 9 1 8 3 5
    // (再次提醒: 此順序只是本機測試結果，不可依賴，標準並未規定任何順序)

    // 2. 使用迭代器(iterator)遍歷
    // unordered_set的迭代器屬於「前向迭代器(Forward Iterator)」，只支援 it++，
    // 不支援 it--、it+n 等運算(比list的雙向迭代器限制更多)
    for (unordered_set<int>::iterator it = us.begin(); it != us.end(); it++){
        cout<< *it << ' ';
    }
    cout<<endl;
    // 輸出: 9 1 8 3 5

    // 3. 【沒有】反向迭代器(reverse_iterator)
    // 與vector/deque/list/set/multiset不同，unordered_set「沒有」rbegin()/rend()，
    // 因為它的元素根本沒有「正向」或「反向」的概念(只有雜湊桶排列順序)，
    // 以下寫法會編譯錯誤: for (auto rit = us.rbegin(); rit != us.rend(); rit++){...}

    // 4. 若需要「排序後」的遍歷結果，常見作法是先複製到vector再排序
    vector<int> sortedVec(us.begin(), us.end());
    sort(sortedVec.begin(), sortedVec.end());
    cout<<"排序後: ";
    for (int x : sortedVec) cout<<x<<' ';
    cout<<endl;
    // 輸出: 排序後: 1 3 5 8 9
}
cout<<("====================================\n");// 分隔線
{
    //《4. 常用功能》

    unordered_set<int> us = {10, 20, 30, 40, 50};

    // 取得元素個數
    int n = us.size();
    cout<< n <<endl;  // 輸出: 5

    // 判斷是否為空
    cout<< us.empty() <<endl;  // 輸出: 0 (表示非空)


    cout<<("======================\n");// 分隔線


    // equal_range(x): 回傳[first,last)範圍，因為unordered_set元素不可重複，
    // 範圍內最多只會有一個元素(找到的話)
    auto range = us.equal_range(20);
    cout<<"equal_range(20)找到的元素: ";
    for (auto it = range.first; it != range.second; it++){
        cout<< *it << ' ';
    }
    cout<<endl;
    // 輸出: equal_range(20)找到的元素: 20


    cout<<("======================\n");// 分隔線


    // 交換兩個unordered_set的內容
    unordered_set<int> usA = {1, 2}, usB = {7, 8, 9};
    usA.swap(usB);
    cout<<"usA的元素個數: "<< usA.size() <<endl;  // 輸出: usA的元素個數: 3
    cout<<"usB的元素個數: "<< usB.size() <<endl;  // 輸出: usB的元素個數: 2


    cout<<("======================\n");// 分隔線


    // 《Bucket(雜湊桶)相關介面》
    // 這些函式用於觀察/調校unordered_set底層雜湊表的內部狀態，一般應用開發較少直接用到，
    // 但考試/面試常考，了解原理有助於分析效能問題

    unordered_set<int> us2 = {1, 2, 3, 4, 5};

    // bucket_count(): 目前總共有幾個bucket(桶)
    cout<<"bucket數量: "<< us2.bucket_count() <<endl;
    // 輸出: bucket數量: 13
    // (libstdc++的實作細節，不同版本/編譯器可能不同)

    // load_factor(): 目前的負載係數 = 元素個數 / bucket數量，數值越高代表雜湊碰撞機率越高
    cout<<"load_factor: "<< us2.load_factor() <<endl;
    // 輸出: load_factor: 0.384615
    // 計算: 5個元素 / 13個bucket ≈ 0.3846

    // max_load_factor(): 取得(或設定)「負載係數上限」，預設通常為1.0
    // 當load_factor超過max_load_factor時，容器會自動rehash(重新配置更多bucket)
    cout<<"max_load_factor: "<< us2.max_load_factor() <<endl;
    // 輸出: max_load_factor: 1

    // bucket(x): 回傳元素x「目前位於第幾個bucket」(索引值)
    cout<<"元素3位於第幾個bucket: "<< us2.bucket(3) <<endl;
    // 輸出: 元素3位於第幾個bucket: 3
    // (由於3對13取餘數=3，剛好對應bucket索引3，這是libstdc++常見的雜湊取餘數策略)

    // bucket_size(n): 回傳「第n個bucket」裡面目前有幾個元素(同一個bucket可能因雜湊碰撞而有多個元素)
    cout<<"bucket 3裡面有幾個元素: "<< us2.bucket_size(3) <<endl;
    // 輸出: bucket 3裡面有幾個元素: 1

    // reserve(n): 預先配置足夠的bucket，讓容器最多可以容納n個元素「而不需要rehash」，用於效能優化
    unordered_set<int> us3;
    us3.reserve(100);  // 預期之後會塞進約100個元素，先一次配置好
    cout<<"reserve(100)後的bucket數量: "<< us3.bucket_count() <<endl;
    // 輸出: reserve(100)後的bucket數量: 103

    // rehash(n): 強制將bucket數量「至少」調整為n(若n比目前的bucket數量小，則可能不會縮小)
    unordered_set<int> us4 = {1,2,3};
    us4.rehash(50);
    cout<<"rehash(50)後的bucket數量: "<< us4.bucket_count() <<endl;
    // 輸出: rehash(50)後的bucket數量: 53


    cout<<("======================\n");// 分隔線


    // hash_function(): 回傳目前使用的雜湊函式物件，可呼叫它來查看某個值的雜湊結果
    unordered_set<int> us5;
    auto hashFn = us5.hash_function();
    cout<<"hash(12345): "<< hashFn(12345) <<endl;
    // 輸出: hash(12345): 12345
    // 說明: int型別的預設雜湊函式(std::hash<int>)，對int而言通常就是「原值本身」
    //      (即雜湊值與輸入值相同，這是libstdc++對整數型別的常見實作方式)


    cout<<("======================\n");// 分隔線


    // 搭配<algorithm>/<numeric>使用: unordered_set的iterator只是前向迭代器，
    // 連std::reverse()都不能用(因為reverse至少需要雙向迭代器)，但count_if、
    // accumulate等只需要輸入迭代器(InputIterator)的演算法仍然可以正常運作

    unordered_set<int> us6 = {10, 20, 30, 40, 50};

    // 計算有幾個元素 > 25
    int cnt = count_if(us6.begin(), us6.end(), [](int x){ return x > 25; });
    cout<< cnt <<endl;  // 輸出: 3

    // 計算所有元素的總和(accumulate不在乎順序，加總結果不受遍歷順序影響)
    int sum = accumulate(us6.begin(), us6.end(), 0);
    cout<< sum <<endl;  // 輸出: 150
}
}


// 本篇筆記參考cppreference std::unordered_set (https://en.cppreference.com/w/cpp/container/unordered_set)
// Generated by Claude 2026/10/2
