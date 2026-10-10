#include<queue>
#include<vector>
#include<map>
#include<iostream>
#include<sstream>
#include<string>
#include<functional>
#include<cstdlib>
#include<utility>
using namespace std;

/*
================================ 題目: 急診室分流系統 ================================

【第一部分】
某醫院急診室依「嚴重程度」決定看診順序，請使用 priority_queue 撰寫程式模擬。

【資料規定】
1. 每位病患以 struct Patient 表示，包含: sev(嚴重程度，數字越大越嚴重)、
   ticket(掛號序號，從1開始，每執行一次ADD就遞增1)、name(姓名，保證不重複)
   請為 Patient 撰寫建構函式 Patient(int sev, int ticket, string name)
2. 看診順序: 嚴重程度高者優先；嚴重程度相同時，掛號序號小者(先掛號者)優先
   請自行撰寫「仿函式 (functor)」比較器 CmpPatient，並宣告
   priority_queue<Patient, vector<Patient>, CmpPatient> pq
3. 因為priority_queue無法修改或刪除已放入的元素，請用「延遲刪除 (lazy deletion)」處理UPGRADE:
   另外用 map<string, pair<int,int>> cur 記錄每位「仍在等候」的病患目前的(sev, ticket)，
   若堆頂的紀錄與cur中的紀錄不符(病患已看診，或嚴重程度已被更新)，就是過時的紀錄，必須丟棄

【指令】(每行一個指令，讀到 END 結束)
ADD name sev     新增病患 (請使用 emplace)，不輸出任何內容
UPGRADE name sev 將仍在等候的病患name的嚴重程度更新為sev (保證sev比原本大，且病患存在)
                 保留原本的掛號序號，不輸出任何內容，不得使用pop()以外的方式刪除舊紀錄
CALL             叫號: 先丟棄堆頂的所有過時紀錄，若有病患，輸出 "Treat 姓名 (sev 嚴重程度)" 並將其移出；
                 否則輸出 "No patient"
PEEK             先丟棄堆頂的所有過時紀錄，輸出 "Top: 姓名 (sev 嚴重程度)"；若沒有病患輸出 "Top: none"
SHOW             在「不破壞原priority_queue」的前提下，依看診順序輸出所有「仍有效」的病患，
                 格式: "Queue:" 後面接每位病患 " 姓名(嚴重程度)"，沒有病患時只輸出 "Queue:"
SIZE             輸出 "Waiting: 等候人數 Heap: priority_queue的size()"
END              結束

【第二部分】(每小題輸出前，請先輸出該小題標籤，如 "2-1:")
2-1: 將 {5,2,8,1,9,3} 以「iterator範圍建構」放入最小堆，依序取出並輸出所有元素
2-2: 資料串流 {4,9,1,7,3,8,5} 依序加入，只用大小不超過3的最小堆，
     每當已加入的數字達3個以上時，輸出「目前第3大的數」(以空白分隔)
2-3: 宣告最大堆 A 放入 {3,1,2}、最大堆 B 放入 {10,20}，
     將A與B交換後輸出 "A.top=? B.top=? A.size=? B.size=?"，
     再將A清空(priority_queue沒有clear())，輸出 A.empty() 的結果
2-4: 使用「Lambda比較器」，將 {12,7,10,8,15,3} 放入 priority_queue，
     依「與10的距離由近到遠」取出並輸出；距離相同時，數值小者先出
2-5: 宣告 priority_queue<pair<int,string>>(使用預設比較)，放入 (2,"b")、(5,"a")、(2,"z")、(5,"c")
     (其中至少一筆須使用emplace)，依序取出並輸出，格式: "5:c 5:a 2:z 2:b "

【本題用到的 priority_queue 功能】
宣告(最大堆、最小堆、自訂比較器、Lambda)、iterator範圍建構、push、emplace、top、pop、
size、empty、swap、清空(無clear())、不破壞原priority_queue的遍歷、
pair的預設比較、延遲刪除

================================ 範例輸入(第一部分) ================================
ADD Amy 3
ADD Ben 5
ADD Cara 3
ADD Dan 1
PEEK
SHOW
UPGRADE Dan 5
UPGRADE Cara 4
SIZE
PEEK
CALL
CALL
SHOW
CALL
CALL
CALL
SIZE
END

================================ 範例輸出 ================================
Top: Ben (sev 5)
Queue: Ben(5) Amy(3) Cara(3) Dan(1)
Waiting: 4 Heap: 6
Top: Ben (sev 5)
Treat Ben (sev 5)
Treat Dan (sev 5)
Queue: Cara(4) Amy(3)
Treat Cara (sev 4)
Treat Amy (sev 3)
No patient
Waiting: 0 Heap: 0
2-1: 1 2 3 5 8 9 
2-2: 1 4 4 7 7 
2-3: A.top=20 B.top=3 A.size=2 B.size=3
1
2-4: 10 8 12 7 15 3 
2-5: 5:c 5:a 2:z 2:b 
================================ 範例解答 ================================
*/

