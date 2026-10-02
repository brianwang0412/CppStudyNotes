#include<queue>
#include<list>
#include<iostream>
#include<sstream>
#include<string>
#include<utility>
using namespace std;

/*
================================ 題目: 銀行叫號系統 ================================

某銀行有「一般窗口」與「VIP窗口」兩條隊伍，請使用 queue 撰寫程式模擬叫號系統。

【資料規定】
1. 每位客戶以 pair<int,string> 表示: first 為「號碼牌」，second 為「姓名」
2. 號碼牌從 1 開始，每執行一次 ADD 就遞增 1 (不論一般或VIP，共用同一組號碼)
3. 一般隊伍 qN 與 VIP隊伍 qV 皆為 queue<pair<int,string>>
4. 另外請宣告 queue<string, list<string>> logQ (底層容器為list)，
   依序記錄「每一位被叫到的客戶姓名」

【指令】(每行一個指令，讀到 END 結束)
ADD  name type   type 為 N 或 V，將客戶加入對應隊伍的尾端
                 (type為N請使用 push；type為V請使用 emplace)
CALL             叫號: 若VIP隊伍不為空，叫VIP隊伍最前面的客戶；否則叫一般隊伍最前面的客戶
                 輸出 "Serve #號碼 姓名"，並將該客戶姓名放入 logQ，且從隊伍中移除
                 若兩條隊伍都是空的，輸出 "No customer"
PEEK             輸出兩條隊伍「最前面」與「最後面」的客戶，格式:
                 "N: front=#號碼 姓名 back=#號碼 姓名"
                 "V: front=#號碼 姓名 back=#號碼 姓名"
                 若該隊伍為空，改輸出 "N: empty" 或 "V: empty"
SHOW             在「不破壞隊伍」的前提下，輸出兩條隊伍的所有客戶，格式:
                 "N(人數): 號碼:姓名 號碼:姓名 ..."  (每位客戶前面有一個空格)
                 "V(人數): ..."
CLEAR x          x 為 N 或 V，清空該隊伍 (queue沒有clear()，請自行處理)
SWAP             將一般隊伍與VIP隊伍的「全部內容」對調 (窗口對調)
CMP              輸出 "N==V:a N<V:b"，a、b 為 0 或 1，使用 queue 的比較運算子
                 (比較時 pair 先比較號碼，再比較姓名)
END              輸出以下兩行後結束:
                 "Log: 姓名 姓名 ..."  (依序輸出logQ中所有姓名，每個姓名後面接一個空格，且輸出後logQ要保持不變)
                 "Left: N=人數 V=人數"

【第二部分: 約瑟夫問題】
7 個人編號 1~7 圍成一圈，從 1 號開始報數，每數到 3 的人出列，
下一個人重新從 1 報起，直到只剩一人。請只用一個 queue<int> 模擬，
輸出出列順序(每個編號後面接一個空格，輸出完換行)，再另起一行輸出最後留下來的人的編號。
輸出前請先輸出一行 "(第二部分)"

【本題用到的 queue 功能】
宣告(含指定底層容器list)、push、emplace、front、back、pop、size、empty、
清空queue(無clear())、不破壞原queue的遍歷、swap、比較運算子 ==、<、
以及「pop與push搭配的循環」

================================ 範例輸入 ================================
ADD Alice N
ADD Bob N
ADD Cathy V
ADD David N
PEEK
SHOW
CALL
CALL
SHOW
ADD Eve V
ADD Frank V
CMP
SWAP
SHOW
CALL
CLEAR N
SHOW
CALL
CALL
CALL
CALL
END

================================ 範例輸出 ================================
N: front=#1 Alice back=#4 David
V: front=#3 Cathy back=#3 Cathy
N(3): 1:Alice 2:Bob 4:David
V(1): 3:Cathy
Serve #3 Cathy
Serve #1 Alice
N(2): 2:Bob 4:David
V(0):
N==V:0 N<V:1
N(2): 5:Eve 6:Frank
V(2): 2:Bob 4:David
Serve #2 Bob
N(0):
V(1): 4:David
Serve #4 David
No customer
No customer
No customer
Log: Cathy Alice Bob David 
Left: N=0 V=0
(第二部分)
3 6 2 7 5 1 
4

================================ 範例解答 ================================
*/

typedef pair<int,string> Customer;  // first: 號碼牌, second: 姓名

// 在不破壞queue的前提下，輸出所有客戶: 複製一份再逐一取出
void show(const char* name, const queue<Customer>& q){
    cout<< name << '(' << q.size() << "):";
    queue<Customer> t = q;
    while (!t.empty()){
        cout<<' '<< t.front().first << ':' << t.front().second;
        t.pop();
    }
    cout<<endl;
}

