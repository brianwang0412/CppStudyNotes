#include<iostream>
#include<string>
using namespace std;


//建立一個結構，名稱為people，內有birth與name兩個變數，用來儲存出生年份與名字
struct people{
    int birth;
    string name;
};

int main(){
    struct people P1; //建立一個物件P1，資料型態為people
    P1.birth = 2025;
    P1.name = "Steve";

    cout<< P1.name << ' ' << P1.birth <<endl;
    //輸出: Steve 2025

    cout<<"=================="<<"\n";//分隔線

    struct people *P2 = new people; //用new動態配置一個people大小的記憶體空間，並將這個空間的位址賦予給P2這個指標
    //因為P2是結構指標，不像P1是結構物件
    //所以在存取時，不能用 P2.birth，要改成使用 P2->birth 或者 (*P2).birth

    //ptr->name 等效於 (*ptr).name

    P2->birth = 2007;
    (*P2).name = "Brian";



    cout<< (*P2).name << ' ' << P2->birth <<endl;
    //輸出: Brian 2007
}

//Created by B.J.Wang 2025/12/17