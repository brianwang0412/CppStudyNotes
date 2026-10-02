#include<queue>  // 需引入<queue>標頭檔 (priority_queue也定義在這個標頭檔中)

#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<utility>      // pair、move、swap
#include<type_traits>  // is_same，用於檢查型別別名
using namespace std;

// 我使用Traversal_q(q)來表示「遍歷」queue q的輸出結果
// 注意: queue沒有迭代器，無法直接遍歷，只能複製一份後，不斷輸出front()再pop()，這樣才不會破壞原本的queue
#define Traversal_q(q) { auto tmp=q; while(!tmp.empty()){cout<<tmp.front()<<' ';tmp.pop();} cout<<endl; }

/*
前言: queue的特性

1. queue(佇列)是一種「先進先出 (FIFO, First In First Out)」的資料結構，像排隊買票一樣:
   最先排隊的人最先離開，新來的人只能排在隊伍的「尾端」
2. queue本身並不是獨立的容器，而是「容器配接器 (container adapter)」，
   它只是把另一個容器（預設是deque）包裝起來，只開放「尾端加入、前端取出」的介面
   因此queue「沒有」: 迭代器(begin()/end())、operator[]、at()、clear()、insert()、erase()、resize()
   也「不能」遍歷、不能查看中間的元素，只能存取最前面(front)與最後面(back)的元素
3. 所有成員函式的時間複雜度皆為 O(1)  (push、pop、front、back、size、empty、swap…)
   其中 swap 是 O(1) 是因為底層容器的 swap 是 O(1)
4. 底層容器必須同時支援 front()、back()、push_back()、pop_front()
   符合條件的標準容器只有 deque (預設) 與 list；vector「不行」(因為vector沒有pop_front())
5. queue可以搭配 deque 與 stack 的觀念對照:
   stack : 後進先出 (LIFO)，只能操作「同一端」(top)
   queue : 先進先出 (FIFO)，加入在back，取出在front，「兩端」各管一件事
   deque : 雙端佇列，兩端都能加入與取出，還可用[i]隨機存取，功能比queue多很多
*/

