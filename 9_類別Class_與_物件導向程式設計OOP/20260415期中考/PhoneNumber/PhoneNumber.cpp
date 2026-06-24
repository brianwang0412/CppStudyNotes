#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

//類別定義
class PhoneNumber{
    friend istream& operator>>(istream& input, PhoneNumber& number);
    friend ostream& operator<<(ostream& output, const PhoneNumber& number);

    private:
        string areaCode;
        string exchange;
        string line;

    public:
        PhoneNumber(){}
        PhoneNumber(string A, string B, string C):areaCode{A},exchange{B},line{C}{}

        void setAreaCode(string s){areaCode=s;}
        void setExchange(string s){exchange=s;}
        void setLine(string s){line=s;}

        string setAreaCode(){return areaCode;}
        string setExchange(){return exchange;}
        string setLine(){return line;}
};



//確認該areaCode, exchange, line是否正常
bool CheckTool(string s, int Len){
    for (int i=0; i<Len; ++i){
        if (!(s[i]>='0' && s[i]<='9')){
            return false;
        }
    }
    return true;  //若都沒問題就回傳true
}


/*
輸入有三種情況
1. areaCode只有兩位數: 讓areaCode,exchange,line都設為0
例如: (02) 123-4567 改為 (000) 000-0000

2. areaCode或exchange或line中任何一個包含「非整數」的字元: 將有異常的部分設為零，無異常則保持原狀
例如: (12c) 246-3579 改為 (000) 246-3579

3. 都正常
例如: (111) 135-1234
*/


//實作運算子過載(輸入)
istream& operator>>(istream& input, PhoneNumber& number){
    input>> ws; // 跳過(忽略)第一個有效輸入前的所有換行(\n)與空格( )
    input.ignore(1); // 忽略areaCode的左括號 (
    input>> setw(3) >> number.areaCode;

    if (number.areaCode[2] == ')'){ // 第一種情況，只有兩位數
        input>>setw(9)>>number.areaCode; 
        //考慮到輸入多支電話號碼的狀況，把後面的號碼都先輸入到areaCode內

        number.areaCode="0";
        number.exchange="0";
        number.line="0";
        return input;
    }
    else if (!CheckTool(number.areaCode,3)){ // 第二種情況，號碼有問題
        number.areaCode="0";
    }
    else // 第三種情況，沒有問題
        ;

    input.ignore(2); // 忽略 右括號跟空格
    input>> setw(3) >> number.exchange;
    if (!CheckTool(number.exchange,3))
        number.exchange="0";

    input.ignore(1); //忽略連字號(-)
    input>> setw(4) >> number.line;
    if (!CheckTool(number.line, 4))
        number.line="0";

    return input;
}

//實作運算子過載(輸出)
ostream& operator<<(ostream& output, const PhoneNumber& number){
    output<< setfill('0')
          << '(' <<setw(3)<< number.areaCode
          << ") " <<setw(3)<< number.exchange
          << '-' <<setw(4)<< number.line;
    return output;
}


int main(){
    PhoneNumber Phone;

    cout<<"Input PhoneNumbers >> ";

    while (cin>>Phone){
        cout<<" Output PhoneNumbers: ";
        cout<<Phone;
        cout<<"\nInput PhoneNumbers >> ";
    }
    return 0;
}

/*
測資1
輸入: (111) 135-1234
輸出: (111) 135-1234

測資2
輸入: (02) 123-4567
輸出: (000) 000-0000

測資3
輸入: (12c) 246-3579
輸出: (000) 246-3579

測資4
輸入: (-23) 123-A567
輸出: (000) 123-0000
*/


//本篇筆記參考嘉義大學114學年度第二學期物件導向程式設計課程內容
//Created by B.J.Wang 2026/4/19
// 20260428 更新