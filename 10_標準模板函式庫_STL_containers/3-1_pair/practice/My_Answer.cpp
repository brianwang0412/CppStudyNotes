/*
題目：學生成績排行榜

請撰寫一個程式，完成以下功能：

定義一個 vector<pair<string, pair<int, double>>> 儲存學生資料，每筆資料為：
first：學生姓名（string）
second.first：學生的班級座號（int）
second.second：學生的總成績（double）
使用以下資料初始化（可用任何合法的 pair 建構方式）：
("Alice", 3, 88.5)
("Bob", 1, 92.0)
("Cathy", 2, 92.0)
("David", 5, 76.5)
撰寫排序規則，將學生依照「總成績由高到低」排序；若成績相同，則依照「座號由小到大」排序。（提示：思考能否只靠 pair 預設比較運算子完成，或需要自訂 comparator）
使用結構化綁定（C++17）印出排序後的名次、姓名、座號、成績，格式如下：
第1名: Bob (座號1) 成績: 92
第2名: Cathy (座號2) 成績: 92
第3名: Alice (座號3) 成績: 88.5
第4名: David (座號5) 成績: 76.5
額外挑戰：寫一個函式 pair<string, double> findTopStudent(const vector<pair<string, pair<int, double>>>& students)回傳成績最高的學生姓名與成績（若有並列，回傳座號最小者）。
*/

//我的做法
#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

bool cmp(pair<string, pair<int, double>>& A, pair<string, pair<int, double>>& B){
    return A.second.second > B.second.second;
}

pair<string, double> findTopStudent(const vector<pair<string, pair<int, double>>>& students);

int main(){
    // 步驟1: 定義
    vector< pair<string, pair<int, double>> > v;

    // 步驟2: 初始化
    v.push_back(make_pair("Alice", make_pair(3, 88.5)));
    v.push_back(make_pair("Bob",   make_pair(1, 92.0)));
    v.push_back(make_pair("Cathy", make_pair(2, 92.0)));
    v.push_back(make_pair("David", make_pair(5, 76.5)));

    // 步驟3: 排序(我使用自訂的cmp比較成績高低)
    sort(v.begin(), v.end(), cmp);

    // 步驟4: 使用C++17後才有的結構化綁定輸出
    // 注意: 不能直接寫for (auto [name, [number, score]] : v)，結構化綁定不支援巢狀語法
    int rank=1;
    for (auto [name, info] : v){
        auto [number, score] = info;
        cout<<"第"<<rank<<"名: "<<name<<" (座號"<<number<<") 成績: "<<score<<endl;
        ++rank;
    }
    /*
    輸出:
    第1名: Bob (座號1) 成績: 92
    第2名: Cathy (座號2) 成績: 92
    第3名: Alice (座號3) 成績: 88.5
    第4名: David (座號5) 成績: 76.5
    */

    // 額外挑戰
    auto TopStudentInfo = findTopStudent(v);
    cout<<"Name: "<< TopStudentInfo.first<<endl;   //輸出: Bob
    cout<<"Score: "<< TopStudentInfo.second<<endl; //輸出: 92
}

pair<string, double> findTopStudent(const vector<pair<string, pair<int, double>>>& students){
    int TopStudentIndex = 0;
    double TopStudentScore = students[0].second.second;
    for (int i=1; i < students.size() ; i++){
        if (students[i].second.second > TopStudentScore){
            TopStudentIndex = i;
            TopStudentScore = students[i].second.second;
        }
        else if (students[i].second.second == TopStudentScore){
            if (students[i].second.first < students[TopStudentIndex].second.first){
                TopStudentIndex = i;
            }
        }
    }
    return make_pair(students[TopStudentIndex].first, TopStudentScore);
}

//Created by B.J.Wang 2026/7/26