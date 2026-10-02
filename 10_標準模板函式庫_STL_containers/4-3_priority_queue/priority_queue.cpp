#include<queue>  // 需引入<queue>標頭檔 (priority_queue與queue定義在同一個標頭檔中)

#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<algorithm>    // make_heap、push_heap、pop_heap、sort_heap、is_heap
#include<functional>   // greater、less
#include<cstdlib>      // abs
#include<utility>      // pair、move、swap
#include<type_traits>  // is_same，用於檢查型別別名
using namespace std;

// 我使用Traversal_pq(pq)來表示「遍歷」priority_queue pq的輸出結果
// 注意: priority_queue沒有迭代器，無法直接遍歷，只能複製一份後，不斷輸出top()再pop()，這樣才不會破壞原本的priority_queue
// 輸出順序即為「優先順序由高到低」的順序
#define Traversal_pq(pq) { auto tmp=pq; while(!tmp.empty()){cout<<tmp.top()<<' ';tmp.pop();} cout<<endl; }

/*
前言: priority_queue的特性

1. priority_queue(優先佇列)是一種「每次取出優先權最高的元素」的資料結構，
   不論元素是什麼時候放進去的，top()永遠是「目前優先權最高」的那一個
   預設的比較方式是 less<T>，因此「最大的元素」優先權最高 (即預設為「最大堆 max-heap」)
2. priority_queue和queue一樣是「容器配接器 (container adapter)」，
   預設包裝vector，並用 <algorithm> 的堆積函式 (make_heap/push_heap/pop_heap) 維護堆積(heap)結構
   因此priority_queue「沒有」: 迭代器(begin()/end())、operator[]、at()、clear()、front()、back()、erase()
   也「不能」遍歷、不能查看或修改非頂端的元素，只能存取頂端(top)的元素
3. 時間複雜度:
   top()   : O(1)
   push()  : O(log n)
   emplace(): O(log n)
   pop()   : O(log n)
   size()/empty()/swap(): O(1)
   用兩個iterator範圍建構: O(n) (內部是make_heap，比一個一個push的O(n log n)更快)
4. 底層容器必須支援「隨機存取迭代器」，以及 front()、push_back()、pop_back()
   符合條件的標準容器只有 vector (預設) 與 deque；list「不行」(因為list不支援隨機存取)
5. 宣告的完整模板形式為: priority_queue<型別, 底層容器, 比較器>
   priority_queue<int>                           = priority_queue<int, vector<int>, less<int>>      (最大堆)
   priority_queue<int, vector<int>, greater<int>>                                                    (最小堆)
6. 「比較器」的意義要特別小心 (與sort()剛好相反，是常見的易錯點):
   比較器 comp(a, b) 回傳 true，表示「a的優先權比b低」(即b應該排在a前面，離top更近)
   less<int>    : comp(a,b) = a < b，a比較小 → a優先權較低 → 大的先出來 (最大堆)
   greater<int> : comp(a,b) = a > b，a比較大 → a優先權較低 → 小的先出來 (最小堆)
   也就是說，sort(..., greater<int>())是由大到小排序，但priority_queue<int, vector<int>, greater<int>>卻是「小的先出來」
*/

// 供《3. 自訂比較方式》使用的型別與比較器，需定義在main外面

// 作法一: 在自訂型別中重載 operator<，搭配預設的less<Task>使用
struct Task{
    int pri;      // 優先權，數字越大越優先
    string name;
};
bool operator<(const Task& a, const Task& b){
    return a.pri < b.pri;  // 與預設的最大堆搭配: pri大的先出來
}

// 作法二: 自訂「仿函式 (functor)」比較器，在模板參數中指定
struct CmpTaskMin{
    bool operator()(const Task& a, const Task& b) const{
        return a.pri > b.pri;  // a.pri較大 → a優先權較低 → pri小的先出來
    }
};

// 作法三: 一般函式 (function pointer)
bool cmpDist(int a, int b){
    return abs(a - 5) > abs(b - 5);  // 離5越近的優先權越高
}

