#include<iostream>
#include<iomanip>
using namespace std;

int main(){
    //二維陣列
    //語法:資料型別 陣列名稱[長度1][長度2]

    //範例一(基本語法)
    int A1[2][2]; //創建一個二維陣列A1，資料型別為int，大小為2*2
    //這樣我們就建立了一個2*2的矩陣，可以用來儲存4個整數


    //範例二(指定初始值)
    int A2[2][2]={{1,11},{2,22}}; //創建一個二維陣列A2，資料型別為int，大小為2*2，並指定其初始值
    //我現在要找到A2中的11這個元素並輸出
    cout << A2[0][1]<<endl; //輸出: 11
    /*
    還記得索引值index嗎 -> 我們會用index來存取陣列中特定的元素，索引值是從零開始，index=0,1,2...
    在A2這個陣列的第一維中:
    A2[0]代表的是A2的第一個元素，即{1,11}
    A2[1]代表的是A2的第二個元素，即{2,22}
    進入第二維
    A2[0][0]代表的是{1,11}的第一個元素，即 1
    A2[0][1]代表的是{1,11}的第二個元素，即 11
    */
    /*
    其他創建陣列的方法
    int Array1[][2]={{0,1},{2,3}} 
    可以不給第一維的長度，電腦會自動依據初始值的數量設定陣列長度
    如Array1，給定初始值0,1,2,3，共四個數，電腦自動設定陣列長度為4

    錯誤範例: int Array[2][]={{1,2},{3,4}};
    一定要給第二維的長度!!
    
    int Array2[2][2]={{1,2},{3}};
    在Array2[1]中，設定其長度為2，但僅給1個初始值，則剩下的元素會自動設為0
    Array2[0][0]=1, Array2[0][1]=2, Array2[1][0]=0, Array2[1][1]=0
    */

    cout<<"=================="<<'\n';//分隔線

    //範例三(更改元素值)
    int A3[2][3]={{1,2,3},{11,22,33}}; //建立一個二維陣列A3，資料型別為int，大小為2*3
    for (int i=0;i<2;i++) for (int j=0;j<3;j++) cout << A3[i][j] << ' '; //用for迴圈依序輸出每個元素
    //輸出: 1 2 3 11 22 33
    cout <<endl; //換行

    A3[0][2]=100; //A3={{1,2,3},{11,22,33}}，A3[0]={1,2,3}，A3[0][2]=3，我把這個3改成100
    A3[1][1]=777; //A3={{1,2,3},{11,22,33}}，A3[1]={11,22,33}，A3[1][1]=22，我把這個22改成777
    for (int i=0;i<2;i++) for (int j=0;j<3;j++) cout << A3[i][j] << ' '; //用for迴圈依序輸出每個元素
    //輸出: 1 2 100 11 777 33 

    cout<<"\n=================="<<'\n';//分隔線

    //範例四(輸入與輸出)
    int A4[2][2]={0}; //建立一個二維陣列A4，資料型別為int，大小為2*2，並將所有元素值初始化為0
    cout << "Please input 4 numbers>> ";
    cin >> A4[0][0] >> A4[0][1] >> A4[1][0] >> A4[1][1]; //將輸入的數字依序存入陣列中
    for (int i=0;i<2;i++){
        for (int j=0;j<2;j++) cout << setw(4) << setfill('_') << A4[i][j];
    }
    /*
    輸入與輸出:
    Please input 4 numbers>> 1 2 3 4
    ___1___2___3___4
    */


    //範例五(用迴圈存取陣列)
    int rows,columns; //row:行，column:列
    //自訂陣列大小
    cout << "How many rows does this array have?>> ";
    cin >> rows;
    cout << "How many columns does this array have?>> ";
    cin >> columns;
    int A5[rows][columns];

    //將1~(rows*columns)依序放入A5中
    int num=1;
    for (int i=0;i<rows;i++){
        for (int j=0;j<columns;j++){
            A5[i][j]=num;
            num++;
        }
    }

    //輸出陣列內容
    //(用來排版的東西不重要，重點是雙重迴圈和輸出二維陣列內的元素)
    cout <<"{ ";
    for (int i=0;i<rows;i++){
        cout << "{ ";
        for (int j=0;j<columns;j++) cout << A5[i][j] << ' ';
        cout << "}";
        if (i!=rows-1) cout <<", ";
    }
    cout <<" }"<<endl;

    /*
    輸入與輸出
    How many rows does this array have?>> 3
    How many columns does this array have?>> 2
    { { 1 2 }, { 3 4 }, { 5 6 } }
    */
    //這是一個3*2的陣列，我將1~6依序放進陣列中，並輸出

    return 0;
}

//本篇筆記參考《徹底研究最新C++物件導向程式設計實例》P6-9~6-18
//Created by B.J.Wang 2025/10/16