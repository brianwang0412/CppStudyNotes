/*
====================================================================
《std::string 綜合測驗題》

題目敘述:

請撰寫一個程式，實作一個「簡易學生成績單處理系統」，需完成以下需求:

給定一筆原始資料(字串)，格式為: "姓名,國文,英文,數學;姓名,國文,英文,數學;..."
例如:
    "Amy,88,92,foo;Bob,75,68,90;Cindy,100,59,77"
    (注意: 此範例中Amy的數學成績故意寫成"foo"，代表一筆錯誤的資料，用來測試例外處理)

請依序完成以下步驟:

1. 使用 stringstream 搭配 getline()，以分號 ';' 為分隔符號，將原始資料切割成每個學生的資料
   (例如: "Amy,88,92,foo"、"Bob,75,68,90"、"Cindy,100,59,77")

2. 對於「每一筆學生資料」，再使用 stringstream 搭配 getline()，以逗號 ',' 為分隔符號，
   切割出 姓名、國文、英文、數學 四個欄位(皆為string)

3. 將 國文、英文、數學 三個字串分別用 stoi() 轉換成整數
   若轉換失敗(拋出 std::invalid_argument)，則印出 "資料錯誤: <學生姓名> 的成績格式不正確"，
   並跳過這位學生(不計入後續計算)

4. 對於資料正確的學生，計算其三科「平均」(取整數，無條件捨去)，
   並判斷等第: 平均>=90 為 "A"，80~89 為 "B"，70~79 為 "C"，60~69 為 "D"，小於60為 "E"

5. 印出每位資料正確的學生的「姓名、平均、等第」，格式為: "<姓名> 平均:<平均> 等第:<等第>"

6. 找出資料正確的學生中，「姓名」的字典順序最小的學生，印出 "字典順序最小的姓名: <姓名>"
   (提示: string已經內建 < 運算子可以直接比較字典順序)

7. 將所有「資料正確」的學生姓名，用 "、" 串接成一個字串後印出，格式為: "全體學生: 姓名1、姓名2、..."
   (提示: 可以邊迴圈邊用 += 串接，並處理好最後一個名字後面不要多一個"、")

8. 將原始資料字串中所有的逗號 ',' 取代為空格 ' '，並印出取代後的完整字串
   (提示: 可以搭配 find() 與 replace()，寫一個迴圈持續尋找並取代，直到找不到為止)

請自行設計程式碼完成以上需求，並確認你的輸出與範例解答完全一致
====================================================================
*/



//====================================================================
//《範例解答》
//====================================================================

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<stdexcept>
using namespace std;

int main(){
    string data = "Amy,88,92,foo;Bob,75,68,90;Cindy,100,59,77";

    vector<string> validNames;  // 儲存資料正確的學生姓名，供第6、7步使用

    cout<<"《步驟1~5: 逐一處理每位學生資料》"<<endl;

    // 1. 以 ';' 切割出每個學生的資料
    stringstream ss(data);
    string studentData;
    while (getline(ss, studentData, ';')){

        // 2. 以 ',' 切割出 姓名、國文、英文、數學
        stringstream ss2(studentData);
        string name, chineseStr, englishStr, mathStr;
        getline(ss2, name, ',');
        getline(ss2, chineseStr, ',');
        getline(ss2, englishStr, ',');
        getline(ss2, mathStr, ',');

        // 3. 將成績字串轉換為整數，並處理例外
        try{
            int chinese = stoi(chineseStr);
            int english = stoi(englishStr);
            int math    = stoi(mathStr);

            // 4. 計算平均與等第
            int avg = (chinese + english + math) / 3;  // 整數除法，自動無條件捨去
            string grade;
            if (avg >= 90) grade = "A";
            else if (avg >= 80) grade = "B";
            else if (avg >= 70) grade = "C";
            else if (avg >= 60) grade = "D";
            else grade = "E";

            // 5. 印出該學生資訊
            cout << name << " 平均:" << avg << " 等第:" << grade << endl;

            validNames.push_back(name);  // 記錄下這位資料正確的學生姓名

        }catch(const std::invalid_argument& e){
            // 3. 轉換失敗時的例外處理
            cout << "資料錯誤: " << name << " 的成績格式不正確" << endl;
        }
    }

    cout<<("======================\n");// 分隔線


    cout<<"《步驟6: 字典順序最小的姓名》"<<endl;

    // 6. 找出validNames中字典順序最小的姓名
    string smallestName = validNames[0];
    for (const string& n : validNames){
        if (n < smallestName){   // string已內建 < 運算子，可直接比較字典順序
            smallestName = n;
        }
    }
    cout << "字典順序最小的姓名: " << smallestName << endl;

    cout<<("======================\n");// 分隔線


    cout<<"《步驟7: 串接所有正確學生姓名》"<<endl;

    // 7. 用"、"串接所有資料正確的學生姓名
    string allNames;
    for (int i=0; i<validNames.size(); i++){
        allNames += validNames[i];
        if (i != validNames.size()-1){  // 不是最後一位學生才加上"、"
            allNames += "、";
        }
    }
    cout << "全體學生: " << allNames << endl;

    cout<<("======================\n");// 分隔線


    cout<<"《步驟8: 將逗號取代為空格》"<<endl;

    // 8. 將data中所有逗號取代為空格
    string replaced = data;
    size_t pos = replaced.find(',');
    while (pos != string::npos){
        replaced.replace(pos, 1, " ");  // 將index=pos開始的1個字元(逗號)取代為空格
        pos = replaced.find(',', pos+1);  // 從取代後的位置繼續往後找下一個逗號
    }
    cout << replaced << endl;

    return 0;
}


/*
====================================================================
《範例解答輸出結果》(可用於自我核對)

《步驟1~5: 逐一處理每位學生資料》
資料錯誤: Amy 的成績格式不正確
Bob 平均:77 等第:C
Cindy 平均:78 等第:C
======================
《步驟6: 字典順序最小的姓名》
字典順序最小的姓名: Bob
======================
《步驟7: 串接所有正確學生姓名》
全體學生: Bob、Cindy
======================
《步驟8: 將逗號取代為空格》
Amy 88 92 foo;Bob 75 68 90;Cindy 100 59 77
====================================================================
*/

// Created by B.J.Wang 2026/8/6
