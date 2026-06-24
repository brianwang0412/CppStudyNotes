#ifndef DATE_H
#define DATE_H

#include<array>
#include<iostream>

class Date{
    friend std::ostream& operator<<(std::ostream&, const Date&);

    private:
        unsigned int month;
        unsigned int day;
        unsigned int year;
        
        static const std::array<unsigned int, 13> days;
        void helpIncrement();

    public:
        Date(int m=1, int d=1, int y=1900);
        void setDate(int ,int ,int);
        Date& operator++();   //++a，因為會回傳自己的引用，所以能做到++++a
        Date operator++(int); //a++，int沒有實際用途，只是用來告訴編譯器這是後置版本的標記
        Date& operator+=(unsigned int); //
        static bool leapYear(int);
        bool endOfMonth(int) const;
};

#endif


/*
行為邏輯

++a
1. 直接將物件本身的值加 1。
2. 回傳自己（透過 *this）

a++
1. 先建立一個暫存物件，紀錄「目前的舊值」。
2. 將物件本身加 1。
3. 回傳那個「舊值」的暫存檔。

*/

/*
Q: 編譯器怎麼知道++是在前面還是後面

A:
1. 靠「函數簽名」的不同 (Function Signature)
當編譯器看到 ++ 符號時，它會根據 ++ 相對於變數的位置，去尋找對應的函數定義：

前置 ++d：編譯器會尋找 沒有參數 的版本：
Date& operator++();

後置 d++：編譯器會尋找 帶有一個 int 參數 的版本：
Date operator++(int);

2. 標記參數（Dummy Parameter）
後置版本的 int 參數完全是為了區分定義而存在的。

當你寫下 d++ 時，編譯器在內部其實會偷偷傳入一個數字 0 給這個函數，把它變成像 d.operator++(0)。

這個 int 參數在函數內部不需要有名字（通常直接寫 int 而不寫 int x）。

它的唯一作用就是讓編譯器知道：「喔！這是在處理後置運算，我要呼叫那個有帶 int 的版本。」
*/