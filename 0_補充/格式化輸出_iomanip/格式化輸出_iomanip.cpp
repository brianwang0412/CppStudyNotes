#include<iostream>
#include<iomanip>
using namespace std;

int main(){
    //《setw: 設定欄位寬度、左右對齊、填充空格》
    cout <<'['<< setw(8) << right << 123 << 22 <<']'<< endl; //輸出: [     12322]
    cout <<'['<< setw(8) << left << 123 << 22 <<']'<< endl;  //輸出: [123     22]
    cout <<'['<< setw(8) << setfill('A')<< left << 123 << 22 <<']'<<endl; //輸出: [123AAAAA22]
    cout<<setfill(' '); //改回預設的setfill(' ')
    /*
    setw(8): 讓「下一個」輸出的項目佔8格
    right/left: 讓「下一個」輸出的項目靠右/左對齊
    setfill('A'): 當setw(8)時，若下一個輸出的項目少於8，會自動以空格補齊，現在改以'A'補齊
    注意!! setfill('A')後，之後的每個setw()的補齊都會用'A'，並非限定下一個輸出項目
    記得改回setfill(' ')
    
    程式分解
    cout 
    <<'['
    << setw(8) << right << 123 
    << 22 
    <<']'
    << endl;
    */

    cout<<"=================="<<'\n';//分隔線


    //《setprecision / fixed / scientific: 設定浮點數格式》
    double x=123.456789; //float佔4bytes，double佔8bytes
    cout << "defaultfloat: " << defaultfloat << x <<endl;
    //輸出: 123.457
    cout << "defaultfloat, precision(5): " << defaultfloat << setprecision(5)  << x <<endl; 
    //輸出: defaultfloat, precision(5): 123.46
    cout << "fixed, precision(5): " << fixed << setprecision(5) << x <<endl; 
    //輸出: fixed, precision(5): 123.45679
    cout << "scientific, precision(5): " << scientific << setprecision(5) << x <<endl; 
    //輸出: scientific, precision(5): 1.23457e+002
    cout << defaultfloat; //改回預設的defaultfloat
    /*
    defaultfloat: 預設，若數字太大會自動轉換為科學記號，不特別設定的話輸出會四捨五入到小數點第三位
    fixed: 固定以小數點的方式表達
    scientific: 固定以科學記號的方式表達，數字部分:1.23457，指數部分:e+002(二次方)
    setprecision(5):
    若為defaultfloat，則代表「由左至右取5位數字」，即123.45，然後四捨五入到最後一位，結果為123.46
    若為fixed或scientific，則代表「取到小數點後5位」，即123.45678與1.23456e+002，四捨五入:123.45679與1.23457e+002
    */
    
    cout<<"=================="<<'\n';//分隔線


    //《showpoint: 即使小數為0也顯示小數點》
    double y=10.0;
    cout << "no showpoint: " << y <<endl; //輸出: no showpoint: 10
    cout << "showpoint: " << showpoint << y <<endl; //輸出: showpoint: 10.000
    cout << noshowpoint; //改回預設的noshowpoint
    //showpoint: 即使浮點數的小數部分為零，也要顯示小數點與尾隨的零

    cout<<"=================="<<'\n';//分隔線


    //《showpos: 顯示正負號》
    cout << showpos << 42 << " " << -42 <<endl; //輸出: +42 -42
    cout << noshowpos; //改回預設的noshowpos

    cout<<"=================="<<'\n';//分隔線


    //《uppercase，十六進位、科學記號中的英文變大寫》
    cout << "uppercase: " << uppercase << scientific << 12345.0 <<endl; //輸出: 1.23450E+004
    cout << "nouppercase: " << nouppercase << scientific << 12345.0 <<endl; //輸出: 1.23450e+004
    cout << uppercase << 'a' <<endl; //輸出: a，因為'a'並非數字，所以無效
    cout << nouppercase <<endl; //改回預設的nouppercase
    //uppercase: 讓「數字」中的英文變為大寫，Q:什麼時候數字會出現英文? A:使用十六進位、科學記號時
    
    cout<<"=================="<<'\n';//分隔線


    //《showbase: 顯示進位的前綴》
    int n=255;
    cout << "showbase\n" << showbase; //顯示前綴
    cout << "dec: " << dec << n <<endl; //輸出: dec: 255
    cout << "oct: " << oct << n <<endl; //輸出: oct: 0377
    cout << "hex: " << hex << n <<endl; //輸出: hex: 0xff

    cout << "noshowbase\n" << noshowbase; //不顯示前綴
    cout << "dec: " << dec << n <<endl; //輸出: dec: 255
    cout << "oct: " << oct << n <<endl; //輸出: oct: 377
    cout << "hex: " << hex << n <<endl; //輸出: hex: ff
    cout << dec; //改回預設的十進位dec
    /*
    showbase: 顯示進位的前綴字元
    dec，十進位，沒有前綴字元
    oct，八進位，前綴字元: 0
    hex，十六進位，前綴字元: 0x
    <iomanip>沒有定義二進位
    */

    cout<<"=================="<<'\n';//分隔線


    //《boolalpha: true or false, noboolalpha: 1 or 0》
    cout << boolalpha << true << " or " << false <<endl; //輸出: true or false
    cout << noboolalpha <<  true << " or " << false <<endl; //輸出: 1 or 0
    cout << noboolalpha; //改回預設的noboolalpha
    //boolalpha: true or false
    //noboolalpha: 1 or 0

    cout<<"=================="<<'\n';//分隔線


    //《表格排版，<iomanip>的應用》
    //目錄: 品項、數量、價格
    cout << left << setw(12) << "Item"
         << right << setw(8) << "Qty"
         << right << setw(12) << "Price" <<endl;
    cout << setfill('-') << setw(32) << "-" << endl <<setfill(' '); //目錄與品項的分隔線
    //品項1:水
    cout << left << setw(12) << "Water"
         << right << setw(8) << 3
         << right << setw(12) << fixed << setprecision(2) << 25.0 <<endl;
    //品項2:果汁
    cout << left << setw(12) << "Juice"
         << right << setw(8) << 12
         << right << setw(12) << 5.5 <<endl; 
    cout << defaultfloat; //改回預設的defaultfloat
    /*
    輸出:
    Item             Qty       Price
    --------------------------------
    Water              3       25.00
    Juice             12        5.50
    */

    cout<<"=================="<<'\n';//分隔線


    //《internal，將符號與數字分開，符號靠左，數字靠右》
    cout << internal << setw(8) << setfill('_') << -123 <<endl; //輸出: -____123
    cout << internal << setw(8) << setfill('_') << hex << showbase << 123 <<endl; //輸出: 0x____7b
    cout << right << setfill(' ') << dec << noshowbase; //改回預設

    return 0;
}

//本篇筆記參考嘉義大學資訊工程學系許政穆老師的授課內容與講義
//本篇筆記參考ChatGPT
//Created by B.J.Wang 2025/10/13