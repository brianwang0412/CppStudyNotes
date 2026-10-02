#include<forward_list>  //需引入forward_list標頭檔

#include<iostream>
#include<algorithm>
#include<numeric>
#include<iterator>   // std::next / std::advance / std::distance，用於forward_list不支援隨機存取時移動迭代器，也用來取代size()計算長度
using namespace std;

// 使用Traversal_fl來表示遍歷forward_list fl的輸出結果
#define Traversal_fl for (const int& i:fl) cout<<i<<' '; cout<<endl;
// 使用Traversal_ff來表示遍歷forward_list ff(即二維forward_list陣列)的輸出結果
#define Traversal_ff for (const auto i:ff){for (const int j:i)cout<<j<<' ';cout<<endl;}

/*
前言: forward_list的特色、用途

forward_list 是一種「單向鏈結串列 (singly linked list)」，每個節點只有一個指向「下一個節點」的指標(沒有指向前一個節點的指標)
它是C++11才新增的容器，設計目標是取代「效能極致精簡」的自製單向鏈結串列，因此犧牲了不少方便的功能

相較於 list(雙向鏈結串列)，forward_list 為了讓每個節點的記憶體開銷降到最低、操作降到最快，做了以下取捨:
  - 沒有 size()：刻意不維護元素個數，才能讓push_front()/insert_after()維持真正的O(1)
                 若要取得長度，須自行呼叫 std::distance(fl.begin(), fl.end()) 計算，時間複雜度O(n)
  - 沒有 back()、push_back()、pop_back()、emplace_back()：因為單向鏈結，不知道「最後一個節點的前一個節點」是誰，
                 無法O(1)地在尾端新增/刪除元素，因此乾脆不提供
  - 沒有 operator[]、at()：不支援隨機存取，也因此完全沒有邊界檢查機制
  - 沒有 rbegin()/rend()：沒有反向迭代器，因為節點只知道「下一個」是誰，不知道「前一個」是誰
  - 所有插入/刪除函式都改名為 xxx_after()(如 insert_after()、erase_after()、emplace_after()、splice_after())
    因為單向鏈結串列要新增/刪除某節點時，必須先取得「前一個節點」才能把指標重新接起來，
    所以函式被設計成「傳入某個位置的迭代器，並在它之後操作」，而非直接對該位置操作
  - 額外提供 before_begin()(和cbefore_begin())：回傳一個指向「begin()之前」的特殊迭代器，
    讓insert_after()/erase_after()也能用來操作到「第一個元素」
  - forward_list的iterator屬於「前向迭代器 (Forward Iterator)」，只支援 it++，不支援 it--、it+n
    因此<algorithm>中需要「雙向迭代器」以上的函式(如 std::reverse())也無法使用，必須改用forward_list自己的成員函式(如 fl.reverse())
*/


