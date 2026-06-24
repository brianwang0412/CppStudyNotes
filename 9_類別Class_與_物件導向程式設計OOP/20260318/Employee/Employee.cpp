#include"Employee.h"
#include<string>
#include<iostream>
using namespace std;

//define and initialize static data member at global namespace scope
unsigned int Employee::count = 0;

Employee::Employee(){};
Employee::Employee(const string& first, const string& last): firstName{first}, lastName{last}{};
Employee::~Employee(){};

string Employee::getFirstName() const{
    return firstName;
};
string Employee::getLastName() const{
    return lastName;
};

unsigned int Employee::getCount(){
    return count;
}

// 實作串接式 Setter
Employee& Employee::setFirstName(const string& first) {
    firstName = first;
    return *this; // 回傳物件本身，才能使用串接式的呼叫，詳情看main.cpp裡面

    // this = 0xe4967ff900 即這個物件的記憶體位置
    // *this = 物件本身，如: MyName2
}

Employee& Employee::setLastName(const string& last) {
    lastName = last;
    return *this; // 回傳物件本身的引用
}

/*關於Employee& 這個回傳值
代表會回傳這個物件「本身」，即*this

它不是位址：雖然底層運作跟指標很像，但在語法上它就代表那個物件。
它不是副本：它不會影印出一份新的物件。

如果你沒加 &（只寫 Employee）：
回傳 *this 時，系統會在那一瞬間影印出一份一模一樣的 emp 副本（假設位址在 0xAAAAA）
然後 .setLastName 會改到那個副本，原本 0xe4967ff900 的名字完全沒變！
*/

/* 關於this
this 是一個指標，指向「目前正在執行這個函式的物件」。
*this 就是把那個指標「解引用」，代表「物件本人」。
*/

/*關於string&
在 C++ 中，如果你寫 setFirstName(string first)（沒有 &），會發生以下過程：

複製 (Copy)：系統會把你傳進去的字串「影印」一份新的，存到參數 first 中。
賦值 (Assign)：再把 first 複製一份給類別成員 firstName。
銷毀：函式結束時，那個暫時影印出來的 first 會被丟掉。

這等於做了兩次影印，非常浪費。


使用 const string& 的好處：
& (引用)：代表「別名」。它告訴編譯器：「直接去讀我原本那個字串的記憶體位址，不要影印！」這樣就省下了第一次影印的時間。
const：因為我們是直接讀取原件，為了怕函式內部不小心改動到原本的字串，加上 const 保證這個字串是「唯讀」的。
*/

/*關於指標跟引用的區別
指標 (const string* first)：這是一個儲存位址的變數。如果你要拿它的內容，你必須手動解參考（使用 *first 或 ->）。
引用 (const string& first)：這是一個別名 (Alias)。一旦繫結了某個物件，它就在語法上「代表」那個物件。

特性	指標 (Pointer)	    引用 (Reference)
宣告	string* ptr	        string& ref
使用時	需手動解參考 *ptr	 直接使用 ref
底層	儲存位址	         儲存位址（但編譯器幫你處理了）
類比	寫著地址的紙條	     人的「綽號」或「分身」
*/