int main(){
{
    // 《1. queue的宣告》

    // 建立空的queue，可以用於儲存整數(int)，名稱為q1
    queue<int> q1;

    // 注意: queue「沒有」像vector那樣的 queue<int> q(5) 或 queue<int> q(5, 10) 的寫法 (會編譯錯誤)
    //       也「沒有」 queue<int> q = {1,2,3} 的初始化串列寫法 (會編譯錯誤)
    //       因為queue只有「以容器建構」與「複製/搬移建構」兩類建構方式

    // 用一個已有的deque來建構 (會「複製」deque的內容，元素順序: 最左邊 = front，最右邊 = back)
    deque<int> dq = {1, 2, 3};
    queue<int> q2(dq);
    Traversal_q(q2)  // 輸出: 1 2 3
    cout<< q2.front() << ' ' << q2.back() <<endl;  // 輸出: 1 3  (front是1，back是3)

    // 複製建構，q2與q3會互相獨立
    queue<int> q3(q2);
    q3.push(4);
    Traversal_q(q2)  // 輸出: 1 2 3
    Traversal_q(q3)  // 輸出: 1 2 3 4

    // 搬移建構: 把dq的資源「搬」進queue，不做複製 (搬移後dq處於「有效但未指定」的狀態，不建議再使用)
    deque<int> dq2 = {7, 8, 9};
    queue<int> q4(move(dq2));
    Traversal_q(q4)  // 輸出: 7 8 9

    // 若資料原本在vector中，無法直接建構queue，須先轉成deque
    vector<int> v = {5, 6, 7};
    queue<int> q5( deque<int>(v.begin(), v.end()) );  // 用兩個iterator範圍建立臨時deque，再交給queue
    Traversal_q(q5)  // 輸出: 5 6 7

    // 指定底層容器: queue<型別, 容器型別>，第二個模板參數預設是 deque<型別>
    queue<int, list<int>> q6;  // 底層改用list
    q6.push(10);
    q6.push(20);
    Traversal_q(q6)  // 輸出: 10 20

    list<int> lst = {100, 200, 300};
    queue<int, list<int>> q7(lst);  // 用list建構 (容器型別必須與第二個模板參數相同)
    Traversal_q(q7)  // 輸出: 100 200 300

    // 注意: queue<int, vector<int>> 會編譯失敗，因為vector沒有pop_front()

    // C++17的類別模板引數推導 (CTAD): 可以省略 <int, deque<int>>，由傳入的容器自動推導
    queue q8(dq);  // 等同於 queue<int, deque<int>> q8(dq);
    Traversal_q(q8)  // 輸出: 1 2 3

    // 常用的型別別名 (type alias)
    static_assert(is_same<queue<int>::value_type, int>::value, "value_type為元素型別");
    static_assert(is_same<queue<int>::container_type, deque<int>>::value, "container_type預設為deque");
    queue<int>::size_type n = q2.size();  // size_type通常為 size_t (無號整數)
    cout<< n <<endl;  // 輸出: 3

    // 元素型別也可以是 string、pair 或其他自訂型別
    queue<string> qs;
    qs.push("apple");
    qs.push("banana");
    cout<< qs.front() <<endl;  // 輸出: apple

    queue<pair<int,int>> qp;
    qp.push({1, 2});
    qp.push({3, 4});
    cout<< qp.front().first << ' ' << qp.front().second <<endl;  // 輸出: 1 2

    // 二維queue: queue中的元素也是queue
    queue<queue<int>> qq;
    queue<int> row1, row2;
    row1.push(1); row1.push(2);
    row2.push(3);
    qq.push(row1);
    qq.push(row2);
    cout<< qq.size() << ' ' << qq.front().size() << ' ' << qq.back().size() <<endl;  // 輸出: 2 2 1

    /*
    C++23 新增的建構方式 (需要GCC 14以上等較新的編譯器，這裡僅列出語法，不實際執行):
    queue<int> q(v.begin(), v.end());           // 直接以iterator範圍建構
    queue<int> q(from_range, v);                // 以range建構 (需 <ranges>)
    q.push_range(v);                            // 一次把整個range依序加入
    */
}
cout<<("====================================\n");// 分隔線
{
    // 《2. queue的新增》

    queue<int> q;

    // q.push(x) 在queue的「尾端(back)」新增元素 (沒有push_front，也不能從中間插入)
    q.push(1);
    q.push(2);
    q.push(3);
    Traversal_q(q)  // 輸出: 1 2 3
    // 隊伍示意:  front → [1][2][3] ← back   (新元素從back進入)

    // q.emplace(args...) 直接在queue尾端「就地建構」元素，可省去一次臨時物件的複製/搬移
    // 對基本型別來說，emplace與push沒有差別；差別主要出現在元素型別是 pair、string、自訂class 的時候
    q.emplace(4);
    Traversal_q(q)  // 輸出: 1 2 3 4

    queue<pair<int,string>> qp;
    qp.push({1, "Alice"});         // push: 需要先用{}建立臨時pair，再複製/搬移進queue
    qp.push(make_pair(2, "Bob"));  // 也可以用make_pair
    qp.emplace(3, "Cathy");        // emplace: 直接把參數3, "Cathy"傳給pair的建構函式，不需要{}
    cout<< qp.size() <<endl;  // 輸出: 3
    cout<< qp.back().first << ' ' << qp.back().second <<endl;  // 輸出: 3 Cathy

    // 注意: 自 C++17 起 emplace() 回傳「指向新元素的參考」(也就是 back())，C++11/14 則回傳void
    int& ref = q.emplace(5);
    ref = 50;  // 透過回傳的參考直接修改剛加入的元素
    Traversal_q(q)  // 輸出: 1 2 3 4 50

    // 在queue中新增「二維」的元素
    queue<queue<int>> qq;
    qq.push(queue<int>());  // 加入一個空的queue
    qq.back().push(1);      // 對最後一個內層queue加入元素
    qq.back().push(2);
    qq.push(queue<int>());
    qq.back().push(3);
    cout<< qq.front().front() << ' ' << qq.back().front() <<endl;  // 輸出: 1 3
}
cout<<("====================================\n");// 分隔線
{
    // 《3. queue的存取》
    // 注意: queue只能存取「最前面 front」與「最後面 back」兩個元素，沒有 [i] 與 at(i)
    //       對「空的queue」呼叫 front() 或 back() 是未定義行為(Undefined Behavior)，
    //       不會丟出例外也不會有任何提示，可能直接當機或得到垃圾值，因此呼叫前務必先檢查 empty()

    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    // q.front() 取得最前面(最早進入)的元素
    cout<< q.front() <<endl;  // 輸出: 10

    // q.back() 取得最後面(最晚進入)的元素
    cout<< q.back() <<endl;  // 輸出: 30

    // front()與back()回傳的是「參考」，因此可以直接修改元素值
    q.front() = 99;
    q.back() += 1;
    Traversal_q(q)  // 輸出: 99 20 31

    // 只有一個元素時，front()與back()是同一個元素
    queue<int> one;
    one.push(5);
    one.front() = 6;
    cout<< one.back() <<endl;  // 輸出: 6

    // 安全的存取寫法: 先檢查是否為空
    queue<int> empty_q;
    if (!empty_q.empty()){
        cout<< empty_q.front() <<endl;
    }
    else{
        cout<<"queue is empty"<<endl;  // 輸出: queue is empty
    }

    // 對const queue而言，front()與back()回傳的是const參考，無法修改
    const queue<int> cq = q;
    cout<< cq.front() <<endl;  // 輸出: 99
}
cout<<("====================================\n");// 分隔線
{
    // 《4. queue的刪除》
    // 注意: queue只能刪除「最前面 front」的元素，不能刪除尾端或中間的元素
    //       也「沒有」clear()與erase()

    queue<int> q;
    for (int i=1; i<=5; i++) q.push(i);
    Traversal_q(q)  // 輸出: 1 2 3 4 5

    // q.pop() 刪除最前面的元素
    // 注意: pop()的回傳型別是void，「不會」回傳被刪除的值！
    //       若想取得被刪除的值，必須先用front()讀出來，再pop()
    q.pop();
    Traversal_q(q)  // 輸出: 2 3 4 5

    int x = q.front();  // 先讀出最前面的值
    q.pop();            // 再刪除
    cout<< x <<endl;  // 輸出: 2
    Traversal_q(q)  // 輸出: 3 4 5

    // 對空的queue呼叫 pop() 同樣是未定義行為，務必先檢查 empty()

    // 清空queue的方法 (queue沒有clear())
    // 方法一: 重複pop()直到空
    {
        queue<int> t = q;
        while (!t.empty()) t.pop();
        cout<< t.size() <<endl;  // 輸出: 0
    }

    // 方法二: 指派一個新的空queue (最簡潔，推薦)
    q = queue<int>();
    cout<< q.size() <<endl;  // 輸出: 0

    // 方法三: 與一個空的queue交換 (swap)
    q.push(1);
    q.push(2);
    queue<int>().swap(q);  // 臨時的空queue與q交換，臨時物件隨後被銷毀
    cout<< q.empty() <<endl;  // 輸出: 1

    // 一邊取出一邊處理，是queue最常見的使用模式
    for (int i=1; i<=3; i++) q.push(i*10);
    while (!q.empty()){
        cout<< q.front() << ' ';
        q.pop();
    }
    cout<<endl;  // 輸出: 10 20 30
    cout<< q.size() <<endl;  // 輸出: 0 (全部被取出後queue變空)
}
cout<<("====================================\n");// 分隔線
{
    // 《5. 遍歷》
    // queue「沒有」迭代器(begin()/end())，因此無法使用:
    //   for (int x : q)                    (range-based for會編譯錯誤)
    //   for (auto it = q.begin(); ...)     (沒有begin())
    //   for (int i=0; i<q.size(); i++) q[i] (沒有operator[])
    // 只能透過「front() + pop()」逐一取出，而這個過程會「破壞」queue

    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    // 方法一: 複製一份後，對複製品逐一取出 (複製品會被清空，原本的q不受影響)
    {
        queue<int> t = q;  // 先複製一份，避免破壞原本的q
        while (!t.empty()){
            cout<< t.front() << ' ';
            t.pop();
        }
        cout<<endl;  // 輸出: 1 2 3
    }
    cout<< q.size() <<endl;  // 輸出: 3 (原本的q不受影響)

    // 方法二: 利用 size() 固定迴圈次數，「取出後再放回尾端」，遍歷一輪後順序保持不變
    // 這種寫法不需要額外複製queue，空間複雜度為O(1)，常用於「逐一處理每個元素」的題目
    int sz = q.size();  // 先把size()存起來，確保只處理「原本的」元素個數(迴圈中pop與push成對出現，若寫成while(!q.empty())會無限迴圈)
    for (int i=0; i<sz; i++){
        int cur = q.front();
        q.pop();
        cout<< cur << ' ';
        q.push(cur);  // 放回尾端
    }
    cout<<endl;  // 輸出: 1 2 3
    Traversal_q(q)  // 輸出: 1 2 3 (順序與遍歷前完全相同)

    // 方法三: 利用 BFS 的「分層處理」寫法: 每一輪只處理「當下這一層」的元素個數
    //        (常用於樹的層序走訪、最短路徑層數計算，見《7. 應用》)

    // 若真的需要經常遍歷或隨機存取，代表queue不適合，應改用deque（它同時具備queue的功能與迭代器、[]）
}
cout<<("====================================\n");// 分隔線
{
    //《6. 常用函式》

    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    // 1. 判斷queue是否為空
    cout<< q.empty() <<endl;  // 輸出: 0 (表示非空)
    queue<int> e;
    cout<< e.empty() <<endl;  // 輸出: 1 (表示是空的)

    // 2. 取得queue的大小(元素個數)
    cout<< q.size() <<endl;  // 輸出: 3
    cout<< e.size() <<endl;  // 輸出: 0
    // 注意: queue「沒有」capacity()、reserve()、max_size()、resize()

    // 3. 交換兩個queue的內容 (時間複雜度 O(1))
    queue<int> a, b;
    a.push(1); a.push(2); a.push(3);
    b.push(7); b.push(8); b.push(9);
    a.swap(b);
    cout<<"a: "; Traversal_q(a)  // 輸出: a: 7 8 9
    cout<<"b: "; Traversal_q(b)  // 輸出: b: 1 2 3

    swap(a, b);  // 也可以使用 std::swap (非成員函式版本，效果相同)
    cout<<"a: "; Traversal_q(a)  // 輸出: a: 1 2 3
    cout<<"b: "; Traversal_q(b)  // 輸出: b: 7 8 9

    // 4. 指派 (assignment)：複製整個queue，兩者互相獨立
    queue<int> c;
    c = a;
    c.push(4);
    cout<<"a: "; Traversal_q(a)  // 輸出: a: 1 2 3
    cout<<"c: "; Traversal_q(c)  // 輸出: c: 1 2 3 4
    // 注意: 不能寫 c = {1,2,3}; (queue沒有接受初始化串列的指派運算子)

    cout<<("======================\n");// 分隔線

    // 5. 比較運算子: ==  !=  <  <=  >  >=
    //    比較規則與「底層容器」相同: 逐一比較元素(由front到back)，採「字典順序」
    //    兩個queue必須「型別相同」(元素型別與底層容器都相同)才能比較
    //    (C++20起另外支援三向比較運算子 <=>，這裡不展開)
    queue<int> x, y;
    x.push(1); x.push(2);
    y.push(1); y.push(3);
    cout<< (x == y) <<endl;  // 輸出: 0 (第二個元素2≠3)
    cout<< (x != y) <<endl;  // 輸出: 1
    cout<< (x <  y) <<endl;  // 輸出: 1 (第一個元素相同，第二個元素 2 < 3)
    cout<< (x <= y) <<endl;  // 輸出: 1
    cout<< (x >  y) <<endl;  // 輸出: 0
    cout<< (x >= y) <<endl;  // 輸出: 0

    queue<int> z = x;
    cout<< (x == z) <<endl;  // 輸出: 1 (內容完全相同)

    queue<int> longer = x;
    longer.push(0);  // longer = {1,2,0}
    cout<< (x < longer) <<endl;  // 輸出: 1 (x是longer的前綴，較短者較小)

    cout<<("======================\n");// 分隔線

    // 6. 容器配接器的特色: 取得底層容器？
    //    queue「沒有」提供取得底層容器的公開函式，底層容器c是protected成員
    //    這是刻意的設計，目的是禁止使用者繞過queue的介面直接操作中間的元素

    // 7. 與 <algorithm> 的搭配
    //    因為queue沒有迭代器，所以 sort()、find()、reverse()、count()、accumulate() 等
    //    需要迭代器範圍的函式「全部無法」直接用在queue上
    //    若需要，必須先把元素取出到vector/deque，處理完再放回queue
    queue<int> data;
    for (int i : {5, 3, 8, 1}) data.push(i);

    vector<int> tmp;
    while (!data.empty()){  // 取出到vector
        tmp.push_back(data.front());
        data.pop();
    }
    // 此時即可對tmp使用 sort、find、accumulate 等函式 (需引入<algorithm>、<numeric>)
    for (int i : tmp) data.push(i);  // 放回queue
    Traversal_q(data)  // 輸出: 5 3 8 1

    // 8. 查詢queue中是否存在某值: queue沒有find()，只能自行逐一取出檢查 (時間複雜度 O(n))
    int target = 8;
    bool found = false;
    int sz = data.size();
    for (int i=0; i<sz; i++){
        int cur = data.front();
        data.pop();
        if (cur == target) found = true;
        data.push(cur);
    }
    cout<< found <<endl;  // 輸出: 1
}
cout<<("====================================\n");// 分隔線
{
    // 《7. 應用範例》

    // 1. BFS (廣度優先搜尋): 以圖的最短路徑(邊權皆為1)為例
    //    圖: 0-1, 0-2, 1-3, 2-3, 3-4
    vector<vector<int>> adj = {
        {1, 2},     // 0的鄰居
        {0, 3},     // 1的鄰居
        {0, 3},     // 2的鄰居
        {1, 2, 4},  // 3的鄰居
        {3}         // 4的鄰居
    };
    vector<int> dist(5, -1);  // dist[i] = 起點到i的最短距離，-1表示尚未走訪
    queue<int> bfs;
    bfs.push(0);
    dist[0] = 0;
    while (!bfs.empty()){
        int cur = bfs.front();
        bfs.pop();
        cout<< cur << ' ';  // 輸出走訪順序
        for (int nxt : adj[cur]){
            if (dist[nxt] == -1){
                dist[nxt] = dist[cur] + 1;
                bfs.push(nxt);
            }
        }
    }
    cout<<endl;  // 輸出: 0 1 2 3 4
    for (int d : dist) cout<< d <<' ';
    cout<<endl;  // 輸出: 0 1 1 2 3

    // 2. 分層處理 (每次處理「當下這一層」的所有節點)，計算BFS總共有幾層
    {
        vector<int> vis(5, 0);
        queue<int> q;
        q.push(0);
        vis[0] = 1;
        int level = 0;
        while (!q.empty()){
            int sz = q.size();  // 這一層的節點個數
            cout<<"Level "<< level <<": ";
            for (int i=0; i<sz; i++){
                int cur = q.front();
                q.pop();
                cout<< cur << ' ';
                for (int nxt : adj[cur]){
                    if (!vis[nxt]){
                        vis[nxt] = 1;
                        q.push(nxt);
                    }
                }
            }
            cout<<endl;
            level++;
        }
        /*
        輸出:
        Level 0: 0
        Level 1: 1 2
        Level 2: 3
        Level 3: 4
        */
    }

    // 3. 用queue模擬「報數出列」(約瑟夫問題): 5人圍成一圈，每次數到2的人出列
    {
        queue<int> q;
        for (int i=1; i<=5; i++) q.push(i);
        while (q.size() > 1){
            q.push(q.front());  // 第1個人報1，排到隊尾
            q.pop();
            cout<< q.front() << ' ';  // 第2個人報2，出列
            q.pop();
        }
        cout<<endl;  // 輸出: 2 4 1 5
        cout<< q.front() <<endl;  // 輸出: 3 (最後留下的人)
    }
}
}


