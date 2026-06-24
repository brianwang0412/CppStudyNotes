#include <iostream>
#include <string>
using namespace std;

class Phone {
private:
    string areaCode;   // 3 digits
    string exchange;   // 3 digits
    string line;       // 4 digits

    bool isAllDigits(const string& s) const {
        for (int i = 0; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9') {
                return false;
            }
        }
        return true;
    }

public:
    Phone();
    Phone(string a, string e, string l);
    string getAreaCode() const;
    string getExchange() const;
    string getLine() const;
    void setAreaCode(string a);
    void setExchange(string e);
    void setLine(string l);

    // friend operator overloading
    friend istream& operator >>(istream& input, Phone& p);
    friend ostream& operator<<(ostream& output, const Phone& p);
};

Phone::Phone() {
    areaCode = "000";
    exchange = "000";
    line = "0000";
}

Phone::Phone(string a, string e, string l) {
    setAreaCode(a);
    setExchange(e);
    setLine(l);
}

string Phone::getAreaCode() const {
    return areaCode;
}

string Phone::getExchange() const {
    return exchange;
}

string Phone::getLine() const {
    return line;
}

void Phone::setAreaCode(string a) {
    if (a.length() == 3 && isAllDigits(a)) {
        areaCode = a;
    } else {
        areaCode = "000";
    }
}

void Phone::setExchange(string e) {
    if (e.length() == 3 && isAllDigits(e)) {
        exchange = e;
    } else {
        exchange = "000";
    }
}

void Phone::setLine(string l) {
    if (l.length() == 4 && isAllDigits(l)) {
        line = l;
    } else {
        line = "0000";
    }
}

// 作答區起始

#include<iomanip>
istream& operator>>(istream& input, Phone& p){
    input>>ws;
    input.ignore(1);
    string s;
    
    input>>setw(3)>>s;
    p.setAreaCode(s);
    
    input.ignore(2);
    input>>setw(3)>>s;
    p.setExchange(s);
    
    input.ignore(1);
    input>>s;
    p.setLine(s);
    
    return input;
}

// (123) 456-7890

ostream& operator<<(ostream& output, const Phone& p){
    cout<<'('<<p.areaCode<<") "<<p.exchange<<'-'<<p.line;
    return output;
}

// 作答區結束

// main function
int main() {

    Phone p1;
    string strarea, strexchange, strline ;
    cin >> strarea >> strexchange >> strline ;
    Phone p2(strarea, strexchange, strline);

    Phone userPhone;
    cin >> userPhone; 
    cout << p1 << endl;
    cout << p2 << endl;
    cout << userPhone ;

    return 0;
}

// 本篇筆記為嘉義大學資訊工程學系物件導向程式設計之課堂題目
// //Created by B.J.Wang 20260609