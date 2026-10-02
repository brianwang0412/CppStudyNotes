#include<set>  //需引入set標頭檔(multiset與set定義在同一個標頭檔中)

#include<iostream>
#include<string>
#include<algorithm>
#include<numeric>
using namespace std;

// 使用Traversal_ms來表示遍歷multiset ms的輸出結果
#define Traversal_ms for (const int& i:ms) cout<<i<<' '; cout<<endl;

/*
前言: multiset的特色、用途

multiset 與 set 非常相似，底層同樣是「紅黑樹(red-black tree)」實作，
因此同樣具備以下特性:
  - 內部元素「永遠自動排序」(預設由小到大，可自訂排序規則)
  - 插入/刪除/搜尋的時間複雜度皆為 O(log n)
  - 元素本身就是key(不像map/multimap是key-value配對)

但 multiset 與 set 最大的不同在於:
  - set的元素「不可重複」，插入重複值會失敗(不會新增)
  - multiset「允許元素重複」，同一個值可以存在多筆
  - 正因為元素本身就是排序的依據(key)，multiset中的元素「不能被修改」
    (迭代器為const_iterator，不可透過迭代器直接修改元素值，若要「修改」某元素，
    必須先erase()刪除舊值，再insert()新值)

適合的使用情境: 需要「保存重複數值」且「隨時保持排序狀態」的場合
(例如: 統計重複出現的分數、保存一堆區間的端點、搭配multiset模擬可重複排序的資料流...等)
*/


