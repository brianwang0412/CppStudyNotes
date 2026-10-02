#include<map>  //需引入map標頭檔(multimap與map定義在同一個標頭檔中)

#include<iostream>
#include<string>
#include<algorithm>
#include<numeric>
using namespace std;

// 使用Traversal_mm來表示遍歷multimap mm的輸出結果(key-value皆印出)
#define Traversal_mm for (const auto& p:mm) cout<<'['<<p.first<<':'<<p.second<<"] "; cout<<endl;

/*
前言: multimap的特色、用途

multimap 與 map 非常相似，底層同樣是「紅黑樹(red-black tree)」實作，
因此同樣具備以下特性:
  - 內部元素「永遠依key自動排序」(預設由小到大，可自訂排序規則)
  - 插入/刪除/搜尋的時間複雜度皆為 O(log n)

但 multimap 與 map 最大的不同在於:
  - map的key「不可重複」，一個key只能對應一個value
  - multimap「允許key重複」，同一個key可以對應多個value(可以想成一個key對應一組值的集合)
  - 正因為同一個key可能對應多個value，multimap「沒有」operator[]與at()，
    因為如果呼叫 mm[key]，編譯器無法判斷到底該回傳「哪一個」符合該key的value，語意會有歧義
  - 要存取/操作某個key「所有」對應的value，必須搭配 equal_range()、lower_bound()/upper_bound() 等函式

適合的使用情境: 需要讓「一個key對應多筆資料」且希望資料自動依key排序的場合
(例如: 同一個分數對應多位學生姓名、同一個日期對應多筆交易紀錄...等)
*/