int main(){
{
    // 《1. forward_list的宣告》

    // 建立空的forward_list，可以用於儲存整數(int)，名稱為fl1
    forward_list<int> fl1;

    // 建立可容納五個整數的 forward_list， 每個元素值預設是 0
    forward_list<int> fl2(5);  // {0, 0, 0, 0, 0}

    // 建立可容納五個整數的 forward_list， 每個元素值預設是 10
    forward_list<int> fl3(5, 10);  // {10, 10, 10, 10, 10}

    // 初始化包含元素的 forward_list，自動設定長度
    forward_list<int> fl4 = {1, 2, 3, 4};  //fl4的長度為 4

    // 複製建構，fl4與fl5會互相獨立
    forward_list<int> fl5(fl4);  //fl5為{1, 2, 3, 4}

    // 也可以用兩個iterator(迭代器)範圍來初始化
    // 注意: forward_list的iterator不支援 it+n 這種隨機存取運算(寫成 fl4.begin()+2 會編譯錯誤)
    // 必須改用<iterator>標頭檔提供的 std::next(it, n)，取得「往後移動n格」的新迭代器
    forward_list<int> fl6(fl4.begin(), next(fl4.begin(), 2));  // {1, 2}

    // 建立 3個元素、每個元素都是 {1,2} 的 二維forward_list
    forward_list<forward_list<int>> ff1(3, forward_list<int>{1,2});  // {{1,2}, {1,2}, {1,2}}
    // 這裡的forward_list<int>{1,2}，代表一個臨時創建的一維forward_list，並且包含 1,2 兩個元素

    // 也可以直接初始化二維forward_list
    forward_list<forward_list<int>> ff2 = {{1,2}, {3,4,5}, {6,7,8,9}};

    // 利用 fl.assign() 清空並重新填入forward_list的內容
    // 這裡介紹填入n個相同的值
    forward_list<int> fl7(100,1);
    cout<<distance(fl7.begin(), fl7.end())<<endl; // 長度為100 (forward_list沒有size()，須用distance()計算)

    fl7.assign(10, 77);
    cout<<distance(fl7.begin(), fl7.end())<<endl; // 長度為10
}
cout<<("====================================\n");// 分隔線
{
    // 《2. forward_list的新增、存取與刪除》
    // 注意: forward_list沒有push_back()、insert()、operator[]、at()
    //       (insert()改名為insert_after()，因為單向鏈結只能「在指定位置之後」操作)

    forward_list<int> fl;  // 建立一個空的forward_list

    // 1. 新增 (push_front、insert_after與before_begin)

    // fl.push_front(x) 在forward_list的開頭新增元素 (forward_list沒有push_back()，只能從開頭新增)
    fl.push_front(3);
    fl.push_front(2);
    fl.push_front(1);
    Traversal_fl // 遍歷輸出: 1 2 3

    // fl.insert_after(pos, x) 在指定位置「之後」插入元素
    // 注意函式名稱多了 _after，這是forward_list與list/vector最大的差異之一：
    // 單向鏈結串列無法從pos反推「pos的前一個節點」，因此插入操作被設計成「在pos之後插入」，而不是「在pos插入」
    fl.insert_after(fl.begin(), 999);  // 在第一個元素(index=0)之後插入999
    Traversal_fl // 輸出: 1 999 2 3

    // 若想插入「開頭之前」(即讓新元素成為新的第一個元素)，須搭配 fl.before_begin() 使用
    // before_begin() 回傳一個指向「begin()前一格」的特殊迭代器，本身不可解參考(不能*before_begin())，
    // 但可以傳給insert_after()/erase_after()，讓這兩個函式也能操作到「第一個元素」
    fl.insert_after(fl.before_begin(), 0);
    Traversal_fl // 輸出: 0 1 999 2 3


    {// 二維陣列中新增元素
    forward_list<forward_list<int>> ff;
    ff.push_front(forward_list<int>{4,5,6});  // 因為只能從開頭新增，須「先放後面的列」
    ff.push_front(forward_list<int>{1,2,3});  // 再放前面的列，最後順序才會是 {1,2,3} 接著 {4,5,6}
    for (const auto& i : ff){
        for (const int& j : i) cout<<j<<' ';
        cout<<endl;
    }
    /*
    輸出:
    1 2 3
    4 5 6
    */}


    cout<<("======================\n");// 分隔線


    // 2. 存取 (.front())
    // forward_list沒有back()、operator[]、at()，只能存取「第一個元素」，也沒有邊界檢查函式可用(因此沒有std::out_of_range的範例)

    fl = {1,2,3,4,5};

    // 使用 fl.front() 來存取
    fl.front() = 2026; //取第一個元素
    cout<< fl.front() <<endl;  // 輸出: 2026

    Traversal_fl // 遍歷輸出: 2026 2 3 4 5

    // 若要存取中間元素(例如index=2)，只能用迭代器從begin()開始逐步往「後」移動(++)，無法往前(沒有--)
    auto it_mid = next(fl.begin(), 2);  // 從begin()往後移動2格，指向index=2的元素
    cout<< *it_mid <<endl;  // 輸出: 3
    *it_mid = 999;  // 透過iterator修改該元素的值
    Traversal_fl // 輸出: 2026 2 999 4 5

    cout<<("======================\n");// 分隔線

    // 3. 刪除

    // 現在forward_list fl中有5個元素 {2026, 2, 999, 4, 5}

    // 用 fl.erase_after(pos) 刪除pos「之後」的元素(注意! 不是刪除pos本身)
    fl.erase_after(fl.begin());  // 刪除第二個元素(2)，即begin()之後的那個元素
    Traversal_fl // 輸出: 2026 999 4 5

    // 若要刪除「第一個元素」，須搭配before_begin()使用，才能刪到index=0
    fl.erase_after(fl.before_begin());
    Traversal_fl // 輸出: 999 4 5

    // fl.erase_after(first, last) 刪除(first, last)之間的元素，注意是「不含first、也不含last」的開區間
    fl = {1,2,3,4,5};
    fl.erase_after(fl.begin(), next(fl.begin(),3)); // 刪除(begin(), begin()+3)之間的元素，即index=1,2(2,3)
    Traversal_fl // 輸出: 1 4 5

    // 用 fl.pop_front() 刪除第一個元素 (forward_list沒有pop_back())
    fl.pop_front();
    Traversal_fl // 輸出: 4 5

    // 用 fl.clear() 清空 forward_list
    fl.clear();
    Traversal_fl // 輸出:     (沒有元素，清空了)

    // 刪除指定元素: 因為forward_list沒有辦法從一個節點「往前退」，
    // 若用find()找到目標元素的迭代器it，並不能直接erase_after(it)刪除it本身(那樣會刪到it的下一個)
    // 因此若只知道元素的「值」，最方便的做法是改用forward_list提供的 remove()(與list相同，直接刪除所有符合值的元素)
    fl = {1,2,3,4,5};
    fl.remove(3);  // 刪除所有值為3的元素
    Traversal_fl  // 輸出: 1 2 4 5


    {// 二維forward_list的刪除
    forward_list<forward_list<int>> ff = {{1,2}, {3,4}, {5,6}};

    ff.erase_after(ff.before_begin()); //刪除第一列 {1,2} (須用before_begin()才能刪到第一個元素)
    Traversal_ff
    /*
    輸出:
    3 4
    5 6
    */

    ff.front().erase_after(ff.front().before_begin()); //刪除第一列的第一個元素 3
    Traversal_ff
    /*
    輸出:
    4
    5 6
    */

    ff.clear();
    Traversal_ff // 輸出:     (沒有元素，清空了)

    }
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 遍歷》
    // 注意: forward_list沒有operator[]，不能用一般for迴圈搭配index存取；也沒有rbegin()/rend()，無法反向遍歷

    forward_list<int> fl = {1,2,3,4,5};

    // 1. 使用「以範圍為基礎的 for 語句」（Range-based for Statement）
    for (int element : fl){
        cout<< element << ' ';
    }
    cout<<endl;
    // 輸出: 1 2 3 4 5


    // 2. 若想更進一步修改元素值，可以改為用element作為forward_list fl 中的元素的參考(reference)
    for (int& element : fl){
        element += 1;
    }
    Traversal_fl  // 輸出: 2 3 4 5 6


    // 3. 使用迭代器(iterator)遍歷
    // forward_list的iterator屬於「前向迭代器(Forward Iterator)」，只支援 it++，不支援 it--、it+n
    for (forward_list<int>::iterator it = fl.begin(); it != fl.end(); it++){
        cout<< *it << ' ';
    }
    cout<<endl;
    // 輸出: 2 3 4 5 6

    // 4. 沒有反向遍歷的方式(沒有rbegin()/rend())，若真的需要「由尾到頭」的順序，只能:
    //    (1) 呼叫 fl.reverse() 把整個forward_list原地反轉後，再正向遍歷一次，或
    //    (2) 把元素複製到 vector/list 等支援反向迭代器的容器，再用那個容器逆向輸出
    fl.reverse();
    Traversal_fl // 輸出: 6 5 4 3 2 (原本2 3 4 5 6反轉後的結果)
    fl.reverse();  // 用完記得反轉回來，恢復原本順序
    Traversal_fl // 輸出: 2 3 4 5 6
}
cout<<("====================================\n");// 分隔線
{
    //《4. 常用功能》

    forward_list<int> fl = {1,2,3,4};

    // 取得長度(元素個數): forward_list「沒有」size()!
    // 必須自行用 std::distance(fl.begin(), fl.end()) 計算，時間複雜度為O(n)(這點與vector/deque的O(1) size()不同)
    int n = distance(fl.begin(), fl.end());
    cout<< n <<endl;  // 輸出: 4

    // 注意: forward_list「沒有」capacity()、reserve()、data()函式(理由與list相同，節點分散各處，並非連續記憶體)

    // 判斷是否為空 (empty()不需要走訪整個容器，仍然是O(1)，因為只需檢查頭節點是否存在)
    cout<< fl.empty() <<endl;  // 輸出: 0 (表示非空)

    // 調整大小: fl.resize(n) 或 fl.resize(n, val)
    fl.resize(6);       // 長度不足時，用預設值0補齊
    Traversal_fl // 輸出: 1 2 3 4 0 0

    fl.resize(8, 9);     // 長度不足時，用指定值9補齊
    Traversal_fl // 輸出: 1 2 3 4 0 0 9 9

    fl.resize(3);        // 長度超過時，直接從尾端截斷
    Traversal_fl // 輸出: 1 2 3

    // 交換兩個forward_list的內容
    forward_list<int> fl1={1,2,3}, fl2={7,8,9};
    fl1.swap(fl2);
    cout<<"fl1: ";
    for (const int& i:fl1) cout<<i<<' ';cout<<endl;  //輸出: fl1: 7 8 9

    cout<<"fl2: ";
    for (const int& i:fl2) cout<<i<<' ';cout<<endl;  //輸出: fl2: 1 2 3


    cout<<("======================\n");// 分隔線


    // 排序: fl.sort()
    // 注意: forward_list的迭代器只是「前向迭代器」，連std::reverse()需要的「雙向迭代器」都不滿足，
    //       更不用說std::sort()需要的「隨機存取迭代器」了，因此 sort(fl.begin(), fl.end()) 會「編譯失敗」
    //       排序「只能」使用forward_list自己的成員函式 fl.sort()
    fl = {5,4,3,2,1};
    fl.sort();  // 由小到大排序(預設)
    Traversal_fl  //輸出: 1 2 3 4 5

    fl.sort(greater<int>());  //由大到小排序，也可以改用Lambda表達式: [](int a, int b) { return a > b; }
    Traversal_fl  //輸出: 5 4 3 2 1


    cout<<("======================\n");// 分隔線


    // 反轉: fl.reverse()
    // 同理，std::reverse(fl.begin(), fl.end()) 需要「雙向迭代器」以上，forward_list的迭代器不滿足，「無法通過編譯」
    // 必須改用forward_list自己的成員函式 fl.reverse()
    fl = {1,3,5,7,9};
    fl.reverse();
    Traversal_fl  //輸出: 9 7 5 3 1


    cout<<("======================\n");// 分隔線


    // 尋找元素的位置: 搭配<algorithm>的find()使用(find()只需要輸入迭代器，符合前向迭代器即可正常使用)
    fl = {1,3,5,7,9};
    auto it = find(fl.begin(), fl.end(), 5);  // it 為指向該元素的迭代器(iterator)
    //若沒找到會回傳 fl.end()
    if (it != fl.end()){
        cout<<"Found "<< *it <<endl;
        cout<<"It's at index "<< distance(fl.begin(), it) <<endl;
        // 注意: distance()對前向迭代器而言，內部是「逐一移動計算」，時間複雜度O(n)，
        //       這與vector/deque（隨機存取迭代器，O(1)）不同，只是恰好function介面相同
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
    fl = {1,1,1,2};
    int cnt = count(fl.begin(), fl.end(), 1);
    cout<< cnt <<endl;  //輸出: 3


    // 搭配 <numeric> 使用

    fl = {10,20,30};

    // 加總
    int sum = accumulate(fl.begin(), fl.end(), 0); // 最後的0代表初始值為0
    cout<< sum <<endl;  //輸出: 60

    // 連乘
    int product = accumulate(fl.begin(), fl.end(), 1, [](int a, int b){return a*b;});
    cout<< product <<endl;  //輸出: 6000


    cout<<("======================\n");// 分隔線


    // emplace系列: emplace_front / emplace_after (forward_list沒有emplace_back)
    // 功能與push_front / insert_after類似，但是「直接在容器內部建構元素」，可省去一次額外的複製或搬移
    fl = {2,3,4};
    fl.emplace_front(1);                   // 相當於 fl.push_front(1) -> {1,2,3,4}
    fl.emplace_after(fl.begin(), 999);     // 相當於 fl.insert_after(fl.begin(), 999) -> 在index=0之後插入999
    Traversal_fl // 輸出: 1 999 2 3 4


    cout<<("======================\n");// 分隔線


    // remove_if(): 刪除「所有」符合條件的元素(搭配Lambda表達式)
    fl = {1,2,3,4,5,6,7,8};
    fl.remove_if([](int x){ return x % 2 == 0; });  // 刪除所有偶數
    Traversal_fl  // 輸出: 1 3 5 7


    cout<<("======================\n");// 分隔線


    // unique(): 刪除「相鄰重複」的元素，只保留一個(注意: 若重複元素不相鄰，須先sort()才能完全去重)
    fl = {1,1,2,2,2,3,1,1};
    fl.unique();
    Traversal_fl  // 輸出: 1 2 3 1
    // 可以看到最後的1沒有被去除，因為它與前面的1並不相鄰

    fl = {3,1,2,2,1,3,3};
    fl.sort();     // 先排序，讓相同的值變成相鄰
    fl.unique();   // 再去重，才能得到「全域」不重複的結果
    Traversal_fl  // 輸出: 1 2 3


    cout<<("======================\n");// 分隔線


    // merge(): 合併「兩個已排序」的forward_list，合併後仍保持排序，並且會把other清空(元素被「搬移」過去，而非複製)
    forward_list<int> flA = {1,3,5};
    forward_list<int> flB = {2,4,6};
    flA.merge(flB);  // 將flB合併進flA(兩者須事先排序好，否則結果不保證正確)
    cout<<"flA: "; for (const int& i:flA) cout<<i<<' '; cout<<endl;  // 輸出: flA: 1 2 3 4 5 6
    cout<<"flB: "; for (const int& i:flB) cout<<i<<' '; cout<<endl;  // 輸出: flB: (空的，因為元素都被搬移到flA了)


    cout<<("======================\n");// 分隔線


    // splice_after(): forward_list版本的splice，因為單向鏈結，所有splice都改名為splice_after()
    // 且部分重載的語意與list::splice()「不同」，使用時要特別小心!

    // 4-1. splice_after(pos, other): 將other的「全部」節點搬移到pos「之後」，搬移後other會變空
    //      (與list::splice(pos, other)語意相同，只差在插入位置是pos之後，而非pos之前)
    forward_list<int> flC = {1,2,3};
    forward_list<int> flD = {100,200,300};
    flC.splice_after(flC.begin(), flD);  // 將flD全部節點搬移到flC的index=0之後
    cout<<"flC: "; for (const int& i:flC) cout<<i<<' '; cout<<endl;  // 輸出: flC: 1 100 200 300 2 3
    cout<<"flD: "; for (const int& i:flD) cout<<i<<' '; cout<<endl;  // 輸出: flD: (空的)

    // 4-2. splice_after(pos, other, it): 注意! 搬移的是「it之後的那一個節點」，而不是it本身指向的節點
    //      這與 list::splice(pos, other, it) 語意不同：list搬移的是it本身，forward_list搬移的是it的下一個
    //      原因: 單向鏈結串列要搬移某節點時，必須先知道它「前一個」節點，才能把前一個節點的指標重新接起來
    //           因此函式被設計成傳入「前一個節點的迭代器」，實際被搬移的是它指向的下一個節點
    forward_list<int> flE = {1,2,3};
    forward_list<int> flF = {100,200,300};
    flE.splice_after(flE.begin(), flF, flF.begin());  // 搬移flF中begin()「之後」的那個節點(200)，接到flE的begin()之後
    cout<<"flE: "; for (const int& i:flE) cout<<i<<' '; cout<<endl;  // 輸出: flE: 1 200 2 3
    cout<<"flF: "; for (const int& i:flF) cout<<i<<' '; cout<<endl;  // 輸出: flF: 100 300

    // 4-3. splice_after(pos, other, first, last): 搬移other中「(first,last)之間」的節點(不含first、也不含last)到pos之後
    forward_list<int> flG = {1,2,3};
    forward_list<int> flH = {100,200,300,400,500};
    flG.splice_after(flG.begin(), flH, flH.begin(), next(flH.begin(),4));  // 搬移flH中(begin(), begin()+4)之間的節點(200,300,400)到flG的begin()之後
    cout<<"flG: "; for (const int& i:flG) cout<<i<<' '; cout<<endl;  // 輸出: flG: 1 200 300 400 2 3
    cout<<"flH: "; for (const int& i:flH) cout<<i<<' '; cout<<endl;  // 輸出: flH: 100 500


    cout<<("======================\n");// 分隔線


    // max_size(): 回傳理論上forward_list「最多」能容納的元素個數上限(受限於系統與實作，實際能用到的遠小於此值)
    // 由於數值極大且因平台而異，這裡僅示範呼叫方式，不列出實際數字
    cout<< (fl.max_size() > 0) <<endl;  // 輸出: 1 (只確認max_size()回傳的上限值大於0，不印出實際數字)
}
}


// Generated by Claude 2026/9/2 (https://claude.ai/share/9c297450-3176-4108-a045-e70c84cde0c3)
