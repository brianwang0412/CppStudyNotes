#include<iostream>
using namespace std;

int main(){
    int row=4,col=2;
    int **table = new int*[row];

    for  (int i=0;i<row;i++){
        table[i] = new int[col];
        table[i][0] = 1;
        table[i][1] = 2;
    }

    for (int i=0;i<4;i++){
        for (int j=0;j<2;j++){
            cout<<*(*(table+i)+j)<<' '; //跟一般的二維陣列Array[row][col]一樣用法，差別只在定義動態陣列與釋出記憶體的部分
        }
        cout<<endl;
    }


}