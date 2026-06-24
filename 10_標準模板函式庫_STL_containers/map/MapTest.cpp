#include<map>

#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

// map<key_type, value_type, comp> MapName;

int main(){
    // 1. 宣告
    map<string, int> scores;
    map<string, int> balls = { {"basketball" , 10}, {"football" , 20} };

    // 2. 存取
    cout<<balls["basketball"]<<'\n';  // 10
    cout<<balls.at("basketball")<<'\n';  // 10
    /*
    注意:
    使用[key]存取元素時
    若此時該元素不存在，會自動新增{該元素名, 型別預設值} (例如{"badminton", 0})
    
    使用.at(key)存取元素時
    若此時該元素不存在，會拋出一個 std::out_of_range 的異常
    要寫 try-catch 才能讓程式繼續運行
    */


    cout<<("====================================\n");// 分隔線

    // 3. 插入
    scores["Math"] = 70; //若當前map內不存在，則新增並賦值
    scores.insert({"English", 80});
    scores.emplace("OOP", 100); //更高效

    // 4. 修改
    balls["basketball"] = 30;
    balls = { {"badminton", 100} };

    // 5. 搜尋
    // .find(key)會回傳該key的iterator(迭代器)，若找不到則回傳end()
    //  iterator(迭代器)的操作類似pointer
    map<string,int>::iterator It1 = scores.find("Math"); // 不推薦打出迭代器完整的型別
    auto It2 = scores.find("Math"); // 推薦使用 auto ，讓編譯器自動推導
    cout<<(*It2).first<<' '<<It2->second<<'\n';  // Math 70

    // .count(key)會回傳該key是否存在，1或0
    bool Exist1 = scores.count("English");
    bool Exist2 = scores.count("Japanese");
    cout<<Exist1<<'\n';  // 1
    cout<<Exist2<<'\n';  // 0

    /*補充
    lower_bound(key)：回傳第一個 key >= 指定值的 iterator
    upper_bound(key)：回傳第一個 key > 指定值的 iterator
    */

    cout<<("====================================\n");// 分隔線

    // 6. 刪除
    balls.erase("badminton");  // erase(key或iterator)
    // 補充:  .clear() 清空所有元素

    // 7. 其他
    // 取得長度 .size()
    cout << "scores's length = " << scores.size();  // scores's length = 3

    // 檢查是否為空 .empty()
    cout << "\nIs scores empty? : " << boolalpha << scores.empty() <<'\n';  // Is scores empty? : false

    cout<<("====================================\n");// 分隔線

    scores = { {"Math", 70}, {"English", 80}, {"OOP", 100} };

    // 8. 遍歷
    // range-based for loop
    for (auto& pair:scores){  // pair 是scores內每一個元素的物件，用dot(.)
        cout<<pair.first<<' '<<pair.second<<'\n';
    }

    cout<<("====================================\n");// 分隔線

    // for loop
    for (auto it = scores.begin(); it != scores.end(); ++it){  // it 是一個指向 pair 的 iterator，要用arrow(->)
        cout<<it->first<<' '<<it->second<<'\n';
    }

    /* 
    兩個方法的輸出相同: 
    English 80
    Math 70
    OOP 100
    */

    //補充 : 檢查是否存在 .count()
    map<string, int>M;
    M["abc"]=1;
    cout << M.count("abc")<<endl; // 1
    cout << M.count("ddd") <<endl; // 2
}




// 本篇筆記參考 https://hackmd.io/@LukeTseng/Hya8JhQVx
// 本篇筆記參考 Gemini
//Created by B.J.Wang