int main(){
{
    // 《1. multimap的宣告》

    // 建立空的multimap，key為string、value為int，名稱為mm1
    multimap<string, int> mm1;

    // 初始化包含元素的 multimap，會「自動依key排序」，key重複的元素皆會保留
    multimap<string, int> mm2 = {
        {"Amy", 90},
        {"Bob", 85},
        {"Amy", 95},   // key "Amy" 重複，兩筆都會保留(這點與map不同，map會覆蓋或插入失敗)
        {"Cathy", 70}
    };
    // mm2內容(依key由小到大排序，相同key依插入順序排列): {Amy:90, Amy:95, Bob:85, Cathy:70}

    // 複製建構，mm2與mm3會互相獨立
    multimap<string, int> mm3(mm2);

    // 也可以用兩個iterator(迭代器)範圍來初始化
    multimap<string, int> mm4(mm2.begin(), mm2.end());

    // 自訂排序規則: 預設是依key由小到大(less<Key>)排序，可改用greater<Key>改為由大到小
    multimap<string, int, greater<string>> mm5 = {
        {"Amy", 90}, {"Bob", 85}, {"Cathy", 70}
    };
    cout<<"mm5(由大到小): ";
    for (const auto& p : mm5) cout<<'['<<p.first<<':'<<p.second<<"] ";
    cout<<endl;
    // 輸出: mm5(由大到小): [Cathy:70] [Bob:85] [Amy:90]
}
cout<<("====================================\n");// 分隔線
{
    // 《2. multimap的新增、存取與刪除》
    // 注意: multimap「沒有」operator[]與at()，因為一個key可能對應多個value，無法用[]明確指定要存取哪一筆

    multimap<string, int> mm;  // 建立一個空的multimap

    // 1. 新增 (insert與emplace)

    // mm.insert({key, value}) 或 mm.insert(make_pair(key, value))，新增一組key-value
    mm.insert({"Amy", 90});
    mm.insert(make_pair("Bob", 85));
    mm.insert({"Amy", 95});  // key重複也會成功插入(這是與map最大的不同，map插入重複key會失敗)
    Traversal_mm // 輸出: [Amy:90] [Amy:95] [Bob:85]
    // 說明: multimap永遠依key自動排序，Amy < Bob，因此Amy的兩筆資料都排在Bob前面
    //       而兩筆Amy彼此之間，則依「插入順序」排列(90先插入，故排在95前面)

    // mm.emplace(key, value): 功能與insert類似，但「直接在容器內部建構元素」，可省去一次額外的複製或搬移
    mm.emplace("Cathy", 70);
    Traversal_mm // 輸出: [Amy:90] [Amy:95] [Bob:85] [Cathy:70]


    cout<<("======================\n");// 分隔線


    // 2. 存取
    // 由於沒有operator[]與at()，若要取得某個key「對應的值」，有以下幾種做法:

    // 2-1. 用find()取得「其中一筆」符合key的迭代器(若有多筆重複key，只會回傳其中一個，通常是第一個)
    auto it = mm.find("Amy");
    if (it != mm.end()){
        cout<< it->first <<": "<< it->second <<endl;
    }
    // 輸出: Amy: 90

    // 2-2. 若要取得某個key「所有」對應的value，須用equal_range()
    // equal_range(key) 回傳一個pair<iterator,iterator>，代表[lower_bound, upper_bound)的範圍
    // 範圍內的所有元素，key皆等於查詢的key
    auto range = mm.equal_range("Amy");
    cout<<"Amy的所有成績: ";
    for (auto rit = range.first; rit != range.second; rit++){
        cout<< rit->second << ' ';
    }
    cout<<endl;
    // 輸出: Amy的所有成績: 90 95

    // 2-3. 搭配結構化綁定(structured binding, C++17)讓程式碼更簡潔
    auto [lo, hi] = mm.equal_range("Amy");
    cout<<"Amy的所有成績(結構化綁定): ";
    for (auto rit = lo; rit != hi; rit++){
        cout<< rit->second << ' ';
    }
    cout<<endl;
    // 輸出: Amy的所有成績(結構化綁定): 90 95


    cout<<("======================\n");// 分隔線


    // 3. 刪除

    // 現在multimap mm中有4組資料: {Amy:90, Amy:95, Bob:85, Cathy:70}

    // 用 mm.erase(key) 刪除「所有」符合該key的元素，回傳實際刪除的元素個數
    int removedCount = mm.erase("Amy");  // 會把Amy:90與Amy:95「兩筆都」刪除
    cout<< removedCount <<endl;  // 輸出: 2
    Traversal_mm // 輸出: [Bob:85] [Cathy:70]

    // 若只想刪除「某個key的其中一筆」，須先用find()或equal_range()取得該筆的iterator，再用 mm.erase(it) 刪除單一元素
    mm.insert({"Bob", 100});
    mm.insert({"Bob", 60});
    Traversal_mm // 輸出: [Bob:85] [Bob:100] [Bob:60] [Cathy:70]
    // 說明: 根據C++標準規定，插入「key重複」的新元素時，會插入到該key範圍的upper_bound位置
    //      (也就是「所有既有的同key元素之後」)，因此同一個key的多筆元素，
    //      彼此之間「會」依照插入的先後順序排列: 85最先插入排最前面，
    //      接著100插入到85之後，接著60再插入到100之後，故結果為 85, 100, 60

    auto itBob = mm.find("Bob");  // 用find()只會找到其中一筆Bob(依標準規定為該key範圍中的第一筆，也就是85)
    mm.erase(itBob);  // 只刪除這一筆(85)
    Traversal_mm // 輸出: [Bob:100] [Bob:60] [Cathy:70]

    // 用 mm.erase(first, last) 刪除一個範圍內的所有元素
    mm = {{"A",1},{"B",2},{"C",3},{"D",4}};
    mm.erase(mm.begin(), next(mm.begin(), 2));  // 刪除前兩筆(A,B)
    Traversal_mm // 輸出: [C:3] [D:4]

    // 用 mm.clear() 清空整個multimap
    mm.clear();
    Traversal_mm // 輸出:     (沒有元素，清空了)
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 遍歷》
    // multimap的元素一律是 pair<const Key, Value>，且「永遠依key排序」

    multimap<string, int> mm = {
        {"Bob", 85}, {"Amy", 90}, {"Amy", 95}, {"Cathy", 70}
    };

    // 1. 使用「以範圍為基礎的 for 語句」（Range-based for Statement）搭配 .first/.second
    for (const auto& p : mm){
        cout<< p.first <<":"<< p.second <<' ';
    }
    cout<<endl;
    // 輸出: Amy:90 Amy:95 Bob:85 Cathy:70


    // 2. 搭配「結構化綁定(structured binding, C++17)」，讓key、value可以直接拆開成獨立變數
    for (const auto& [key, value] : mm){
        cout<< key <<"="<< value <<' ';
    }
    cout<<endl;
    // 輸出: Amy=90 Amy=95 Bob=85 Cathy=70


    // 3. 使用迭代器(iterator)遍歷
    // multimap/map的迭代器屬於「雙向迭代器(Bidirectional Iterator)」，不支援it+n這種隨機存取運算
    for (multimap<string,int>::iterator it = mm.begin(); it != mm.end(); it++){
        cout<<"("<< it->first <<","<< it->second <<") ";
    }
    cout<<endl;
    // 輸出: (Amy,90) (Amy,95) (Bob,85) (Cathy,70)


    // 4. 反向迭代器(reverse_iterator)：由尾到頭遍歷(即key由大到小)
    for (auto rit = mm.rbegin(); rit != mm.rend(); rit++){
        cout<< rit->first <<":"<< rit->second <<' ';
    }
    cout<<endl;
    // 輸出: Cathy:70 Bob:85 Amy:95 Amy:90
    // 注意: 同key的Amy:90與Amy:95，反向遍歷時順序也會跟著整個反過來(變成95在90前面)


    // 5. 修改value: multimap的key是const，不能修改，但value可以透過迭代器修改
    for (auto& p : mm){  // 這裡不能加const，才能修改p.second
        p.second += 1;
    }
    Traversal_mm // 輸出: [Amy:91] [Amy:96] [Bob:86] [Cathy:71]
}
cout<<("====================================\n");// 分隔線
{
    //《4. 常用功能》

    multimap<int, string> mm = {
        {80, "Amy"}, {60, "Bob"}, {80, "Cathy"}, {90, "David"}
    };
    // 這裡改成key=int(分數)、value=string(姓名)，示範「同一個分數對應多位學生」的情境
    // multimap內容(依key排序): {60:Bob, 80:Amy, 80:Cathy, 90:David}

    // 取得元素個數(所有key-value的總筆數，重複key會分開計算)
    int n = mm.size();
    cout<< n <<endl;  // 輸出: 4

    // 判斷是否為空
    cout<< mm.empty() <<endl;  // 輸出: 0 (表示非空)


    cout<<("======================\n");// 分隔線


    // count(key): 計算某個key「出現的次數」(multimap可能>1，這點與map不同，map的count()結果只會是0或1)
    cout<< mm.count(80) <<endl;  // 輸出: 2 (80分有Amy和Cathy兩筆)
    cout<< mm.count(60) <<endl;  // 輸出: 1
    cout<< mm.count(100) <<endl; // 輸出: 0 (不存在的key)


    cout<<("======================\n");// 分隔線


    // find(key): 尋找某個key「其中一筆」的位置，回傳iterator；找不到則回傳end()
    auto it = mm.find(80);
    if (it != mm.end()){
        cout<<"找到 80 分，其中一位是: "<< it->second <<endl;
    }
    // 輸出: 找到 80 分，其中一位是: Amy


    cout<<("======================\n");// 分隔線


    // lower_bound(key) / upper_bound(key)
    // lower_bound(key): 回傳「第一個」key不小於(>=)查詢值的位置
    // upper_bound(key): 回傳「第一個」key大於(>)查詢值的位置
    // 兩者合併使用，恰好可以框出所有key等於查詢值的範圍(equal_range()其實就是封裝這兩者)
    auto lo = mm.lower_bound(80);
    auto hi = mm.upper_bound(80);
    cout<<"80分的所有學生: ";
    for (auto it2 = lo; it2 != hi; it2++){
        cout<< it2->second << ' ';
    }
    cout<<endl;
    // 輸出: 80分的所有學生: Amy Cathy

    // 搭配lower_bound實作「範圍查詢」: 找出所有分數 >= 80 的學生
    cout<<"80分以上(含)的所有學生: ";
    for (auto it3 = mm.lower_bound(80); it3 != mm.end(); it3++){
        cout<< it3->second <<"("<< it3->first <<") ";
    }
    cout<<endl;
    // 輸出: 80分以上(含)的所有學生: Amy(80) Cathy(80) David(90)


    cout<<("======================\n");// 分隔線


    // equal_range(key): 一次取得某個key的[lower_bound, upper_bound)範圍(等同上面兩者合併)
    auto range = mm.equal_range(80);
    cout<<"80分的所有學生(equal_range): ";
    for (auto it4 = range.first; it4 != range.second; it4++){
        cout<< it4->second << ' ';
    }
    cout<<endl;
    // 輸出: 80分的所有學生(equal_range): Amy Cathy


    cout<<("======================\n");// 分隔線


    // 交換兩個multimap的內容
    multimap<int,string> mmA = {{1,"a"}}, mmB = {{2,"b"},{3,"c"}};
    mmA.swap(mmB);
    cout<<"mmA: "; for (const auto& p:mmA) cout<<'['<<p.first<<':'<<p.second<<"] "; cout<<endl;
    cout<<"mmB: "; for (const auto& p:mmB) cout<<'['<<p.first<<':'<<p.second<<"] "; cout<<endl;
    // 輸出: mmA: [2:b] [3:c]
    // 輸出: mmB: [1:a]


    cout<<("======================\n");// 分隔線


    // insert搭配hint(提示)迭代器: insert(hint, {key,value})
    // 若能正確提供「插入位置附近」的提示迭代器，可以加快插入效率(從O(log n)降為平攤O(1))
    // 即使hint提供錯誤，insert仍會正確插入到該排序的正確位置，只是會失去效能優化的效果
    multimap<int,string> mm2 = {{1,"a"},{3,"c"}};
    mm2.insert(mm2.end(), {5,"e"});  // 提示: 5應該插入在end()附近(因為5是目前最大值)
    cout<<"mm2: "; for (const auto& p:mm2) cout<<'['<<p.first<<':'<<p.second<<"] "; cout<<endl;
    // 輸出: mm2: [1:a] [3:c] [5:e]


    cout<<("======================\n");// 分隔線


    // key_comp(): 回傳目前使用的「key比較函式物件」，可用來呼叫並比較兩個key的大小關係
    multimap<int,string> mm3;
    auto cmp = mm3.key_comp();
    cout<< cmp(1, 2) <<endl;  // 輸出: 1 (預設為less<int>，1<2成立，回傳true)
    cout<< cmp(2, 1) <<endl;  // 輸出: 0 (2<1不成立，回傳false)


    cout<<("======================\n");// 分隔線


    // contains(key): C++20新增，判斷是否存在某個key(回傳bool)，語意比count()>0更直覺
    // 若編譯環境支援C++20，可以用以下方式判斷(若環境只到C++17，則須改用 mm.count(key) > 0 或 mm.find(key)!=mm.end())
    multimap<int,string> mm4 = {{1,"a"},{2,"b"}};
    cout<< (mm4.count(1) > 0) <<endl;  // 輸出: 1 (C++17相容寫法，存在key=1)
    cout<< (mm4.count(9) > 0) <<endl;  // 輸出: 0 (不存在key=9)
    // 若為C++20環境，也可以直接寫成: cout<< mm4.contains(1) <<endl;  // 輸出: 1


    cout<<("======================\n");// 分隔線


    // 搭配<algorithm>/<numeric>使用: 由於multimap的iterator只是雙向迭代器，
    // 大部分需要隨機存取的演算法(如sort)無法使用，但count_if、accumulate等只需要
    // 雙向(甚至只需要輸入)迭代器的演算法仍然可以正常運作

    multimap<int,string> mm5 = {{80,"Amy"},{60,"Bob"},{80,"Cathy"},{90,"David"}};

    // 計算有幾位學生「分數>=80」
    int cnt = count_if(mm5.begin(), mm5.end(), [](const pair<const int,string>& p){
        return p.first >= 80;
    });
    cout<< cnt <<endl;  // 輸出: 3

    // 計算所有分數的總和
    int sum = accumulate(mm5.begin(), mm5.end(), 0, [](int acc, const pair<const int,string>& p){
        return acc + p.first;
    });
    cout<< sum <<endl;  // 輸出: 310 (80+60+80+90=310)
}
}


// 本篇筆記參考cppreference std::multimap (https://en.cppreference.com/w/cpp/container/multimap)
// Generated by Claude 2026/10/2
