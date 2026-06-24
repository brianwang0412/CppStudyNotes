#include <iostream>
#include <iterator> // ostream_iterator and istream_iterator
using namespace std;

int main() {
   cout << "Enter two integers: ";

   // create istream_iterator for reading int values from cin   
   istream_iterator<int> inputInt = cin;

   int number1 = *inputInt; // read int from standard input
   cout<<number1<<endl;
   ++inputInt; // move iterator to next input value
   cout<<*inputInt;
   int number2 = *inputInt; // read int from standard input
   cout<<number2<<endl;

   // create ostream_iterator for writing int values to cout
   ostream_iterator<int> outputInt = cout;

   cout << "The sum is: ";
   *outputInt = number1 + number2; // output result to cout
}

// 額外參考 : https://hackmd.io/@LukeTseng/BkLL3USVex

/*Gemini解釋
INPUT
初始化（綁定 cin）： istream_iterator<int> inputInt = cin; 這行程式碼將迭代器 inputInt 與標準輸入串流 cin 綁定。此時，迭代器會立刻嘗試從 cin 讀取第一個整數。這意味著程式執行到這裡時，就會暫停並等待使用者輸入。

解引用 *inputInt（獲取資料）：
在 C++ 的迭代器概念中，*（解引用）代表「取出目前位置的值」。在這裡，*inputInt 就等於把你剛剛從 cin 輸入的第一個整數取出來，並賦值給 number1。

遞增操作 ++inputInt（前進到下一個數據）：
平常我們對指標或動態陣列迭代器做 ++，是指向記憶體的下一個位置。但對 istream_iterator 做 ++，它的底層行為是再次呼叫 cin >> ...，讓串流讀取下一個由空格或換行分隔的整數。

再次解引用：
number2 = *inputInt; 則是把剛剛 ++ 讀進來的第二個整數取出來。

OUTPUT
初始化（綁定 cout）：
ostream_iterator<int> outputInt = cout; 將迭代器與標準輸出串流 cout 綁定。這代表任何被塞進這個迭代器的資料，都會被送到螢幕上顯示。

指派值 *outputInt = ...（觸發輸出）：
對 ostream_iterator 進行解引用並賦值（*iterator = value），在底層會被轉換為 cout << value 的操作。因此，當執行 *outputInt = number1 + number2; 時，計算結果就會立刻被印在螢幕上。
*/