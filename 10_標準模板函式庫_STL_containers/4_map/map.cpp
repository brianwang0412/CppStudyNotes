#include<map>  // 需引入<map>標頭檔

#include<iostream>
#include<string>
#include<stdexcept>
#include<utility>
using namespace std;

/*
前言: map的特性

1. 每個元素皆為pair鍵值對 pair<const Key, Value>
2. 依照 Key 自動排序（預設由小到大）
3. Key 不可重複
4. 插入、刪除、搜尋的時間複雜度皆為 O(log n)，底層邏輯為紅黑樹
*/

int main(){
{
    // 《1. map的宣告》

    // 建立空的map
    map<string, int> m1;

    // 初始化
    map<string, int> m2 = {{"water", 1}, {"soda", 20}};

    // 複製建構
    map<string, int> m3(m2);

    // 自訂排序方式 (改成以key值由大到小)
    map<string, int, greater<string> > m4 = {{"apple", 999}, {"banana", 1}};
    for (auto& i:m4) cout<<i.first<<' '<<i.second<<endl;
    /*
    輸出:
    banana 1
    apple 999
    */
}   

cout<<("======================\n");// 分隔線

{
    // 《2. 存取》
    // 只能用Key去找Value
    // 若想用Value找Key需要遍歷整個map

    map<string, int> mp = {{"apple", 5}, {"banana", 3}} ;

    // 使用 mp[Key] 來存取
    // 若Key不存在會自動建立並給予預設值，再賦值
    cout<< mp["apple"] <<endl;  // 輸出: 5
    mp["apple"] = 111;  // 修改{"apple", 5}的值
    cout<< mp["apple"] <<endl;  // 輸出: 111

    cout<< mp["cherry"] <<endl;  // 輸出: 0 （會自動建立 key="cherry", value=0）

    // 使用 mp.at(Key) 來存取
    // key 不存在時會拋出 std::out_of_range 例外，不會新增 key，較安全
    cout<< mp.at("banana") <<endl;  // 輸出: 3

    try{
        cout<< mp.at("egg") <<endl;
    }catch (const std::out_of_range& e){
        cout<< "error: " << e.what() <<endl;
    }
    // 輸出: error: map::at

    // 使用 mp.find(Key) 來找到指定元素
    // 回傳指向該元素的 迭代器(iterator)，找不到則回傳 mp.end()
    // 不會新增 key，是最推薦的查詢方式
    map<string, int>::iterator it = mp.find("banana");  //banana存在，回傳指向{banana, 3}的iterator
    if (it != mp.end()){
        cout<< it->first << " : " << it->second <<endl;
    }
    // 輸出: banana : 3

    auto it_2 = mp.find("mango");  // mango不存在，回傳mp.end()
    if (it_2 == mp.end()){
        cout<< "mango does not exist" <<endl;
    }

    // 使用 mp.count(Key) 來取得該Key在mp中存在的個數
    // 由於map中Key不得重複，因此也可視作確認Key是否存在
    cout << mp.count("apple") << endl;   // 輸出: 1 (map中key不重複，只會是0或1)
    cout << mp.count("fruit") << endl;  // 輸出: 0
}

cout<<("======================\n");// 分隔線

{
    // 《3. 新增》

    map<string, int> mp;

    // 使用 mp[Key]=Value 來新增
    mp["apple"] = 1;  // 新增動作 : 此時mp內還沒有"apple"，所以新增{"apple", 1}
    mp["apple"] = 2;  // 修改動作 : 此時mp內已有{"apple", 1}，將其改為{"apple", 2}
    cout<< mp["apple"] <<endl;  // 輸出: 2


    // 使用 mp.insert( {Key, Value} ) 來新增
    // 不會覆蓋已存在的 key，回傳 pair<iterator, bool>，bool 表示是否新增成功
    auto result_1 = mp.insert({"banana", 123});
    cout<< mp["banana"] <<endl;  // 輸出: 123
    cout<< result_1.second <<endl;  //輸出: 1 (代表成功新增)

    auto result_2 = mp.insert({"banana", 999});
    cout<< mp["banana"] <<endl;  // 輸出: 123
    
}

}




// 本篇筆記參考 ShengYu Talk - C++ std::map 用法與範例(https://shengyu7697.github.io/std-map/)
// 本篇筆記參考 Claude