struct Patient{
    int sev;
    int ticket;
    string name;
    Patient(int s, int t, string n) : sev(s), ticket(t), name(n) {}
};

// comp(a,b)為true表示「a的優先權比b低」
struct CmpPatient{
    bool operator()(const Patient& a, const Patient& b) const{
        if (a.sev != b.sev) return a.sev < b.sev;  // 嚴重程度低者優先權低
        return a.ticket > b.ticket;                 // 嚴重程度相同: 序號大(較晚掛號)者優先權低
    }
};

int main(){
    // ---------- 第一部分 ----------
    string input =
        "ADD Amy 3\nADD Ben 5\nADD Cara 3\nADD Dan 1\nPEEK\nSHOW\nUPGRADE Dan 5\nUPGRADE Cara 4\n"
        "SIZE\nPEEK\nCALL\nCALL\nSHOW\nCALL\nCALL\nCALL\nSIZE\nEND\n";
    istringstream in(input);  // 實際考試時可改成 cin

    priority_queue<Patient, vector<Patient>, CmpPatient> pq;
    map<string, pair<int,int>> cur;  // name -> (sev, ticket)，仍在等候的病患
    int ticket = 1;

    // 判斷一筆紀錄是否過時: 病患已不在等候名單，或嚴重程度與最新資料不同
    auto isStale = [&](const Patient& p){
        auto it = cur.find(p.name);
        return it == cur.end() || it->second.first != p.sev;
    };
    // 丟棄堆頂所有過時紀錄
    auto clean = [&](){
        while (!pq.empty() && isStale(pq.top())) pq.pop();
    };

    string cmd;
    while (in >> cmd && cmd != "END"){
        if (cmd == "ADD"){
            string name; int sev;
            in >> name >> sev;
            pq.emplace(sev, ticket, name);
            cur[name] = {sev, ticket};
            ticket++;
        }
        else if (cmd == "UPGRADE"){
            string name; int sev;
            in >> name >> sev;
            int t = cur[name].second;      // 保留原本的掛號序號
            cur[name].first = sev;         // 舊的紀錄因此變成過時紀錄
            pq.emplace(sev, t, name);      // 放入新的紀錄 (priority_queue無法修改舊紀錄)
        }
        else if (cmd == "CALL"){
            clean();
            if (pq.empty()){
                cout<<"No patient"<<endl;
            }
            else{
                Patient p = pq.top();  // pop()不會回傳值，須先用top()複製出來
                pq.pop();
                cout<<"Treat "<< p.name <<" (sev "<< p.sev <<")"<<endl;
                cur.erase(p.name);
            }
        }
        else if (cmd == "PEEK"){
            clean();
            if (pq.empty()) cout<<"Top: none"<<endl;
            else cout<<"Top: "<< pq.top().name <<" (sev "<< pq.top().sev <<")"<<endl;
        }
        else if (cmd == "SHOW"){
            cout<<"Queue:";
            priority_queue<Patient, vector<Patient>, CmpPatient> t = pq;  // 複製一份再逐一取出
            while (!t.empty()){
                if (!isStale(t.top())) cout<<' '<< t.top().name <<'('<< t.top().sev <<')';
                t.pop();
            }
            cout<<endl;
        }
        else if (cmd == "SIZE"){
            cout<<"Waiting: "<< cur.size() <<" Heap: "<< pq.size() <<endl;
        }
    }

    // ---------- 第二部分 ----------
    // 2-1: 最小堆 + iterator範圍建構
    {
        vector<int> data = {5, 2, 8, 1, 9, 3};
        priority_queue<int, vector<int>, greater<int>> h(data.begin(), data.end());
        cout<<"2-1: ";
        while (!h.empty()){
            cout<< h.top() << ' ';
            h.pop();
        }
        cout<<endl;
    }

    // 2-2: 資料串流第3大 (大小不超過3的最小堆)
    {
        priority_queue<int, vector<int>, greater<int>> h;
        cout<<"2-2: ";
        for (int x : {4, 9, 1, 7, 3, 8, 5}){
            h.push(x);
            if (h.size() > 3) h.pop();  // 超過3個就丟掉最小的
            if (h.size() == 3) cout<< h.top() << ' ';
        }
        cout<<endl;
    }

    // 2-3: swap與清空
    {
        priority_queue<int> A, B;
        for (int x : {3, 1, 2}) A.push(x);
        for (int x : {10, 20}) B.push(x);
        A.swap(B);
        cout<<"2-3: A.top="<< A.top() <<" B.top="<< B.top()
            <<" A.size="<< A.size() <<" B.size="<< B.size() <<endl;
        A = priority_queue<int>();  // 以指派空priority_queue清空
        cout<< A.empty() <<endl;
    }

    // 2-4: Lambda比較器，距離相同時數值小者先出
    {
        auto cmp = [](int a, int b){
            int da = abs(a - 10), db = abs(b - 10);
            if (da != db) return da > db;  // 距離大者優先權低
            return a > b;                  // 距離相同: 數值大者優先權低
        };
        priority_queue<int, vector<int>, decltype(cmp)> h(cmp);  // Lambda須在建構時傳入
        for (int x : {12, 7, 10, 8, 15, 3}) h.push(x);
        cout<<"2-4: ";
        while (!h.empty()){
            cout<< h.top() << ' ';
            h.pop();
        }
        cout<<endl;
    }

    // 2-5: pair的預設比較 (先比first，再比second)
    {
        priority_queue<pair<int,string>> h;
        h.push({2, "b"});
        h.push(make_pair(5, "a"));
        h.emplace(2, "z");
        h.emplace(5, "c");
        cout<<"2-5: ";
        while (!h.empty()){
            cout<< h.top().first << ':' << h.top().second << ' ';
            h.pop();
        }
        cout<<endl;
    }

    return 0;
}

/*
================================ 評分重點 ================================
1. 自訂仿函式比較器，並理解 comp(a,b)=true 代表「a優先權較低」                (自訂比較器)
2. ADD使用emplace；UPGRADE以「再放入一筆新紀錄」取代修改                      (emplace / 無法修改元素)
3. CALL: 先top()複製、再pop()；呼叫前先檢查empty()                           (top / pop / empty)
4. 延遲刪除: 以cur判斷堆頂是否過時，過時就pop()丟棄                            (延遲刪除)
5. SHOW: 複製一份priority_queue再逐一取出，原priority_queue不可被破壞          (遍歷技巧)
6. SIZE: size()包含過時紀錄，與實際等候人數不同                                (size)
7. 2-1: greater + iterator範圍建構；2-2: 大小為K的最小堆                      (最小堆、範圍建構)
8. 2-3: swap()、以指派空priority_queue清空(無clear())                        (swap / 清空)
9. 2-4: Lambda比較器需用decltype並在建構時傳入，且平手時加入第二判斷條件        (Lambda)
10. 2-5: pair預設比較                                                       (pair)
*/
