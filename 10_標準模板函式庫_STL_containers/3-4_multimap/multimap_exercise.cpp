#include<map>      // multimap定義在<map>標頭檔中
#include<iostream>
#include<string>
#include<algorithm>
#include<numeric>
using namespace std;

/*
======================================================================
《multimap綜合練習題》—— 社團報名系統
======================================================================

情境:
學校要用 std::multimap<string, string> 來管理「社團報名名單」，
key為社團名稱(string)、value為報名學生的姓名(string)。
之所以選用multimap而非map，是因為「同一個社團」本來就允許「多位學生」
報名，也就是同一個key(社團名稱)需要對應多個value(學生姓名)，這正是
multimap與map最根本的差異(map的key不可重複，multimap則允許key重複)。

------------------------------------------------------------
請依序完成以下 Step1 ~ Step10 的操作(請完全依照順序執行，因為每一步
都是基於「前一步執行完的結果」繼續操作)。每完成一步，請將要求的內容
印出：

【Step1】建立一個空的 multimap<string, string> clubList

【Step2】依序使用 insert() 新增以下6筆報名資料，並印出此時
         clubList「完整的內容」(依key排序):
           ("Basketball", "Amy")
           ("TableTennis", "Bob")
           ("Basketball", "Cathy")
           ("Guitar", "David")
           ("Basketball", "Eric")
           ("TableTennis", "Fiona")

【Step3】使用 count() 印出目前報名「Basketball」的人數

【Step4】使用 equal_range() 印出所有報名「Basketball」的學生姓名

【Step5】因為桌球社(TableTennis)臨時停辦，請用 erase(key) 將
         「TableTennis」底下所有的報名資料一次刪除，並印出
         erase()的回傳值(實際刪除的筆數)，以及刪除後clubList
         的完整內容

【Step6】吉他社(Guitar)新增一位報名學生 "Grace"，請用insert()加入
         ("Guitar", "Grace")，並印出此時clubList的完整內容
         (此步驟會讓Guitar社出現兩筆資料: David與Grace)

【Step7】請用 find() 找出「Guitar」社的其中一筆報名資料，印出
         該筆資料的學生姓名，接著直接用 erase(iterator) 把「這一筆」
         刪除(只刪除找到的這一筆，不可用erase(key)整個刪除)，
         並印出刪除後clubList的完整內容

【Step8】請用 lower_bound() 印出所有「社團名稱(key)按字典順序)
         大於等於"Guitar"」的報名資料(key與value都要印出)

【Step9】印出目前clubList的: 總筆數(size)、是否為空(empty)

【Step10】請搭配 <algorithm> 的 count_if()，計算目前clubList中
          「社團名稱為Basketball」的報名筆數，並印出結果
          (此步驟是為了驗證count_if()也能正確處理
          multimap的pair<const Key,Value>元素型別)
======================================================================
*/


// ============================ 以下為範例解答 ============================
// 注意: 以下所有輸出結果，皆已實際編譯執行驗證，確保完全正確
// (編譯環境: g++ 13.3.0, C++17)

