#include<iostream>
using namespace std;

int main(){
    /*
    if (條件){
        程式敘述A;
    }
    else{
        程式敘述B;
    }

    如果條件成立(=true)，就執行 程式敘述A 中的程式碼
    否則若條件不成立(=false)，就執行 程式敘述B 中的程式碼
    程式敘述A跟B 同時只會有一個被執行，不會出現 程式敘述A,B 都被執行的情況
    */

    //範例一
    int x;
    cout << "Please input a number>> ";
    cin >> x;
    if (x>1){
        cout << "Your number is bigger than 1\n";
    }
    /*
    實際輸入與輸出:
    Please input a number>> 35
    Your number is bigger than 1
    */

    //補充:因為大括號內只有一行程式，因此可將大括號省略，如下
    // if (x>1) cout<<"Your...than 1\n";

    cout<<"=================="<<'\n';//分隔線

    /*
    if (條件一){
        程式敘述A;
    }
    else{
        if (條件二){
            程式敘述B;
        }
        else{
            程式敘述C;
        }
    }

    如果條件一成立，就執行 程式敘述A
    否則若條件一不成立，則進入else，執行裡面的程式碼:
        如果條件二成立，就執行 程式敘述B
        否則若條件二不成立，則執行 程式敘述C
    */

    //範例二
    int y;
    cout << "Please input a number>> ";
    cin >> y;
    if (y<=0) cout << "Your number is smaller than 0\n";
    else {
        if (y>=10) cout << "Your number is bigger than 10\n";
        else {
            cout << "Your number is smaller than 10\n";
            cout << "Your number is bigger than 0\n";
        }
    }
    /*
    實際輸入與輸出:
    Please input a number>> 99
    Your number is bigger than 10
    */

    cout<<"=================="<<'\n';//分隔線

    /*
    if (條件一){
        程式敘述A;
    }
    else if (條件二){
        程式敘述B;
    }
    else{
        程式敘述C;
    }

    else if (條件二) 為以下的簡寫
    =============
    else{
        if (條件二)
    }
    =============
    其中，else if可以放很多個，見範例三
    */
   
    //範例三
    int ans;
    cout <<"1. Hamburger\n";
    cout <<"2. French Fries\n";
    cout <<"3. Chicken Rice\n";
    cout <<"Choose one food>> ";
    cin >> ans;
    cout <<"You input "<<ans<<'\n';
    if (ans == 1) cout<<"Here is your Hamburger. :)\n";
    else if (ans == 2) cout<<"Here is your French Fries. :)\n";
    else if (ans == 3) cout<<"Here is your Chicken Rice. :)\n";
    else cout<<"No this food. :(\n";
    /*
    實際輸入與輸出:
    1. Hamburger
    2. French Fries
    3. Chicken Rice
    Choose one food>> 3
    You input 3
    Here is your Chicken Rice. :)
    */

    return 0;
}


//本篇筆記參考《徹底研究最新C++物件導向程式設計實例》4-1~4-22
//Create by B.J.Wang 2025/9/23