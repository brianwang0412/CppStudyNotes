#include"CreateAndDestroy.h"
#include<iostream>
#include<string>
using namespace std;


/*
static特性:
1. 不會隨著函數結束被清除
2. 函數再次被調用/宣告，也不會重新初始化
3. 存在直到程式結束
*/


void create(){
    cout << "\nCREATE FUNCTION: EXECUTION BEGINS"<<endl;
    CAD fifth{5, "(local in create)"}; //僅在這個函數內可用，函數結束即清除
    static CAD sixth{6, "(local static in create)"};  //存在直到程式結束
    CAD seventh{7, "(local in create)"};  //僅在這個函數內可用，函數結束即清除
    cout << "\nCREATE FUNCTION: EXECUTION ENDS"<<endl;
}

//建立第一個物件
CAD first{1, "(global before main)"};

int main(){
    cout << "\nMAIN FUNCTION: EXECUTION BEGINS"<<endl;
    CAD second{2, "(local in main)"};
    static CAD third{3, "(local static in main)"};

    create();

    cout << "\nMAIN FUNCTION: EXECUTION RESUMES"<<endl;
    CAD fourth{4, "(local in main)"};
    cout << "\nMAIN FUNCTION: EXECUTION ENDS"<<endl;
    return 0;
}
//程式結束，從最後宣告的物件開始清除，最後才清除static(也是一樣從最後宣告的物件開始清除)