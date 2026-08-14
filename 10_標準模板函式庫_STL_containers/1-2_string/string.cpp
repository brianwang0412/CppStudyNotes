#include<string>  //需引入string標頭檔

#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>   // stringstream / istringstream / ostringstream
#include<cctype>    // toupper, tolower, isdigit...等字元判斷函式
#include<stdexcept> // std::out_of_range 定義在 <stdexcept> 標頭檔中
using namespace std;

/*
前言: string的特色、用途

string 是 C++標準函式庫提供的「字串類別」
相較於傳統C字元陣列(如 char s[100];)
string 可以像vector一樣「動態調整長度」，並且提供大量好用的成員函式(如插入、刪除、搜尋、比較...等)
不需要再手動處理'\0'結尾字元，更安全、更方便
*/

int main(){
{
    // 《1. string的宣告》

    // 建立空的string，名稱為s1
    string s1;

    // 使用字串字面值(string literal)初始化
    string s2 = "hello";
    string s3("world");

    // 建立包含5個'a'字元的string
    string s4(5, 'a');  // "aaaaa"

    // 複製建構，s5與s2會互相獨立
    string s5(s2);  // "hello"

    // 部分複製: string(str, pos, len)，從str的index=pos開始複製len個字元
    string s6(s2, 1, 3);  // 從s2的index=1開始複製3個字元 -> "ell"

    // 用C風格字元陣列初始化
    char arr[] = "abc";
    string s7(arr);  // "abc"

    // 用字元陣列的前n個字元初始化
    string s8(arr, 2);  // "ab"

    // 也可以用兩個iterator(迭代器)範圍來初始化
    string s9(s2.begin(), s2.begin()+3);  // "hel"

    // 建立string所組成的vector(儲存多個字串)
    vector<string> vs = {"apple", "banana", "cherry"};
}
//===============================分隔線===============================
{
    // 《2. string的新增、存取與刪除》  

    string s = "Hello";

    // 1. 新增 (+=, append, push_back, insert)

    // 使用 += 在尾端新增字元或字串
    s += '!';         // "Hello!"
    s += " World";    // "Hello! World"
    cout<< s <<endl;  // 輸出: Hello! World

    // 使用 s.append(x) 在尾端新增字串(功能與+=類似，但更彈性，可指定新增的長度、次數)
    s.append("!!!");        // 新增字串 -> "Hello! World!!!"
    s.append(3, '?');        // 新增3個'?' -> "Hello! World!!!???"
    cout<< s <<endl;  // 輸出: Hello! World!!!???

    // 使用 s.push_back(c) 在尾端新增「單一字元」
    s = "abc";
    s.push_back('d');
    cout<< s <<endl;  // 輸出: abcd

    // 使用 s.insert(pos, x) 在指定位置插入字串
    // 注意: string的insert第一個參數是「index(整數)」，也可以是iterator，兩種寫法皆合法
    s = "abc";
    s.insert(1, "XY");  // 在index=1的位置插入"XY"
    cout<< s <<endl;  // 輸出: aXYbc

    s.insert(s.begin(), 'Z');  // 使用iterator，在開頭插入'Z'
    cout<< s <<endl;  // 輸出: ZaXYbc


    cout<<("======================\n");// 分隔線


    // 2. 存取 ([i] .at(i) .front() .back())

    s = "Hello";

    // 使用 s[i] 來存取
    s[0] = 'h';
    cout<< s[0] <<endl;  // 輸出: h

    // 使用 s.at(i) 來存取
    // .at(i) 會先做邊界檢查
    s.at(1) = 'E';
    cout<< s.at(1) <<endl;  // 輸出: E

    // 邊界檢查範例
    try {
        cout << s.at(99) << endl;  // 超出範圍
    } catch (const std::out_of_range &e) {
        cout << "錯誤：" << e.what() << endl;
        // 輸出: 錯誤：basic_string::at: __n (which is 99) >= this->size() (which is 5)
        // 注意: 此訊息內容為 libstdc++(GCC) 的實作細節，並非C++標準規範，
        //       換到 MSVC 等其他編譯器可能會顯示不同文字
    }

    // 使用 s.front()與s.back() 來存取
    s.front() = 'X';  // 取第一個字元，等同於存取s[0]
    cout<< s.front() <<endl;  // 輸出: X

    s.back() = 'Y';  // 取最後一個字元
    cout<< s.back() <<endl;  // 輸出: Y

    cout<< s <<endl;  // 輸出: XEllY

    cout<<("======================\n");// 分隔線

    // 3. 刪除

    // 現在string s為 "XEllY"

    // 用 s.erase(pos, len) 刪除從index=pos開始的len個字元(預設len會刪到結尾)
    s.erase(1, 2);  // 從index=1開始刪除2個字元(即"El")
    cout<< s <<endl;  // 輸出: XlY

    // 用 s.erase(iterator) 刪除指定位置(單一字元)
    s = "abcde";
    s.erase(s.begin()+1);  // 刪除index=1的字元('b')
    cout<< s <<endl;  // 輸出: acde

    // 用 s.erase(first, last) 刪除範圍[first, last)
    s = "abcde";
    s.erase(s.begin(), s.begin()+2);  // 刪除前兩個字元
    cout<< s <<endl;  // 輸出: cde

    // 用 s.pop_back() 刪除最後一個字元
    s = "abcde";
    s.pop_back();
    cout<< s <<endl;  // 輸出: abcd

    // 用 s.clear() 清空string
    s.clear();
    cout<<"["<< s <<"]"<<endl;  // 輸出: []  (空字串)
}
cout<<("====================================\n");// 分隔線
{
    // 《3. 遍歷》

    string s = "abcde";

    // 1. 基本for迴圈
    for (int i=0; i<s.size(); i++){
        cout<< s[i] << ' ';
    }
    cout<<endl;
    // 輸出: a b c d e


    // 2. 使用「以範圍為基礎的 for 語句」（Range-based for Statement）
    for (char c : s){
        cout<< c << ' ';
    }
    cout<<endl;
    // 輸出: a b c d e


    // 3. 若想修改元素值，可以改為用c作為字元的參考(reference)
    for (char& c : s){
        c = toupper(c);  // 將每個字元轉為大寫
    }
    cout<< s <<endl;  // 輸出: ABCDE


    // 4. 使用迭代器(iterator)遍歷
    for (string::iterator it = s.begin(); it != s.end(); it++){
        cout<< *it << ' ';
    }
    cout<<endl;
    // 輸出: A B C D E
}
cout<<("====================================\n");// 分隔線
{
    //《4. 常用功能》

    string s = "Hello World";

    // 1. 取得字串長度: s.length() 與 s.size() 功能完全相同
    cout<< s.length() <<endl;  // 輸出: 11
    cout<< s.size()   <<endl;  // 輸出: 11

    // 判斷字串是否為空
    cout<< s.empty() <<endl;  // 輸出: 0 (表示非空)


    cout<<("======================\n");// 分隔線


    // 2. 子字串擷取: s.substr(pos, len)
    // 從index=pos開始擷取len個字元(預設len會擷取到結尾)，回傳一個新的string(不會修改原字串s)
    string sub1 = s.substr(6);      // 從index=6擷取到結尾
    cout<< sub1 <<endl;  // 輸出: World

    string sub2 = s.substr(0, 5);   // 從index=0開始擷取5個字元
    cout<< sub2 <<endl;  // 輸出: Hello


    cout<<("======================\n");// 分隔線


    // 3. 搜尋: find / rfind / find_first_of / find_last_of / find_first_not_of
    // 皆回傳「index(size_t型別)」，找不到則回傳 string::npos

    s = "Hello World, Hello C++";

    // s.find(x, pos=0): 從index=pos開始「往右」搜尋子字串x第一次出現的位置
    size_t pos1 = s.find("Hello");
    cout<< pos1 <<endl;  // 輸出: 0

    size_t pos2 = s.find("Hello", 1);  // 從index=1開始找
    cout<< pos2 <<endl;  // 輸出: 13

    // 找不到的情況
    size_t pos3 = s.find("Java");
    if (pos3 == string::npos){
        cout<<"Not found"<<endl;
    }
    // 輸出: Not found

    // s.rfind(x, pos=npos): 從index=pos開始「往左」搜尋子字串x最後一次出現的位置
    size_t pos4 = s.rfind("Hello");
    cout<< pos4 <<endl;  // 輸出: 13

    // s.find_first_of(chars): 找「chars中任一字元」第一次出現的位置
    s = "abc123xyz";
    size_t pos5 = s.find_first_of("0123456789");  // 找第一個數字字元
    cout<< pos5 <<endl;  // 輸出: 3

    // s.find_last_of(chars): 找「chars中任一字元」最後一次出現的位置
    size_t pos6 = s.find_last_of("0123456789");  // 找最後一個數字字元
    cout<< pos6 <<endl;  // 輸出: 5

    // s.find_first_not_of(chars): 找「第一個不屬於chars」的字元位置
    s = "   Hello";
    size_t pos7 = s.find_first_not_of(" ");  // 找第一個不是空白的字元
    cout<< pos7 <<endl;  // 輸出: 3


    cout<<("======================\n");// 分隔線


    // 4. 取代: s.replace(pos, len, newStr)
    // 將index=pos開始的len個字元，取代為newStr
    s = "Hello World";
    s.replace(6, 5, "C++");  // 將"World"(從index=6開始的5個字元)取代為"C++"
    cout<< s <<endl;  // 輸出: Hello C++

    // 搭配find()使用，取代第一次出現的子字串
    s = "cat dog cat";
    size_t p = s.find("cat");
    if (p != string::npos){
        s.replace(p, 3, "bird");  // 將第一個"cat"取代為"bird"
    }
    cout<< s <<endl;  // 輸出: bird dog cat


    cout<<("======================\n");// 分隔線


    // 5. 比較: s.compare(other) 與 == != < <= > >= 運算子

    // s.compare(other): 依字典順序比較，s<other回傳負數，s==other回傳0，s>other回傳正數
    string a = "apple", b = "banana";
    cout<< a.compare(b) <<endl;  // 輸出: -1 (a的字典順序在b之前，實際負值依實作而定，一般為 'a'-'b' = -1)

    // 也可以直接使用比較運算子，較直覺
    cout<< (a == b) <<endl;  // 輸出: 0
    cout<< (a != b) <<endl;  // 輸出: 1
    cout<< (a <  b) <<endl;  // 輸出: 1
    cout<< (a >  b) <<endl;  // 輸出: 0


    cout<<("======================\n");// 分隔線


    // 6. 字串與數字的轉換

    // 數字轉字串: to_string(x)
    int num = 123;
    string numStr = to_string(num);
    cout<< numStr <<endl;  // 輸出: 123
    cout<< (numStr + "!") <<endl;  // 輸出: 123!  (驗證numStr確實是string型別，可以與字串相加)

    double d = 3.14;
    cout<< to_string(d) <<endl;  // 輸出: 3.140000  (預設保留6位小數)

    // 字串轉數字: stoi (轉int)、stol (轉long)、stod (轉double) ...等
    string s10 = "456";
    int n = stoi(s10);
    cout<< n + 1 <<endl;  // 輸出: 457  (驗證n確實是int型別，可以做數值運算)

    string s11 = "3.14abc";  // 若字串開頭可以轉換成數字，會轉換到不能轉換為止，不會報錯
    double dd = stod(s11);
    cout<< dd <<endl;  // 輸出: 3.14

    // 若字串「開頭」就無法轉換成數字，則會拋出std::invalid_argument例外
    try{
        int bad = stoi("abc");
    }catch(const std::invalid_argument& e){
        cout<< "error: " << e.what() <<endl;
    }
    // 輸出: error: stoi
    // 注意: 此訊息內容同樣為 libstdc++(GCC) 的實作細節，不同編譯器可能顯示不同文字


    cout<<("======================\n");// 分隔線


    // 7. 大小寫轉換
    // string本身沒有內建的大小寫轉換函式，需要搭配<algorithm>的transform()與<cctype>的toupper/tolower使用

    s = "Hello World";
    string upper = s;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    cout<< upper <<endl;  // 輸出: HELLO WORLD

    string lower = s;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    cout<< lower <<endl;  // 輸出: hello world


    cout<<("======================\n");// 分隔線


    // 8. 反轉與排序
    // 搭配<algorithm>使用，用法與vector相同

    s = "Hello";
    reverse(s.begin(), s.end());
    cout<< s <<endl;  // 輸出: olleH

    s = "dcba";
    sort(s.begin(), s.end());  // 依字元的ASCII碼由小到大排序
    cout<< s <<endl;  // 輸出: abcd


    cout<<("======================\n");// 分隔線


    // 9. 交換兩個字串的內容: s.swap(other)
    string x = "abc", y = "xyz";
    x.swap(y);
    cout<< "x: " << x <<endl;  // 輸出: x: xyz
    cout<< "y: " << y <<endl;  // 輸出: y: abc


    cout<<("======================\n");// 分隔線


    // 10. 字串分割 (string本身沒有內建split函式，常見作法為搭配stringstream)

    string csv = "apple,banana,cherry";
    stringstream ss(csv);
    string token;
    vector<string> tokens;
    while (getline(ss, token, ',')){  // 以逗號','作為分隔符號，逐一取出子字串
        tokens.push_back(token);
    }
    for (const string& t : tokens) cout<< t << ' ';
    cout<<endl;
    // 輸出: apple banana cherry


    cout<<("======================\n");// 分隔線


    // 11. c_str() 與 data()
    // 將string轉換為C風格字串(const char*)，常用於需要與C語言函式庫互動的情境

    s = "Hello";
    const char* cstr = s.c_str();
    cout<< cstr <<endl;  // 輸出: Hello


    cout<<("======================\n");// 分隔線


    // 12. 計算某字元的出現次數
    // string本身沒有內建count函式，需要搭配<algorithm>的count()使用

    s = "banana";
    int cnt = count(s.begin(), s.end(), 'a');
    cout<< cnt <<endl;  // 輸出: 3
}
//===============================分隔線===============================
{
    // 《補充: getline() 的用法》
    // getline() 定義在 <string> (讀取cin/一般字串) 或 <sstream> (讀取stringstream)
    // 功能: 讀取「一整行」文字，會讀到空白字元也不會停止，直到遇到換行字元'\n'(或指定的分隔符號)為止

    // 1. getline(cin, s)：從標準輸入讀取一整行，存入字串s
    string line;
    cout<<"請輸入一整行文字: ";
    getline(cin, line);
    cout<<"你輸入的是: "<< line <<endl;
    // 輸入: Hello World from Claude
    // 輸出: 你輸入的是: Hello World from Claude
    // 注意: 若改用 cin >> line，遇到空白就會停止，只會讀到"Hello"，這是getline與cin>>最大的差異


    cout<<("======================\n");// 分隔線


    // 2-1. 【經典陷阱】cin>>x 之後直接接 getline() 會讀到空字串
    // cin>>n 只會讀取數字本身，「不會」把數字後面的換行字元'\n'一併讀走，
    // 因此緩衝區中還殘留著那個'\n'，若接著呼叫getline，會立刻讀到這個殘留的'\n'就結束，得到「空字串」
    int n;
    cin >> n;
    cout<<"cin>>讀到的數字: "<< n <<endl;

    string rest;
    getline(cin, rest);
    cout<<"未清緩衝區直接getline，得到: ["<< rest <<"]"<<endl;  // 用中括號標示方便觀察是否為空字串
    /*
    輸入: 5
    輸出:
    cin>>讀到的數字: 5
    未清緩衝區直接getline，得到: []
    */


    // 2-2. 正確作法: 在cin>>之後、getline()之前，先用cin.ignore()清掉殘留的換行字元
    int m;
    cin >> m;
    cout<<"cin>>讀到的數字: "<< m <<endl;

    cin.ignore();  // 忽略緩衝區中的下一個字元(也就是那個殘留的'\n')
    string next_line;
    getline(cin, next_line);
    cout<<"清掉殘留換行後getline，得到: "<< next_line <<endl;
    /*
    輸入:
    42
    Hello after ignore
    輸出:
    cin>>讀到的數字: 42
    清掉殘留換行後getline，得到: Hello after ignore
    */


    cout<<("======================\n");// 分隔線


    // 3. getline(ss, token, delim)：搭配stringstream使用，以「自訂分隔符號」切割字串
    // 這正是練習題中用來切割"姓名,國文,英文,數學"、"學生1;學生2;..."的作法
    string data = "apple,banana,cherry";
    stringstream ss(data);
    string token;
    while (getline(ss, token, ',')){  // 每次呼叫getline，讀到下一個','之前的內容
        cout<< token << " | ";
    }
    cout<<endl;
    // 輸出: apple | banana | cherry | 
}
}


// 本篇筆記參考 cppreference std::basic_string (https://en.cppreference.com/w/cpp/string/basic_string)
// Generated by Claude 2026/8/6 (https://claude.ai/share/25b24c3f-c3cb-4636-96b6-ccaf36090a34)