int main(){

    // 《Step1》建立空的multimap<string,string>
    multimap<string, string> clubList;


    // 《Step2》依序insert()新增6筆報名資料
    clubList.insert({"Basketball", "Amy"});
    clubList.insert({"TableTennis", "Bob"});
    clubList.insert({"Basketball", "Cathy"});
    clubList.insert({"Guitar", "David"});
    clubList.insert({"Basketball", "Eric"});
    clubList.insert({"TableTennis", "Fiona"});

    cout<<"[Step2] ";
    for (const auto& [club, name] : clubList){
        cout<<'['<<club<<':'<<name<<"] ";
    }
    cout<<endl;
    // 輸出: [Step2] [Basketball:Amy] [Basketball:Cathy] [Basketball:Eric] [Guitar:David] [TableTennis:Bob] [TableTennis:Fiona]
    // 解釋: multimap永遠依key(社團名稱)自動排序(Basketball<Guitar<TableTennis)
    //      同一個key(如三筆Basketball)之間，依照標準規定的insert行為(新元素插入到該key範圍的
    //      upper_bound)，會依照「插入順序」排列: Amy最先插入排最前面，其次Cathy，最後Eric


    // 《Step3》count()計算Basketball的報名人數
    cout<<"[Step3] Basketball count = "<< clubList.count("Basketball") <<endl;
    // 輸出: [Step3] Basketball count = 3


    // 《Step4》equal_range()取得Basketball的[lower_bound,upper_bound)範圍，印出所有姓名
    auto range = clubList.equal_range("Basketball");
    cout<<"[Step4] Basketball members: ";
    for (auto it = range.first; it != range.second; it++){
        cout<< it->second << ' ';
    }
    cout<<endl;
    // 輸出: [Step4] Basketball members: Amy Cathy Eric


    // 《Step5》erase(key)刪除「TableTennis」底下所有資料
    int removed = clubList.erase("TableTennis");
    cout<<"[Step5] removed="<<removed<<" -> ";
    for (const auto& [club, name] : clubList){
        cout<<'['<<club<<':'<<name<<"] ";
    }
    cout<<endl;
    // 輸出: [Step5] removed=2 -> [Basketball:Amy] [Basketball:Cathy] [Basketball:Eric] [Guitar:David]
    // 解釋: erase(key)會把「所有」符合該key的元素一次刪除，TableTennis底下的Bob與Fiona
    //      共2筆都被刪除，因此回傳值(實際刪除筆數)為2


    // 《Step6》insert()新增("Guitar","Grace")，此時Guitar會有兩筆資料
    clubList.insert({"Guitar", "Grace"});
    cout<<"[Step6] ";
    for (const auto& [club, name] : clubList){
        cout<<'['<<club<<':'<<name<<"] ";
    }
    cout<<endl;
    // 輸出: [Step6] [Basketball:Amy] [Basketball:Cathy] [Basketball:Eric] [Guitar:David] [Guitar:Grace]
    // 解釋: 同理，新插入的Grace依標準規定排在既有的David之後


    // 《Step7》find()找到Guitar「其中一筆」(標準規定為該key範圍最前面那筆，即David)，印出後erase(iterator)單獨刪除
    auto itG = clubList.find("Guitar");
    cout<<"[Step7] find(Guitar) -> "<< itG->second <<endl;
    // 輸出: [Step7] find(Guitar) -> David

    clubList.erase(itG);  // 只刪除David這一筆，Grace不受影響
    cout<<"[Step7] after erase -> ";
    for (const auto& [club, name] : clubList){
        cout<<'['<<club<<':'<<name<<"] ";
    }
    cout<<endl;
    // 輸出: [Step7] after erase -> [Basketball:Amy] [Basketball:Cathy] [Basketball:Eric] [Guitar:Grace]


    // 《Step8》lower_bound("Guitar")開始列出到end()的所有資料(即key字典順序>=Guitar的部分)
    cout<<"[Step8] clubs >= Guitar: ";
    for (auto it = clubList.lower_bound("Guitar"); it != clubList.end(); it++){
        cout<<'['<<it->first<<':'<<it->second<<"] ";
    }
    cout<<endl;
    // 輸出: [Step8] clubs >= Guitar: [Guitar:Grace]
    // 解釋: 目前clubList中唯一key>=Guitar(字典順序)的只剩Guitar自己這一筆(Basketball<Guitar)


    // 《Step9》size() / empty()
    cout<<"[Step9] size="<<clubList.size()<<", empty="<<clubList.empty()<<endl;
    // 輸出: [Step9] size=4, empty=0


    // 《Step10》搭配<algorithm>的count_if()，統計key為Basketball的筆數
    int cnt = count_if(clubList.begin(), clubList.end(),
                        [](const pair<const string,string>& p){
                            return p.first == "Basketball";
                        });
    cout<<"[Step10] Basketball count via count_if = "<<cnt<<endl;
    // 輸出: [Step10] Basketball count via count_if = 3
    // 解釋: 與Step3用count()得到的結果相同，驗證兩種作法等價
    //      (注意: multimap的元素型別為pair<const Key, Value>，Lambda參數型別須寫成
    //      pair<const string,string>&，而不能只寫pair<string,string>&，否則會編譯錯誤)

    return 0;
}


// 本練習題與範例解答 Generated by Claude 2026/10/2