int main(){
{
    // 《1. multiset的宣告》

    // 建立空的multiset，可以用於儲存整數(int)，名稱為ms1
    multiset<int> ms1;

    // 初始化包含元素的 multiset，會「自動排序」，重複的值皆會保留
    multiset<int> ms2 = {5, 3, 8, 3, 1, 8, 8};
    cout<<"ms2: ";
    for (const int& x : ms2) cout<<x<<' ';
    cout<<endl;
    // 輸出: ms2: 1 3 3 5 8 8 8
    // 說明: 這點與set不同，set遇到重複值只會保留一個，multiset則全部保留

    // 複製建構，ms2與ms3會互相獨立
    multiset<int> ms3(ms2);

    // 也可以用兩個iterator(迭代器)範圍來初始化
    multiset<int> ms4(ms2.begin(), ms2.end());

    // 自訂排序規則: 預設是由小到大(less<T>)排序，可改用greater<T>改為由大到小
    multiset<int, greater<int>> ms5 = {5, 3, 8, 3, 1};
    cout<<"ms5(由大到小): ";
    for (const int& x : ms5) cout<<x<<' ';
    cout<<endl;
    // 輸出: ms5(由大到小): 8 5 3 3 1
}
cout<<("====================================\n");// 分隔線
{
    // 《2. multiset的新增、存取與刪除》
    // 注意: multiset「沒有」operator[]與at()，因為元素本身就是key，並非一組key-value，
    //      存取方式只能透過iterator(find()/equal_range()等)間接取得，無法用index或key直接存取

    multiset<int> ms;  // 建立一個空的multiset

    // 1. 新增 (insert與emplace)

    // ms.insert(x) 新增元素x，一律會成功插入(即使x已存在)，並自動排序
    ms.insert(5);
    ms.insert(3);
    ms.insert(5);  // 重複值也會成功插入(這是與set最大的不同，set插入重複值會失敗)
    Traversal_ms // 輸出: 3 5 5

    // ms.emplace(x): 功能與insert類似，但「直接在容器內部建構元素」，可省去一次額外的複製或搬移
    ms.emplace(8);
    Traversal_ms // 輸出: 3 5 5 8


    cout<<("======================\n");// 分隔線


    // 2. 存取
    // multiset沒有operator[]/at()，元素也不能被修改(const)，只能透過以下方式「查詢」是否存在、或取得位置

    // 2-1. 用find()取得「其中一筆」等於查詢值的迭代器(若有多筆重複值，只會回傳其中一個)
    auto it = ms.find(5);
    if (it != ms.end()){
        cout<<"找到: "<< *it <<endl;
    }
    // 輸出: 找到: 5

    // 2-2. 若要取得「所有」等於查詢值的元素範圍，須用equal_range()
    // equal_range(x) 回傳一個pair<iterator,iterator>，代表[lower_bound, upper_bound)的範圍
    auto range = ms.equal_range(5);
    cout<<"所有值為5的元素: ";
    for (auto rit = range.first; rit != range.second; rit++){
        cout<< *rit << ' ';
    }
    cout<<endl;
    // 輸出: 所有值為5的元素: 5 5

    // 2-3. 搭配結構化綁定(structured binding, C++17)讓程式碼更簡潔
    auto [lo, hi] = ms.equal_range(5);
    cout<<"所有值為5的元素(結構化綁定): ";
    for (auto rit = lo; rit != hi; rit++){
        cout<< *rit << ' ';
    }
    cout<<endl;
    // 輸出: 所有值為5的元素(結構化綁定): 5 5

    // 注意: multiset的元素是const，不能透過迭代器修改！以下寫法「不合法」:
    // *it = 10;  // 編譯錯誤: 無法對const int賦值
    // 若要「修改」某個元素，須先erase()刪除舊值，再insert()新值


    cout<<("======================\n");// 分隔線


    // 3. 刪除

    // 現在multiset ms中有4個元素: {3, 5, 5, 8}

    // 用 ms.erase(value) 刪除「所有」等於該值的元素，回傳實際刪除的元素個數
    int removedCount = ms.erase(5);  // 會把兩個5「都」刪除
    cout<< removedCount <<endl;  // 輸出: 2
    Traversal_ms // 輸出: 3 8

    // 若只想刪除「其中一筆」，須先用find()取得該筆的iterator，再用 ms.erase(it) 刪除單一元素
    ms.insert(5);
    ms.insert(5);
    ms.insert(5);
    Traversal_ms // 輸出: 3 5 5 5 8

    auto it5 = ms.find(5);  // 只會找到其中一筆5
    ms.erase(it5);  // 只刪除這一筆
    Traversal_ms // 輸出: 3 5 5 8

    // 用 ms.erase(first, last) 刪除一個範圍內的所有元素
    ms = {1, 2, 3, 4, 5};
    ms.erase(ms.begin(), next(ms.begin(), 2));  // 刪除前兩個元素(1,2)
    Traversal_ms // 輸出: 3 4 5

    // 用 ms.clear() 清空整個multiset
    ms.clear();
    Traversal_ms // 輸出:     (沒有元素，清空了)
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 遍歷》
    // multiset的元素「永遠自動排序」，且元素本身為const，不可透過迭代器修改

    multiset<int> ms = {5, 3, 8, 3, 1, 8};

    // 1. 使用「以範圍為基礎的 for 語句」（Range-based for Statement）
    for (int x : ms){
        cout<< x << ' ';
    }
    cout<<endl;
    // 輸出: 1 3 3 5 8 8

    // 2. 使用迭代器(iterator)遍歷
    // multiset的迭代器屬於「雙向迭代器(Bidirectional Iterator)」，不支援it+n這種隨機存取運算
    for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++){
        cout<< *it << ' ';
    }
    cout<<endl;
    // 輸出: 1 3 3 5 8 8

    // 3. 反向迭代器(reverse_iterator)：由尾到頭遍歷(即由大到小)
    for (auto rit = ms.rbegin(); rit != ms.rend(); rit++){
        cout<< *rit << ' ';
    }
    cout<<endl;
    // 輸出: 8 8 5 3 3 1

    // 注意: multiset「不可」寫成 for(int& x:ms){x+=1;} 這種帶參考(reference)的寫法來修改元素，
    // 因為multiset的iterator本質上是const_iterator(元素即為排序依據，不允許修改)，以下寫法會編譯錯誤:
    // for (int& x : ms){ x += 1; }  // 編譯錯誤: 無法將 const int 繫結到 int&
}
cout<<("====================================\n");// 分隔線
{
    //《4. 常用功能》

    multiset<int> ms = {80, 60, 80, 90, 80, 70};
    // multiset內容(自動排序後): {60, 70, 80, 80, 80, 90}

    // 取得元素個數(所有元素的總筆數，重複值會分開計算)
    int n = ms.size();
    cout<< n <<endl;  // 輸出: 6

    // 判斷是否為空
    cout<< ms.empty() <<endl;  // 輸出: 0 (表示非空)


    cout<<("======================\n");// 分隔線


    // count(x): 計算某個值「出現的次數」(multiset可能>1，這點與set不同，set的count()結果只會是0或1)
    cout<< ms.count(80) <<endl;  // 輸出: 3 (80出現了3次)
    cout<< ms.count(60) <<endl;  // 輸出: 1
    cout<< ms.count(100) <<endl; // 輸出: 0 (不存在的值)


    cout<<("======================\n");// 分隔線


    // find(x): 尋找某個值「其中一筆」的位置，回傳iterator；找不到則回傳end()
    auto it = ms.find(80);
    if (it != ms.end()){
        cout<<"找到 80，位置的下一個元素是: "<< *next(it) <<endl;
    }
    // 輸出: 找到 80，位置的下一個元素是: 80


    cout<<("======================\n");// 分隔線


    // lower_bound(x) / upper_bound(x)
    // lower_bound(x): 回傳「第一個」值不小於(>=)x的位置
    // upper_bound(x): 回傳「第一個」值大於(>)x的位置
    // 兩者合併使用，恰好可以框出所有值等於x的範圍(equal_range()其實就是封裝這兩者)
    auto lo = ms.lower_bound(80);
    auto hi = ms.upper_bound(80);
    cout<<"所有等於80的元素: ";
    for (auto it2 = lo; it2 != hi; it2++){
        cout<< *it2 << ' ';
    }
    cout<<endl;
    // 輸出: 所有等於80的元素: 80 80 80

    // 搭配lower_bound實作「範圍查詢」: 找出所有「>= 80」的元素
    cout<<"80以上(含)的所有元素: ";
    for (auto it3 = ms.lower_bound(80); it3 != ms.end(); it3++){
        cout<< *it3 << ' ';
    }
    cout<<endl;
    // 輸出: 80以上(含)的所有元素: 80 80 80 90


    cout<<("======================\n");// 分隔線


    // equal_range(x): 一次取得某個值的[lower_bound, upper_bound)範圍(等同上面兩者合併)
    auto range = ms.equal_range(80);
    cout<<"所有等於80的元素(equal_range): ";
    for (auto it4 = range.first; it4 != range.second; it4++){
        cout<< *it4 << ' ';
    }
    cout<<endl;
    // 輸出: 所有等於80的元素(equal_range): 80 80 80


    cout<<("======================\n");// 分隔線


    // 交換兩個multiset的內容
    multiset<int> msA = {1, 1, 2}, msB = {7, 8, 9};
    msA.swap(msB);
    cout<<"msA: "; for (const int& x:msA) cout<<x<<' '; cout<<endl;
    cout<<"msB: "; for (const int& x:msB) cout<<x<<' '; cout<<endl;
    // 輸出: msA: 7 8 9
    // 輸出: msB: 1 1 2


    cout<<("======================\n");// 分隔線


    // insert搭配hint(提示)迭代器: insert(hint, x)
    // 若能正確提供「插入位置附近」的提示迭代器，可以加快插入效率(從O(log n)降為平攤O(1))
    // 即使hint提供錯誤，insert仍會正確插入到該排序的正確位置，只是會失去效能優化的效果
    multiset<int> ms2 = {1, 3, 5};
    ms2.insert(ms2.end(), 7);  // 提示: 7應該插入在end()附近(因為7是目前最大值)
    cout<<"ms2: "; for (const int& x:ms2) cout<<x<<' '; cout<<endl;
    // 輸出: ms2: 1 3 5 7


    cout<<("======================\n");// 分隔線


    // key_comp() / value_comp(): 回傳目前使用的「比較函式物件」，可用來呼叫並比較兩個元素的大小關係
    // (multiset中key_comp()與value_comp()效果相同，因為元素本身就是key)
    multiset<int> ms3;
    auto cmp = ms3.key_comp();
    cout<< cmp(1, 2) <<endl;  // 輸出: 1 (預設為less<int>，1<2成立，回傳true)
    cout<< cmp(2, 1) <<endl;  // 輸出: 0 (2<1不成立，回傳false)


    cout<<("======================\n");// 分隔線


    // contains(x): C++20新增，判斷是否存在某個值(回傳bool)，語意比count()>0更直覺
    // 若編譯環境只到C++17，須改用 ms.count(x) > 0 或 ms.find(x)!=ms.end()
    multiset<int> ms4 = {1, 2, 2};
    cout<< (ms4.count(2) > 0) <<endl;  // 輸出: 1 (C++17相容寫法，存在值2)
    cout<< (ms4.count(9) > 0) <<endl;  // 輸出: 0 (不存在值9)
    // 若為C++20環境，也可以直接寫成: cout<< ms4.contains(2) <<endl;  // 輸出: 1


    cout<<("======================\n");// 分隔線


    // 搭配<algorithm>/<numeric>使用: 由於multiset的iterator只是雙向迭代器，
    // 大部分需要隨機存取的演算法(如sort)無法使用(況且multiset本來就「永遠排序好」，
    // 也完全不需要再呼叫sort())，但count_if、accumulate等只需要雙向(甚至只需要輸入)
    // 迭代器的演算法仍然可以正常運作

    multiset<int> ms5 = {80, 60, 80, 90, 80, 70};

    // 計算有幾個元素「>= 80」
    int cnt = count_if(ms5.begin(), ms5.end(), [](int x){ return x >= 80; });
    cout<< cnt <<endl;  // 輸出: 4

    // 計算所有元素的總和
    int sum = accumulate(ms5.begin(), ms5.end(), 0);
    cout<< sum <<endl;  // 輸出: 460 (60+70+80+80+80+90=460)


    cout<<("======================\n");// 分隔線


    // 「修改」multiset中某個元素的正確做法: 先erase()刪除舊值，再insert()新值
    // (不可直接用迭代器賦值，因為元素本身是排序依據，不允許修改)
    ms5 = {1, 2, 3};
    auto itOld = ms5.find(2);
    if (itOld != ms5.end()){
        ms5.erase(itOld);   // 先刪除舊值2
        ms5.insert(99);     // 再插入新值99
    }
    for (const int& x : ms5) cout<<x<<' ';
    cout<<endl;
    // 輸出: 1 3 99
}
}


// 本篇筆記參考cppreference std::multiset (https://en.cppreference.com/w/cpp/container/multiset)
// Generated by Claude 2026/10/2