int main(){
{
    // 《1. priority_queue的宣告》

    // 建立空的priority_queue (最大堆)，名稱為pq1
    priority_queue<int> pq1;

    // 注意: priority_queue「沒有」像vector那樣的 priority_queue<int> pq(5) 或 pq(5, 10) 的寫法 (會編譯錯誤)
    //       也「沒有」 priority_queue<int> pq = {1,2,3} 的初始化串列寫法 (會編譯錯誤)

    // 最小堆: 需指定三個模板參數 (型別、底層容器、比較器)
    priority_queue<int, vector<int>, greater<int>> pq2;

    // 用兩個iterator(迭代器)範圍建構 (時間複雜度 O(n))
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    priority_queue<int> pq3(v.begin(), v.end());
    Traversal_pq(pq3)  // 輸出: 9 6 5 4 3 2 1 1  (重複的元素會被保留，不會去重)

    // 最小堆也可以用iterator範圍建構
    priority_queue<int, vector<int>, greater<int>> pq4(v.begin(), v.end());
    Traversal_pq(pq4)  // 輸出: 1 1 2 3 4 5 6 9

    // 用一個已有的底層容器來建構: 第一個參數是比較器物件，第二個參數是容器 (會「複製」容器的內容並整理成堆積)
    priority_queue<int> pq5(less<int>(), v);
    Traversal_pq(pq5)  // 輸出: 9 6 5 4 3 2 1 1

    // 搬移建構: 把容器的資源「搬」進priority_queue，不做複製 (搬移後原容器處於「有效但未指定」的狀態，不建議再使用)
    vector<int> v2 = {7, 8, 9};
    priority_queue<int> pq6(less<int>(), move(v2));
    Traversal_pq(pq6)  // 輸出: 9 8 7

    // 複製建構，pq5與pq7會互相獨立
    priority_queue<int> pq7(pq5);
    pq7.push(100);
    cout<< pq5.top() << ' ' << pq7.top() <<endl;  // 輸出: 9 100

    // 指定底層容器為deque
    priority_queue<int, deque<int>> pq8;
    pq8.push(1);
    pq8.push(3);
    pq8.push(2);
    Traversal_pq(pq8)  // 輸出: 3 2 1

    // 注意: priority_queue<int, list<int>> 會編譯失敗，因為list不支援隨機存取

    // C++17的類別模板引數推導 (CTAD): 傳入「比較器+容器」時可省略模板參數
    priority_queue pq9(greater<int>(), v);  // 推導為 priority_queue<int, vector<int>, greater<int>>
    Traversal_pq(pq9)  // 輸出: 1 1 2 3 4 5 6 9

    // 常用的型別別名 (type alias)
    static_assert(is_same<priority_queue<int>::value_type, int>::value, "value_type為元素型別");
    static_assert(is_same<priority_queue<int>::container_type, vector<int>>::value, "container_type預設為vector");
    static_assert(is_same<priority_queue<int>::value_compare, less<int>>::value, "value_compare預設為less");
    priority_queue<int>::size_type n = pq3.size();  // size_type通常為 size_t (無號整數)
    cout<< n <<endl;  // 輸出: 8

    // 元素型別也可以是 string、pair 或其他自訂型別
    priority_queue<string> pqs;  // 字串依字典順序比較，字典順序最大的先出來
    pqs.push("banana");
    pqs.push("apple");
    pqs.push("cherry");
    cout<< pqs.top() <<endl;  // 輸出: cherry

    // pair的預設比較: 先比較first，first相同再比較second (與set筆記中的pair比較規則相同)
    priority_queue<pair<int,int>> pqp;
    pqp.push({1, 9});
    pqp.push({3, 2});
    pqp.push({3, 5});
    pqp.push({2, 7});
    cout<< pqp.top().first << ' ' << pqp.top().second <<endl;  // 輸出: 3 5  (first最大是3，其中second較大的是5)

    /*
    C++23 新增的建構方式 (需要GCC 14以上等較新的編譯器，這裡僅列出語法，不實際執行):
    priority_queue<int> pq(from_range, v);   // 以range建構 (需 <ranges>)
    pq.push_range(v);                        // 一次把整個range依序加入
    */
}
cout<<("====================================\n");// 分隔線
{
    // 《2. priority_queue的新增、存取與刪除》

    priority_queue<int> pq;

    // 1. 新增 (push與emplace)

    // pq.push(x) 新增元素，內部會自動調整堆積，時間複雜度 O(log n)
    // 新增的位置由優先權決定，不是固定在尾端或前端
    pq.push(3);
    pq.push(10);
    pq.push(5);
    pq.push(7);
    Traversal_pq(pq)  // 輸出: 10 7 5 3

    // pq.emplace(args...) 直接在容器內就地建構元素，可省去一次臨時物件的複製/搬移
    // 對基本型別來說，emplace與push沒有差別；差別主要出現在元素型別是 pair、string、自訂class 的時候
    // 注意: priority_queue::emplace() 回傳void (與queue::emplace()自C++17起回傳參考不同)
    pq.emplace(8);
    Traversal_pq(pq)  // 輸出: 10 8 7 5 3

    priority_queue<pair<int,string>> pqp;
    pqp.push({2, "Bob"});             // push: 需要先用{}建立臨時pair，再複製/搬移進priority_queue
    pqp.push(make_pair(5, "Alice"));  // 也可以用make_pair
    pqp.emplace(3, "Cathy");          // emplace: 直接把參數3, "Cathy"傳給pair的建構函式，不需要{}
    cout<< pqp.size() <<endl;  // 輸出: 3

    cout<<("======================\n");// 分隔線

    // 2. 存取 (top)
    // priority_queue只能存取「頂端」的元素 (優先權最高者)，沒有front()、back()、[i]、at(i)
    // 對「空的priority_queue」呼叫 top() 是未定義行為(Undefined Behavior)，
    // 不會丟出例外也不會有任何提示，因此呼叫前務必先檢查 empty()

    cout<< pq.top() <<endl;  // 輸出: 10
    cout<< pqp.top().second <<endl;  // 輸出: Alice  (first=5最大)

    // 注意: top() 回傳的是「const參考 (const T&)」，因此「不能」透過top()修改元素
    // pq.top() = 99;   // 編譯錯誤
    // 原因: 修改頂端元素的值會破壞堆積的結構。若要改變優先權，只能 pop() 後再 push() 新的值

    // 另一個陷阱: top() 回傳的是參考，pop() 之後該參考會失效，使用前請先複製
    int x = pq.top();  // 先複製出來
    pq.pop();
    cout<< x <<endl;  // 輸出: 10  (若寫成 const int& x = pq.top(); 再pop()，x會變成懸空參考，行為未定義)

    cout<<("======================\n");// 分隔線

    // 3. 刪除 (pop)
    // priority_queue只能刪除「頂端」的元素，不能刪除其他位置的元素，也「沒有」clear()與erase()
    // 注意: pop()的回傳型別是void，「不會」回傳被刪除的值！
    //       若想取得被刪除的值，必須先用top()讀出來，再pop()
    // 時間複雜度 O(log n)

    Traversal_pq(pq)  // 輸出: 8 7 5 3
    pq.pop();
    Traversal_pq(pq)  // 輸出: 7 5 3

    int y = pq.top();  // 先讀出頂端的值
    pq.pop();          // 再刪除
    cout<< y <<endl;  // 輸出: 7
    Traversal_pq(pq)  // 輸出: 5 3

    // 對空的priority_queue呼叫 pop() 同樣是未定義行為，務必先檢查 empty()

    // 清空priority_queue的方法 (priority_queue沒有clear())
    // 方法一: 重複pop()直到空
    {
        priority_queue<int> t = pq;
        while (!t.empty()) t.pop();
        cout<< t.size() <<endl;  // 輸出: 0
    }

    // 方法二: 指派一個新的空priority_queue (最簡潔，推薦)
    // 注意: 如果pq是使用greater或自訂比較器宣告的，要寫成 pq = decltype(pq)(); 以保持相同型別
    pq = priority_queue<int>();
    cout<< pq.size() <<endl;  // 輸出: 0

    // 方法三: 與一個空的priority_queue交換 (swap)
    pq.push(1);
    pq.push(2);
    priority_queue<int>().swap(pq);  // 臨時的空priority_queue與pq交換，臨時物件隨後被銷毀
    cout<< pq.empty() <<endl;  // 輸出: 1

    // 一邊取出一邊處理，是priority_queue最常見的使用模式
    for (int i : {20, 50, 10, 40}) pq.push(i);
    while (!pq.empty()){
        cout<< pq.top() << ' ';
        pq.pop();
    }
    cout<<endl;  // 輸出: 50 40 20 10  (這就是「堆積排序」的概念: 不斷取出最大值，得到由大到小的序列)
    cout<< pq.size() <<endl;  // 輸出: 0
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 自訂比較方式》
    // 預設為最大堆 (less)。若想改變優先順序，共有以下幾種方式

    // 方法一: 使用標準庫的 greater<T> 得到最小堆 (最常用，已於《1.》介紹)
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int i : {5, 1, 4, 2}) minHeap.push(i);
    cout<< minHeap.top() <<endl;  // 輸出: 1
    Traversal_pq(minHeap)  // 輸出: 1 2 4 5

    // 方法二: 取負號的技巧 (只適用於數值型別，用最大堆模擬最小堆)
    // 放進去時乘上-1，取出時再乘上-1
    priority_queue<int> neg;
    for (int i : {5, 1, 4, 2}) neg.push(-i);
    cout<< -neg.top() <<endl;  // 輸出: 1  (最小的數取負號後最大，因此先出來)

    cout<<("======================\n");// 分隔線

    // 方法三: 自訂型別重載 operator< (搭配預設的less使用)
    priority_queue<Task> pqTask;
    pqTask.push({3, "write report"});
    pqTask.push({9, "fix bug"});
    pqTask.push({5, "review code"});
    while (!pqTask.empty()){
        cout<< pqTask.top().pri << ':' << pqTask.top().name << ' ';
        pqTask.pop();
    }
    cout<<endl;  // 輸出: 9:fix bug 5:review code 3:write report

    // 方法四: 自訂仿函式 (functor) 比較器，放在第三個模板參數
    priority_queue<Task, vector<Task>, CmpTaskMin> pqMin;
    pqMin.push({3, "write report"});
    pqMin.push({9, "fix bug"});
    pqMin.push({5, "review code"});
    while (!pqMin.empty()){
        cout<< pqMin.top().pri << ':' << pqMin.top().name << ' ';
        pqMin.pop();
    }
    cout<<endl;  // 輸出: 3:write report 5:review code 9:fix bug

    // 方法五: 使用Lambda表達式
    // 因為Lambda沒有名稱，模板參數需要用 decltype() 取得型別，且建構時必須把Lambda物件傳入
    auto cmp = [](int a, int b){ return a > b; };  // 與greater<int>相同，小的先出來
    priority_queue<int, vector<int>, decltype(cmp)> pqLambda(cmp);
    for (int i : {5, 1, 4, 2}) pqLambda.push(i);
    Traversal_pq(pqLambda)  // 輸出: 1 2 4 5

    // 方法六: 使用一般函式 (function pointer)，同樣須在建構時傳入函式
    priority_queue<int, vector<int>, bool(*)(int,int)> pqFunc(cmpDist);
    for (int i : {1, 8, 4, 5, 12}) pqFunc.push(i);
    Traversal_pq(pqFunc)  // 輸出: 5 4 8 1 12  (離5的距離分別為0 1 3 4 7)
    // 注意: 若有兩個元素的優先權相同(例如距離5同樣為1的4與6)，priority_queue「不保證」它們的輸出順序
    //       (順序依實作而定，並非穩定排序，因此上面刻意挑選沒有平手的資料)
    //       若需要固定順序，比較器應該加入第二個判斷條件，見下方

    // 比較器加入「平手時的判斷條件」，讓輸出順序固定: 距離相同時，數值小的先出來
    auto cmp2 = [](int a, int b){
        int da = abs(a - 5), db = abs(b - 5);
        if (da != db) return da > db;  // 距離大的優先權低
        return a > b;                  // 距離相同時，數值大的優先權低 (小的先出來)
    };
    priority_queue<int, vector<int>, decltype(cmp2)> pqLambda2(cmp2);
    for (int i : {1, 9, 4, 6, 5}) pqLambda2.push(i);
    Traversal_pq(pqLambda2)  // 輸出: 5 4 6 1 9  (距離0:5，距離1:4,6，距離4:1,9)

    cout<<("======================\n");// 分隔線

    // 比較器的規則: 必須滿足「嚴格弱序 (strict weak ordering)」
    // 也就是說，comp(a, a) 必須為 false。因此比較器要用 < 或 >，「不可以」用 <= 或 >=
    // 若寫成 return a >= b; 在元素相同時行為未定義，可能導致當機或無窮迴圈
}
cout<<("====================================\n");// 分隔線
{
    // 《4. 遍歷》
    // priority_queue「沒有」迭代器(begin()/end())，因此無法使用:
    //   for (int x : pq)                   (range-based for會編譯錯誤)
    //   for (auto it = pq.begin(); ...)    (沒有begin())
    //   for (int i=0; i<pq.size(); i++) pq[i] (沒有operator[])
    // 只能透過「top() + pop()」逐一取出，而這個過程會「破壞」priority_queue
    // 取出的順序即為「優先權由高到低」

    priority_queue<int> pq;
    for (int i : {4, 7, 1, 9}) pq.push(i);

    // 方法一: 複製一份後，對複製品逐一取出 (複製品會被清空，原本的pq不受影響)
    {
        priority_queue<int> t = pq;
        while (!t.empty()){
            cout<< t.top() << ' ';
            t.pop();
        }
        cout<<endl;  // 輸出: 9 7 4 1
    }
    cout<< pq.size() <<endl;  // 輸出: 4 (原本的pq不受影響)

    // 方法二: 取出到vector中 (取出後pq會被清空；若要保留，可再放回去)
    vector<int> out;
    while (!pq.empty()){
        out.push_back(pq.top());
        pq.pop();
    }
    for (int i : out) cout<< i << ' ';
    cout<<endl;  // 輸出: 9 7 4 1
    for (int i : out) pq.push(i);  // 放回去，恢復原本內容
    cout<< pq.size() <<endl;  // 輸出: 4

    // 注意: priority_queue「內部」的儲存順序是堆積(heap)順序，並不是排序後的順序，
    //       且沒有任何公開的方式可以查看，因此不要假設任何內部順序

    // 若真的需要經常遍歷、修改任意元素或隨機存取，代表priority_queue不適合，
    // 應改用 set / multiset (自動排序、有迭代器、可刪除任意元素)
}
cout<<("====================================\n");// 分隔線
{
    //《5. 常用函式》

    priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(2);

    // 1. 判斷priority_queue是否為空
    cout<< pq.empty() <<endl;  // 輸出: 0 (表示非空)
    priority_queue<int> e;
    cout<< e.empty() <<endl;  // 輸出: 1 (表示是空的)

    // 2. 取得priority_queue的大小(元素個數)
    cout<< pq.size() <<endl;  // 輸出: 3
    cout<< e.size() <<endl;  // 輸出: 0
    // 注意: priority_queue「沒有」capacity()、reserve()、max_size()、resize()

    // 3. 交換兩個priority_queue的內容 (時間複雜度 O(1))
    // 兩者的型別(含比較器)必須完全相同
    priority_queue<int> a, b;
    for (int i : {1, 2, 3}) a.push(i);
    for (int i : {7, 8, 9}) b.push(i);
    a.swap(b);
    cout<<"a: "; Traversal_pq(a)  // 輸出: a: 9 8 7
    cout<<"b: "; Traversal_pq(b)  // 輸出: b: 3 2 1

    swap(a, b);  // 也可以使用 std::swap (非成員函式版本，效果相同)
    cout<<"a: "; Traversal_pq(a)  // 輸出: a: 3 2 1
    cout<<"b: "; Traversal_pq(b)  // 輸出: b: 9 8 7

    // 4. 指派 (assignment)：複製整個priority_queue，兩者互相獨立
    priority_queue<int> c;
    c = a;
    c.push(100);
    cout<<"a: "; Traversal_pq(a)  // 輸出: a: 3 2 1
    cout<<"c: "; Traversal_pq(c)  // 輸出: c: 100 3 2 1
    // 注意: 不能寫 c = {1,2,3}; (priority_queue沒有接受初始化串列的指派運算子)

    cout<<("======================\n");// 分隔線

    // 5. 比較運算子
    // 注意: priority_queue「沒有」提供 ==、!=、<、> 等比較運算子 (與queue不同)！
    //       因為堆積的內部順序不唯一，內容相同的兩個priority_queue，內部排列可能不同，直接比較沒有意義
    //       若要判斷內容是否相同，須各自取出到vector後再比較

    // 6. 與 <algorithm> 的搭配
    //    因為priority_queue沒有迭代器，所以 sort()、find()、count()、accumulate() 等
    //    需要迭代器範圍的函式「全部無法」直接用在priority_queue上
    //    若需要，必須先把元素取出到vector，處理完再放回priority_queue

    // 7. 查詢priority_queue中是否存在某值: 沒有find()，只能自行逐一取出檢查 (時間複雜度 O(n log n))
    priority_queue<int> data;
    for (int i : {5, 3, 8, 1}) data.push(i);
    int target = 3;
    bool found = false;
    {
        priority_queue<int> t = data;  // 複製一份，避免破壞原本的data
        while (!t.empty()){
            if (t.top() == target){ found = true; break; }
            t.pop();
        }
    }
    cout<< found <<endl;  // 輸出: 1

    // 8. 「修改某個元素的優先權」或「刪除任意元素」: priority_queue「沒有」提供這類功能
    //    常用的替代做法是「延遲刪除 (lazy deletion)」，見《6. 應用範例》的Dijkstra
}
cout<<("====================================\n");// 分隔線
{
    // 《6. 堆積演算法 (<algorithm>)》
    // priority_queue內部就是靠這些函式實作的。若需要「可遍歷、可隨機存取」的堆積，
    // 可以直接對vector使用這些函式 (預設為最大堆，比較器的意義與priority_queue相同)
    //   make_heap(first, last [, comp])  : 把一段範圍整理成堆積，O(n)
    //   push_heap(first, last [, comp])  : 範圍[first, last-1)已是堆積，把最後一個元素加入堆積，O(log n)
    //   pop_heap(first, last [, comp])   : 把最大值(堆頂)移到範圍的「最後面」，其餘[first, last-1)仍維持堆積，O(log n)
    //   sort_heap(first, last [, comp])  : 把堆積排序成「由小到大」的序列(使用預設比較器時)，O(n log n)
    //   is_heap(first, last [, comp])    : 判斷範圍是否為堆積
    //   is_heap_until(first, last [, comp]): 回傳第一個不滿足堆積條件的位置

    vector<int> h = {3, 1, 4, 1, 5, 9, 2, 6};
    cout<< is_heap(h.begin(), h.end()) <<endl;  // 輸出: 0 (原本的順序不是堆積)

    make_heap(h.begin(), h.end());
    cout<< is_heap(h.begin(), h.end()) <<endl;  // 輸出: 1
    cout<< h.front() <<endl;  // 輸出: 9 (堆頂為最大值，相當於priority_queue的top())

    h.push_back(10);                 // 先放到vector尾端
    push_heap(h.begin(), h.end());   // 再調整成堆積 (相當於priority_queue的push())
    cout<< h.front() <<endl;  // 輸出: 10

    pop_heap(h.begin(), h.end());    // 把最大值10移到最後面 (相當於pop()的前半部)
    cout<< h.back() <<endl;   // 輸出: 10
    h.pop_back();                    // 再真正刪除 (相當於pop()的後半部)
    cout<< h.front() <<endl;  // 輸出: 9

    sort_heap(h.begin(), h.end());   // 排序成由小到大
    for (int i : h) cout<< i << ' ';
    cout<<endl;  // 輸出: 1 1 2 3 4 5 6 9

    // 最小堆: 傳入greater<int>() (所有堆積函式都要傳入同一個比較器)
    vector<int> h2 = {3, 1, 4, 1, 5};
    make_heap(h2.begin(), h2.end(), greater<int>());
    cout<< h2.front() <<endl;  // 輸出: 1
    cout<< is_heap(h2.begin(), h2.end(), greater<int>()) <<endl;  // 輸出: 1
    sort_heap(h2.begin(), h2.end(), greater<int>());  // 使用greater時，sort_heap得到「由大到小」
    for (int i : h2) cout<< i << ' ';
    cout<<endl;  // 輸出: 5 4 3 1 1
}
cout<<("====================================\n");// 分隔線
{
    // 《7. 應用範例》

    // 1. Dijkstra最短路徑 (最小堆 + pair)
    //    無向圖: 0-1(4)、0-2(1)、2-1(2)、1-3(1)、2-3(5)、3-4(3)，括號內為邊的權重
    //    pair<距離, 節點>，用greater做最小堆，pair會先比較距離
    vector<vector<pair<int,int>>> adj(5);  // adj[u] = {(v, w), ...}
    auto addEdge = [&](int u, int v, int w){
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };
    addEdge(0, 1, 4);
    addEdge(0, 2, 1);
    addEdge(2, 1, 2);
    addEdge(1, 3, 1);
    addEdge(2, 3, 5);
    addEdge(3, 4, 3);

    vector<int> dist(5, 1000000000);  // 1e9代表無限大
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()){
        pair<int,int> cur = pq.top();
        pq.pop();
        int d = cur.first, u = cur.second;
        if (d > dist[u]) continue;  // 延遲刪除 (lazy deletion): 這筆是過時的紀錄，直接跳過
        // 因為priority_queue無法修改或刪除已經放進去的元素，
        // 當發現更短的路徑時，只能再push一筆新的紀錄，等舊紀錄被取出時再判斷並丟棄
        for (pair<int,int> e : adj[u]){
            int v = e.first, w = e.second;
            if (dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    for (int d : dist) cout<< d << ' ';
    cout<<endl;  // 輸出: 0 3 1 4 7

    // 2. 找出第K大的元素 (大小為K的最小堆)
    //    堆中始終保留「目前最大的K個數」，堆頂就是這K個數中最小的，也就是第K大
    //    時間複雜度 O(n log K)，比排序的 O(n log n) 更好，且適合資料量很大或資料持續進來的情況
    {
        vector<int> nums = {5, 1, 8, 3, 9, 2};
        int K = 3;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int x : nums){
            minHeap.push(x);
            if ((int)minHeap.size() > K) minHeap.pop();  // 超過K個就丟掉最小的
        }
        cout<< minHeap.top() <<endl;  // 輸出: 5 (最大的三個數是9,8,5，第3大為5)
        Traversal_pq(minHeap)  // 輸出: 5 8 9
    }

    // 3. 資料串流的中位數 (兩個堆: 最大堆存較小的一半，最小堆存較大的一半)
    {
        priority_queue<int> lo;                                  // 較小的一半，堆頂是這一半的最大值
        priority_queue<int, vector<int>, greater<int>> hi;       // 較大的一半，堆頂是這一半的最小值
        for (int x : {5, 15, 1, 3}){
            lo.push(x);
            hi.push(lo.top());  // 把lo的最大值移到hi，確保lo的所有元素 <= hi的所有元素
            lo.pop();
            if (hi.size() > lo.size()){  // 維持 lo.size() == hi.size() 或 lo.size() == hi.size()+1
                lo.push(hi.top());
                hi.pop();
            }
            double median = (lo.size() > hi.size()) ? lo.top() : (lo.top() + hi.top()) / 2.0;
            cout<< median << ' ';
        }
        cout<<endl;  // 輸出: 5 10 5 4
    }

    // 4. 堆積排序的概念: 全部push進最大堆，再依序取出，就得到由大到小的序列 (見《2.》)
}
}


