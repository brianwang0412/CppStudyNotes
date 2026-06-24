#include<iostream>
using namespace std;

/*
while迴圈與do-while迴圈的差異:
while先判斷運行條件是否成立，若成立則執行迴圈，否則跳出迴圈
do-while先執行程式，再判斷運行條件是否成立，若成立則繼續執行迴圈，否則跳出迴圈
*/

int main(){
    //while迴圈
    /*
    語法
    while (運行條件){
        程式敘述;
    }
    */

    //範例一
    int i=0;
    while (i<5){ //一直執行迴圈「直到i<5不成立」
        cout << i << " ";
        i++;
    }
    //輸出: 0 1 2 3 4

    /*
    程式詳解
    先宣告int i=0;
    進入while迴圈，此時i<5成立，運行程式，輸出i，並讓i++ (i+=1)
    此時i=1，進入下一次迴圈
    
    i=1符合i<5，執行程式...
    .
    .
    .
    執行直到i=5，不符合i<5跳出while迴圈
    */

    cout<<"\n=================="<<'\n';//分隔線

    //do-while迴圈
    /*
    語法
    do{
        程式敘述;
    }while(運行條件);
    */

    //範例二
    int j=666;
    do{
        cout << "hello" << endl;
    }while (j<5);
    //輸出: hello

    /*
    程式詳解
    先執行cout << "hello" << endl;
    再判斷j<5是否成立-> j=666，j<5不成立，跳出迴圈
    */

    return 0;
}
//Create by B.J.Wang 2025/10/2