// 輸出最前面與最後面的客戶 (先檢查empty()，避免對空queue呼叫front()/back())
void peek(const char* name, const queue<Customer>& q){
    if (q.empty()){
        cout<< name << ": empty" <<endl;
    }
    else{
        cout<< name << ": front=#" << q.front().first << ' ' << q.front().second
            << " back=#" << q.back().first << ' ' << q.back().second <<endl;
    }
}

int main(){
    // ---------- 第一部分 ----------
    string input =
        "ADD Alice N\nADD Bob N\nADD Cathy V\nADD David N\nPEEK\nSHOW\nCALL\nCALL\nSHOW\n"
        "ADD Eve V\nADD Frank V\nCMP\nSWAP\nSHOW\nCALL\nCLEAR N\nSHOW\nCALL\nCALL\nCALL\nCALL\nEND\n";
    istringstream in(input);  // 實際考試時可改成 cin

    queue<Customer> qN, qV;
    queue<string, list<string>> logQ;
    int ticket = 1;

    string cmd;
    while (in >> cmd && cmd != "END"){
        if (cmd == "ADD"){
            string name, type;
            in >> name >> type;
            if (type == "N") qN.push({ticket, name});
            else             qV.emplace(ticket, name);
            ticket++;
        }
        else if (cmd == "CALL"){
            queue<Customer>* target = nullptr;  // 指向要叫號的隊伍
            if (!qV.empty())      target = &qV;
            else if (!qN.empty()) target = &qN;

            if (target == nullptr){
                cout<<"No customer"<<endl;
            }
            else{
                Customer c = target->front();  // pop()不會回傳值，須先用front()取出
                target->pop();
                cout<<"Serve #"<< c.first << ' ' << c.second <<endl;
                logQ.push(c.second);
            }
        }
        else if (cmd == "PEEK"){
            peek("N", qN);
            peek("V", qV);
        }
        else if (cmd == "SHOW"){
            show("N", qN);
            show("V", qV);
        }
        else if (cmd == "CLEAR"){
            string x;
            in >> x;
            if (x == "N") qN = queue<Customer>();  // 指派空queue來清空
            else          qV = queue<Customer>();
        }
        else if (cmd == "SWAP"){
            qN.swap(qV);
        }
        else if (cmd == "CMP"){
            cout<<"N==V:"<< (qN == qV) <<" N<V:"<< (qN < qV) <<endl;
        }
    }

    // END: 輸出logQ (複製一份再取出，logQ保持不變)
    cout<<"Log: ";
    queue<string, list<string>> t = logQ;
    while (!t.empty()){
        cout<< t.front() << ' ';
        t.pop();
    }
    cout<<endl;
    cout<<"Left: N="<< qN.size() <<" V="<< qV.size() <<endl;

    // ---------- 第二部分: 約瑟夫問題 (n=7, k=3) ----------
    cout<<"(第二部分)"<<endl;
    queue<int> q;
    for (int i=1; i<=7; i++) q.push(i);
    while (q.size() > 1){
        for (int i=0; i<2; i++){  // 前2個人報1、報2，排到隊尾
            q.push(q.front());
            q.pop();
        }
        cout<< q.front() << ' ';  // 第3個人報3，出列
        q.pop();
    }
    cout<<endl;
    cout<< q.front() <<endl;  // 最後留下的人

    return 0;
}

/*
================================ 評分重點 ================================
1. 宣告 queue<pair<int,string>> 與 queue<string, list<string>>             (宣告、指定底層容器)
2. ADD: N用push({...})、V用emplace(a, b)                                  (push / emplace)
3. CALL: 先front()取值再pop()、呼叫前先檢查empty()                          (front / pop / empty)
4. PEEK: 同時使用front()與back()，且空queue不可呼叫                          (front / back)
5. SHOW / END: 複製一份queue再逐一取出，原queue不可被破壞                    (遍歷技巧、複製建構)
6. CLEAR: 以指派空queue(或swap、重複pop)清空，不可使用不存在的clear()         (清空)
7. SWAP: 使用swap()                                                       (swap)
8. CMP: 使用 == 與 < ，並理解為字典順序比較                                  (比較運算子)
9. 約瑟夫問題: 使用 push(front()) 搭配 pop() 讓隊伍循環                       (pop與push搭配)
10. size()的使用 (人數統計、迴圈條件)                                        (size)
*/
