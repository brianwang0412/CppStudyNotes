#include<iostream>
using namespace std;

int main(){
//《一維動態陣列》
    int *arr = new int[5]; //arr是pointer(int*)
    for (int i=0;i<5;i++){
        *(arr+i) = i+1;  //將陣列初始化為 1 2 3 4 5
    }
    
    for (int i=0;i<5;i++){
        cout << *(arr+i)<<' ';
    }
    //輸出: 1 2 3 4 5

    //釋出記憶體
    delete[] arr;
    arr = nullptr;

cout<<"\n\n=================="<<"\n\n";//分隔線==========================================

//《2. 二維動態陣列》

    int rows = 4, columns = 2;  //要建立一個大小為4*2的動態陣列(4列*2行)

    //建立第一維
    int **table = new int*[rows]; //先建立一維
    //table是一個pointer-to-pointer，它指向一個「放著多個 int*（每一行的起始位址）」的陣列

    //對於每一列，建立第二維
    int num=1;
    for (int i=0;i<rows;i++){  //建立每一列有幾行
        table[i] = new int[columns];
        
        //將陣列的值設為1,2,3,4...
        for (int j=0;j<columns;j++){
            table[i][j]=num;
            num++;
        }
    }

    //輸出
    for (int i=0;i<rows;i++){
        for (int j=0;j<columns;j++){
            cout<<table[i][j]<<' '; //跟一般的二維陣列Array[rows][columns]一樣用法，差別只在定義動態陣列與釋出記憶體的部分
            //table[i][j] 等同於 *(*(table+i)+j)
        }
        cout<<endl;
    }
    /*
    輸出: 
    1 2 
    3 4 
    5 6 
    7 8
    */

    //刪除(釋放記憶體)
    for (int i=0;i<rows;i++){
        delete[] table[i];  //先釋出每一列
    }

    delete[] table; //再釋出整個陣列

    table = nullptr;
}

//本篇筆記參考嘉義大學資訊工程學系許政穆老師的授課內容與講義
//Created by B.J.Wang 2025/12/11