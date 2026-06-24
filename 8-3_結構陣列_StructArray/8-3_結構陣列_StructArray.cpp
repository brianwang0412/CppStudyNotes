#include<iostream>
using namespace std;

struct Student{ //定義一個結構Student，裡面有兩個元素:ID(學號)跟name(姓名)
    int ID;
    char name[10];
};

//這裡一個Student物件的大小為 16 bytes
//因為int 4 bytes + char 10 bytes = 14 bytes，而編譯器會自動padding為16bytes來提升效率

int main(){
    int n;
    cout<<"How many students in your class>> ";
    cin>>n; //輸入一個班內有幾個學生

    Student *Class_A = new Student[n];
    //建立一個結構陣列Class_A，資料型別為Student，長度為n

    /*注意!!!
    Class_A 是一個指向陣列開頭的指標
    但是
    Class_A[i] 是許多個結構物件，每個都有各自的ID跟name
    */

    for (int i=0;i<n;i++){
        cout<<"Student "<<i+1<<" ID : ";
        cin>>Class_A[i].ID; //輸入第i個學生的學號

        cout<<"Student "<<i+1<<" name : ";
        cin>>Class_A[i].name; //輸入第i個學生的姓名
    }

    for (int i=0;i<n;i++){
        cout<< "Student "<<i+1<<" : "<<Class_A[i].name<<' '<<Class_A[i].ID<<endl;
        cout<< &Class_A[i].ID <<endl; //存放第i個學生的ID的記憶體位址
        cout<< &Class_A[i].name <<endl<<endl; //存放第i個學生的name的記憶體位址
    }

    /*
    輸入:
    How many students in your class>> 3
    Student 1 ID : 1142901
    Student 1 name : ChatGPT
    Student 2 ID : 1142902
    Student 2 name : Gemini
    Student 3 ID : 1142903
    Student 3 name : Grok
    */

    /*
    輸出:
    Student 1 : ChatGPT 1142901
    0x1281718
    0x128171c

    Student 2 : Gemini 1142902
    0x1281728
    0x128172c

    Student 3 : Grok 1142903
    0x1281738
    0x128173c
    */

    delete[] Class_A;
}

//本篇筆記參考ChatGPT
//Created by B.J.Wang 2025/12/31