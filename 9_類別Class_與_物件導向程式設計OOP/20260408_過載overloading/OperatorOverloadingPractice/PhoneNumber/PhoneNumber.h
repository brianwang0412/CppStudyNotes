#ifndef PHONENUMBER_H
#define PHONENUMBER_H

#include<iostream>
#include<string>
using namespace std;

class PhoneNumber{
    friend ostream& operator<<(ostream&, const PhoneNumber&);
    friend istream& operator>>(istream&, PhoneNumber&);

    private:
        string areaCode;
        string exchange;
        string line;
};



#endif

/*
成員函數（Member Function）： 
屬於類別的一部分，調用時必須透過物件（如 obj.func()），實作時需要 ClassName::

友元函數（Friend Function）： 
它是外部的普通函數，並非類別的成員。
friend 關鍵字只是在告訴類別：「請允許這個外部函數存取我的 private 成員。」
*/