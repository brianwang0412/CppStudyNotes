#include<iomanip>
#include"PhoneNumber.h"
using namespace std;

ostream& operator<<(ostream& output, const PhoneNumber& number){
    output<< "Area code: "<< number.areaCode
          << "\nExchange: "<< number.exchange
          << "\nLine: "<< number.line
          << "\n(" << number.areaCode << ") "
          <<number.exchange << "-" << number.line << "\n";
    return output;
}

istream& operator>>(istream& input, PhoneNumber& number){
    //  istream& ignore(streamsize n = 1, int_type delim = EOF)
    //  跳過n個字元
    input.ignore(); //ignore(1)
    input >> setw(3) >> number.areaCode;
    input.ignore(2);
    input >> setw(3) >> number.exchange;
    input.ignore();
    input >> setw(4) >> number.line;
    return input;
}

//cout << 10; 時，編譯器內部其實是在呼叫 cout.operator<<(10);

