#include<list>  //需引入list標頭檔

#include<iostream>
#include<algorithm>
#include<numeric>
#include<iterator>   // std::next / std::advance / std::distance，用於list不支援隨機存取時移動迭代器
#include<stdexcept>  // std::out_of_range 定義在 <stdexcept> 標頭檔中
using namespace std;

// 使用Traversal_lt來表示遍歷list lt的輸出結果
#define Traversal_lt for (const int& i:lt) cout<<i<<' '; cout<<endl;
// 使用Traversal_ll來表示遍歷list ll(即二維list陣列)的輸出結果
#define Traversal_ll for (const auto i:ll){for (const int j:i)cout<<j<<' ';cout<<endl;}

/*
前言: list的特色、用途

list 是一種「雙向鏈結串列 (doubly linked list)」，每個節點各自儲存資料，並用指標與前後節點相連

相較於 vector / deque 底層仰賴「連續(或分區連續)記憶體」，
list 的節點分散在記憶體各處，因此:
  - 在「任意位置」插入/刪除元素都是 O(1) (只要已經有該位置的iterator，不需搬移其他元素)
  - 但「不支援隨機存取」，沒有 operator[] 與 at()，也沒有 data() / capacity() / reserve()
  - list的iterator屬於「雙向迭代器 (Bidirectional Iterator)」，只支援 ++ / --，不支援 it+n、it1-it2 等隨機存取運算
    因此<algorithm>的 sort()、部分演算法無法直接用在list身上，必須改用list自己的成員函式(如 lt.sort())
*/