/*
補充一: queue 與 deque 的差異

queue : 容器配接器，只開放 push / emplace / pop / front / back / size / empty / swap，無迭代器，無法隨機存取
deque : 真正的序列容器，兩端皆可 push/pop，支援 [i]、at(i)、迭代器、insert、erase、clear
若只需要「先進先出」的語意，用queue可以讓程式碼意圖更清楚，也避免誤用到中間的元素；
若需要遍歷或隨機存取，改用deque

補充二: queue 與 priority_queue 的差異 (priority_queue同樣定義在<queue>標頭檔)

queue          : 先進先出，依「進入順序」取出
priority_queue : 依「優先順序」取出 (預設最大值最先出來)，底層為heap(預設用vector)，
                 push/pop為 O(log n)，取出最大(或最小)元素的函式是 top() 而不是 front()，也沒有back()
                 宣告最小堆: priority_queue<int, vector<int>, greater<int>> pq;

補充三: queue 與 stack 的差異

queue : 先進先出 (FIFO)，用 front()/back() 存取，pop() 刪除最早進入的元素
stack : 後進先出 (LIFO)，用 top() 存取，pop() 刪除最晚進入的元素

補充四: 為什麼 pop() 不回傳被刪除的值？

為了「例外安全性 (exception safety)」: 若pop()要回傳值，必須先複製出元素再刪除；
若複製的過程拋出例外，元素已被刪除卻沒拿到值，資料就遺失了。
因此標準庫把「讀取(front)」與「刪除(pop)」分成兩個動作，讓使用者自行控制
*/


// 參考 cppreference std::queue (https://en.cppreference.com/w/cpp/container/queue)
// Generated by Claude 2026/10/2
