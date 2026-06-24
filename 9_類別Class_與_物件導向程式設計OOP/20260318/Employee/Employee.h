#include<string>
using namespace std;

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee{
    private:
        string firstName;
        string lastName;

        static unsigned int count;

    public:
        Employee();
        Employee(const string&, const string&);
        ~Employee();

        string getFirstName() const;
        string getLastName() const;

        static unsigned int getCount();

        Employee& setFirstName(const string& first);
        Employee& setLastName(const string& last);
        /*
        Setter 函式：回傳 Employee& 以支援串接式呼叫 (Cascaded Calls)

        Employee: 類別名稱
        &: 這是「引用」符號。在回傳型別中，它代表函式執行完後，回傳的是物件本身，而不是物件的副本。

        Employee: 
        
        傳值 (Value)	    Employee setFirstName(...)	系統會把物件完整複製一份再回傳。這會浪費記憶體，且後續的操作是在副本上，不是在原物件上。
        傳引用 (Reference)	Employee& setFirstName(...)	系統直接回傳原本那個物件的記憶體位置。沒有複製動作，效能極高，且「所有改動都發生在同一個物件上」。
        */

        /*
        如果沒有 Employee&，你要寫三行：
        emp.setFirstName("Brian");
        emp.setLastName("Wang");
        emp.setID(101);

        有了 Employee&，你可以寫成一行：
        emp.setFirstName("Brian").setLastName("Wang").setID(101);
        */
};

#endif