int main(){
{
    // 《1. list的宣告》

    // 建立空的list，可以用於儲存整數(int)，名稱為lt1
    list<int> lt1;

    // 建立可容納五個整數的 list， 每個元素值預設是 0
    list<int> lt2(5);  // {0, 0, 0, 0, 0}

    // 建立可容納五個整數的 list， 每個元素值預設是 10
    list<int> lt3(5, 10);  // {10, 10, 10, 10, 10}

    // 初始化包含元素的 list，自動設定長度
    list<int> lt4 = {1, 2, 3, 4};  //lt4的長度為 4

    // 複製建構，lt4與lt5會互相獨立
    list<int> lt5(lt4);  //lt5為{1, 2, 3, 4}

    // 也可以用兩個iterator(迭代器)範圍來初始化
    // 注意: list的iterator不支援 it+n 這種隨機存取運算(寫成 lt4.begin()+2 會編譯錯誤)
    // 必須改用<iterator>標頭檔提供的 std::next(it, n)，取得「往後移動n格」的新迭代器
    list<int> lt6(lt4.begin(), next(lt4.begin(), 2));  // {1, 2}

    // 建立 3x2 的二維list，每個內層list初始化為 {1, 2}
    list<list<int>> ll1(3, list<int>{1,2});  // {{1,2}, {1,2}, {1,2}}
    // 這裡的list<int>{1,2}，代表一個臨時創建的一維list，並且包含 1,2 兩個元素

    // 也可以直接初始化二維list
    list<list<int>> ll2 = {{1,2}, {3,4,5}, {6,7,8,9}};

    // 利用 lt.assign() 清空並重新填入list的內容
    // 這裡介紹填入n個相同的值
    list<int> lt7(100,1);
    cout<<lt7.size()<<endl; // 長度為100

    lt7.assign(10, 77);
    cout<<lt7.size()<<endl; // 長度為10
}
cout<<("====================================\n");// 分隔線
{
    // 《2. list的新增、存取與刪除》
    // 注意: list「沒有」operator[]與at()，因為list不支援隨機存取，無法用index直接跳到任意節點

    list<int> lt;  // 建立一個空的list

    // 1. 新增 (push_back、push_front與insert)

    // lt.push_back(x) 在list的尾端新增元素
    lt.push_back(1);
    lt.push_back(2);
    lt.push_back(3);
    Traversal_lt // 遍歷輸出: 1 2 3

    // lt.push_front(x) 在list的開頭新增元素 (與deque相同，vector沒有這個函式)
    lt.push_front(0);
    lt.push_front(-1);
    Traversal_lt // 輸出: -1 0 1 2 3

    // lt.insert(pos, x) 在list的指定位置插入元素
    // 注意: pos必須是iterator，list沒有operator[]，因此無法像vector一樣用index+運算來移動位置
    // 若要移到第n個位置的iterator，須搭配<iterator>的 std::next()/std::advance() 使用
    lt.insert(next(lt.begin(), 2), 999);  //在index=2的位置插入元素(即從begin()往後移動2格)
    Traversal_lt // 輸出: -1 0 999 1 2 3


    {// 二維陣列中新增元素
    list<list<int>> ll;
    ll.push_back(list<int>{1,2,3});
    ll.push_back(list<int>{4,5,6});
    for (const auto& i : ll){
        for (const int& j : i) cout<<j<<' ';
        cout<<endl;
    }
    /*
    輸出:
    1 2 3
    4 5 6
    */}


    cout<<("======================\n");// 分隔線


    // 2. 存取 (.front() .back())
    // list只能存取「頭尾」，若要存取中間元素，必須用iterator逐步移動(++/--)才能到達，無法直接跳躍

    lt = {1,2,3,4,5};

    // 使用 lt.front()與lt.back() 來存取
    lt.front() = 2026; //取第一個元素
    cout<< lt.front() <<endl;  // 輸出: 2026

    lt.back() = 1234;  //取最後一個元素
    cout<< lt.back() <<endl;  // 輸出: 1234

    Traversal_lt // 遍歷輸出: 2026 2 3 4 1234

    // 若要存取中間元素(例如index=2)，須用std::next()取得該位置的iterator後再解參考(dereference)
    auto it_mid = next(lt.begin(), 2);  // 從begin()往後移動2格，指向index=2的元素
    cout<< *it_mid <<endl;  // 輸出: 3
    *it_mid = 999;  // 透過iterator修改該元素的值
    Traversal_lt // 輸出: 2026 2 999 4 1234

    cout<<("======================\n");// 分隔線

    // 3. 刪除

    // 現在list lt中有5個元素 {2026, 2, 999, 4, 1234}

    // 用 lt.erase(pos) 刪除指定位置的元素(pos為iterator)
    lt.erase(next(lt.begin(), 1));  // 刪除第二個元素(2)
    Traversal_lt // 輸出: 2026 999 4 1234

    lt.erase(lt.begin(), next(lt.begin(), 2)); // 刪除第一到第二個元素(不含第三個)
    Traversal_lt // 輸出: 4 1234

    // 用 lt.pop_back() 刪除最後一個元素
    lt.pop_back();
    Traversal_lt // 輸出: 4

    // 用 lt.pop_front() 刪除第一個元素 (與deque相同，vector沒有這個函式)
    lt.push_front(100);
    Traversal_lt // 輸出: 100 4
    lt.pop_front();
    Traversal_lt // 輸出: 4

    // 用 lt.clear() 清空 list
    lt.clear();
    Traversal_lt // 輸出:     (沒有元素，清空了)

    // 刪除指定元素(用find找到位置後再erase)
    lt = {1,2,3,4,5};
    lt.erase(find(lt.begin(), lt.end(), 3));
    Traversal_lt  // 輸出: 1 2 4 5

    // list額外提供 lt.remove(val)：直接刪除「所有」值等於val的元素(不需搭配find)
    lt = {1,3,3,5,3};
    lt.remove(3);  // 刪除所有值為3的元素
    Traversal_lt  // 輸出: 1 5


    {// 二維list的刪除
    list<list<int>> ll = {{1,2}, {3,4}, {5,6}};

    ll.erase(ll.begin()); //刪除第一列 {1,2}
    Traversal_ll
    /*
    輸出:
    3 4
    5 6
    */

    ll.front().erase(ll.front().begin()); //刪除第一列的第一個元素 3
    Traversal_ll
    /*
    輸出:
    4
    5 6
    */

    ll.clear();
    Traversal_ll // 輸出:     (沒有元素，清空了)

    }
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 遍歷》
    // 注意: list不支援隨機存取，因此「不能」用 for(int i=0;i<lt.size();i++) 搭配 lt[i] 的寫法來遍歷

    list<int> lt = {1,2,3,4,5};

    // 1. 使用「以範圍為基礎的 for 語句」（Range-based for Statement）
    for (int element : lt){
        cout<< element << ' ';
    }
    cout<<endl;
    // 輸出: 1 2 3 4 5


    // 2. 若想更進一步修改元素值，可以改為用element作為list lt 中的元素的參考(reference)
    for (int& element : lt){
        element += 1;
    }
    Traversal_lt  // 輸出: 2 3 4 5 6


    // 3. 使用迭代器(iterator)遍歷
    // list的iterator屬於「雙向迭代器(Bidirectional Iterator)」，只支援 it++、it--，不支援 it+n
    for (list<int>::iterator it = lt.begin(); it != lt.end(); it++){
        cout<< *it << ' ';
    }
    cout<<endl;
    // 輸出: 2 3 4 5 6

    // 4. 反向迭代器(reverse_iterator)：用rbegin()/rend()由尾到頭遍歷
    for (list<int>::reverse_iterator rit = lt.rbegin(); rit != lt.rend(); rit++){
        cout<< *rit << ' ';
    }
    cout<<endl;
    // 輸出: 6 5 4 3 2
}
cout<<("====================================\n");// 分隔線
{
    //《4. 常用功能》

    list<int> lt = {1,2,3,4};

    // 取得長度(元素個數)
    int n = lt.size();
    cout<< n <<endl;  // 輸出: 4

    // 注意: list「沒有」capacity()與reserve()函式(理由與deque相同，底層並非連續記憶體，沒有「容量」概念)
    // list也「沒有」data()函式(理由同上，節點分散各處，無法回傳單一連續陣列的指標)

    // 判斷是否為空
    cout<< lt.empty() <<endl;  // 輸出: 0 (表示非空)

    // 調整大小: lt.resize(n) 或 lt.resize(n, val)
    lt.resize(6);       // 長度不足時，用預設值0補齊
    Traversal_lt // 輸出: 1 2 3 4 0 0

    lt.resize(8, 9);     // 長度不足時，用指定值9補齊
    Traversal_lt // 輸出: 1 2 3 4 0 0 9 9

    lt.resize(3);        // 長度超過時，直接從尾端截斷
    Traversal_lt // 輸出: 1 2 3

    // 交換兩個list的內容
    list<int> lt1={1,2,3}, lt2={7,8,9};
    lt1.swap(lt2);
    cout<<"lt1: ";
    for (const int& i:lt1) cout<<i<<' ';cout<<endl;  //輸出: lt1: 7 8 9

    cout<<"lt2: ";
    for (const int& i:lt2) cout<<i<<' ';cout<<endl;  //輸出: lt2: 1 2 3


    cout<<("======================\n");// 分隔線


    // 排序: lt.sort()
    // 注意: <algorithm>的 std::sort() 需要「隨機存取迭代器」，list的迭代器不支援，因此「不能」寫成 sort(lt.begin(), lt.end())
    // 必須改用list自己的成員函式 lt.sort()
    lt = {5,4,3,2,1};
    lt.sort();  // 由小到大排序(預設)
    Traversal_lt  //輸出: 1 2 3 4 5

    lt.sort(greater<int>());  //由大到小排序，也可以改用Lambda表達式: [](int a, int b) { return a > b; }
    Traversal_lt  //輸出: 5 4 3 2 1


    cout<<("======================\n");// 分隔線


    // 反轉: lt.reverse()
    // 同理，<algorithm>的 std::reverse() 需要雙向迭代器以上，其實list的迭代器「符合」雙向迭代器規範，
    // 所以 reverse(lt.begin(), lt.end()) 實際上「可以」正常使用；但list仍額外提供效率更好的成員函式 lt.reverse()，建議優先使用
    lt = {1,3,5,7,9};
    lt.reverse();
    Traversal_lt  //輸出: 9 7 5 3 1


    cout<<("======================\n");// 分隔線


    // 尋找元素的位置: 搭配<algorithm>的find()使用(find只需要輸入迭代器，符合雙向迭代器即可正常使用)
    lt = {1,3,5,7,9};
    auto it = find(lt.begin(), lt.end(), 5);  // it 為指向該元素的迭代器(iterator)
    //若沒找到會回傳 lt.end()
    if (it != lt.end()){
        cout<<"Found "<< *it <<endl;
        cout<<"It's at index "<< distance(lt.begin(), it) <<endl;
        // 注意: distance()對雙向迭代器而言，內部是「逐一移動計算」，時間複雜度O(n)，
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
    lt = {1,1,1,2};
    int cnt = count(lt.begin(), lt.end(), 1);
    cout<< cnt <<endl;  //輸出: 3


    // 搭配 <numeric> 使用

    lt = {10,20,30};

    // 加總
    int sum = accumulate(lt.begin(), lt.end(), 0); // 最後的0代表初始值為0
    cout<< sum <<endl;  //輸出: 60

    // 連乘
    int product = accumulate(lt.begin(), lt.end(), 1, [](int a, int b){return a*b;});
    cout<< product <<endl;  //輸出: 6000


    cout<<("======================\n");// 分隔線


    // emplace系列: emplace_back / emplace_front / emplace
    // 功能與push_back / push_front / insert類似，但是「直接在容器內部建構元素」，可省去一次額外的複製或搬移
    lt = {1,2,3};
    lt.emplace_back(4);                    // 相當於 lt.push_back(4)
    lt.emplace_front(0);                   // 相當於 lt.push_front(0)
    lt.emplace(next(lt.begin(),2), 999);   // 相當於 lt.insert(next(lt.begin(),2), 999)
    Traversal_lt // 輸出: 0 1 999 2 3 4


    cout<<("======================\n");// 分隔線


    // remove_if(): 刪除「所有」符合條件的元素(搭配Lambda表達式)
    lt = {1,2,3,4,5,6,7,8};
    lt.remove_if([](int x){ return x % 2 == 0; });  // 刪除所有偶數
    Traversal_lt  // 輸出: 1 3 5 7


    cout<<("======================\n");// 分隔線


    // unique(): 刪除「相鄰重複」的元素，只保留一個(注意: 若重複元素不相鄰，須先sort()才能完全去重)
    lt = {1,1,2,2,2,3,1,1};
    lt.unique();
    Traversal_lt  // 輸出: 1 2 3 1
    // 可以看到最後的1沒有被去除，因為它與前面的1並不相鄰

    lt = {3,1,2,2,1,3,3};
    lt.sort();     // 先排序，讓相同的值變成相鄰
    lt.unique();   // 再去重，才能得到「全域」不重複的結果
    Traversal_lt  // 輸出: 1 2 3


    cout<<("======================\n");// 分隔線


    // merge(): 合併「兩個已排序」的list，合併後仍保持排序，並且會把other清空(元素被「搬移」過去，而非複製)
    list<int> ltA = {1,3,5};
    list<int> ltB = {2,4,6};
    ltA.merge(ltB);  // 將ltB合併進ltA(兩者須事先排序好，否則結果不保證正確)
    cout<<"ltA: "; for (const int& i:ltA) cout<<i<<' '; cout<<endl;  // 輸出: ltA: 1 2 3 4 5 6
    cout<<"ltB: "; for (const int& i:ltB) cout<<i<<' '; cout<<endl;  // 輸出: ltB: (空的，因為元素都被搬移到ltA了)


    cout<<("======================\n");// 分隔線


    // splice(): list最特別的功能，可以將「另一個list的部分節點」直接「搬移」接到本身的指定位置
    // 由於是直接搬移節點(而非複製)，時間複雜度為O(1)(或O(n)，依重載版本而定)，這是vector/deque做不到的

    // 3-1. splice(pos, other): 將other的「全部」節點搬移到pos之前，搬移後other會變空
    list<int> ltC = {1,2,3};
    list<int> ltD = {100,200,300};
    ltC.splice(next(ltC.begin(),1), ltD);  // 將ltD全部節點搬移到ltC的index=1之前
    cout<<"ltC: "; for (const int& i:ltC) cout<<i<<' '; cout<<endl;  // 輸出: ltC: 1 100 200 300 2 3
    cout<<"ltD: "; for (const int& i:ltD) cout<<i<<' '; cout<<endl;  // 輸出: ltD: (空的)

    // 3-2. splice(pos, other, it): 只搬移other中「it所指向的單一節點」到pos之前
    list<int> ltE = {1,2,3};
    list<int> ltF = {100,200,300};
    ltE.splice(ltE.begin(), ltF, next(ltF.begin(),1));  // 只搬移ltF中的200，接到ltE的開頭
    cout<<"ltE: "; for (const int& i:ltE) cout<<i<<' '; cout<<endl;  // 輸出: ltE: 200 1 2 3
    cout<<"ltF: "; for (const int& i:ltF) cout<<i<<' '; cout<<endl;  // 輸出: ltF: 100 300

    // 3-3. splice(pos, other, first, last): 搬移other中「[first,last)範圍」的節點到pos之前
    list<int> ltG = {1,2,3};
    list<int> ltH = {100,200,300,400,500};
    ltG.splice(ltG.end(), ltH, next(ltH.begin(),1), next(ltH.begin(),4));  // 搬移ltH的index=1~3(200,300,400)到ltG尾端
    cout<<"ltG: "; for (const int& i:ltG) cout<<i<<' '; cout<<endl;  // 輸出: ltG: 1 2 3 200 300 400
    cout<<"ltH: "; for (const int& i:ltH) cout<<i<<' '; cout<<endl;  // 輸出: ltH: 100 500
}
}


// Generated by Claude 2026/8/26 (https://claude.ai/share/9cab36b3-fd14-43b1-a69c-51175af8a4a0)