/*
補充一: priority_queue 與 queue 的差異 (兩者同樣定義在<queue>標頭檔)

queue          : 先進先出，依「進入順序」取出；用 front()/back() 存取；有 ==、< 等比較運算子；
                 底層預設為deque；所有操作皆為 O(1)
priority_queue : 依「優先順序」取出；只能用 top() 存取，沒有front()和back()；沒有比較運算子；
                 底層預設為vector；push/pop 為 O(log n)

補充二: priority_queue 與 set / multiset 的差異

priority_queue : 只能存取、刪除「最優先」的一個元素，不能搜尋或刪除任意元素，沒有迭代器；
                 push/pop 為 O(log n)，top 為 O(1)，常數小、記憶體連續，速度通常較快
set / multiset : 完全排序，有迭代器，可以搜尋 (find) 與刪除任意元素 (erase)，
                 同時取最大與最小元素都很方便 (rbegin() 與 begin())；所有操作為 O(log n)
若只需要不斷取出最大或最小值，用priority_queue；若需要刪除或修改任意元素，用multiset

補充三: 建構堆積的時間複雜度

用n個元素「一個一個push」進去: O(n log n)
用兩個iterator範圍或底層容器一次建構: O(n) (內部使用make_heap)
因此若資料一開始就全部已知，建議使用範圍建構

補充四: 為什麼 pop() 不回傳被刪除的值？

為了「例外安全性 (exception safety)」: 若pop()要回傳值，必須先複製出元素再刪除；
若複製的過程拋出例外，元素已被刪除卻沒拿到值，資料就遺失了。
因此標準庫把「讀取(top)」與「刪除(pop)」分成兩個動作，讓使用者自行控制
*/


// 參考 cppreference std::priority_queue (https://en.cppreference.com/w/cpp/container/priority_queue)
// Generated by Claude 2026/10/2
