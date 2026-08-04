#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, int> students;
    int n;
    cin >> n;

    // 步驟1：輸入資料，重複姓名用最新分數覆蓋
    for (int i = 0; i < n; i++) {
        string name;
        int score;
        cin >> name >> score;
        students[name] = score;  // operator[] 天生就是「覆蓋或新增」的語意
    }

    // 步驟2：依姓名排序印出所有資料
    for (const auto& [name, score] : students) {
        cout << name << ": " << score << endl;
    }

    // 步驟3：查詢
    string queryName;
    cin >> queryName;
    auto it = students.find(queryName);
    if (it != students.end()) {
        cout << it->second << endl;
    } else {
        cout << "查無此人" << endl;
    }

    // 步驟3(第二次查詢，依範例輸入共查詢兩次)
    cin >> queryName;
    it = students.find(queryName);
    if (it != students.end()) {
        cout << it->second << endl;
    } else {
        cout << "查無此人" << endl;
    }

    // 步驟4：刪除
    string deleteName;
    cin >> deleteName;
    if (students.count(deleteName)) {
        students.erase(deleteName);
        cout << "刪除成功" << endl;
    } else {
        cout << "刪除失敗" << endl;
    }

    cin >> deleteName;
    if (students.count(deleteName)) {
        students.erase(deleteName);
        cout << "刪除成功" << endl;
    } else {
        cout << "刪除失敗" << endl;
    }

    // 步驟5：統計60分以上人數
    int countAbove60 = 0;
    for (const auto& [name, score] : students) {
        if (score >= 60) countAbove60++;
    }
    cout << countAbove60 << endl;

    // 步驟6：目前總人數
    cout << students.size() << endl;

    return 0;
}

/*
範例輸入:
5
Alice 85
Bob 45
Charlie 90
Bob 70
David 55
Charlie
Eve
Bob
Frank

範例輸出:
Alice:85
Bob:70
Charlie:90
David:55
90
查無此人
刪除成功
刪除失敗
2
3
*/