#include<iostream>
using namespace std;

//《指標應用1: 利用指標在自訂函式中操作變數/陣列》


//求立方，傳入值n為變數值
int Cube1_CallByValue(int n){ 
    return n*n*n; //回傳結果，不會改寫原本的元素值
}       


//求立方，傳入值n為指標
void Cube2_CallByReference(int* n){ 
    *n = (*n)*(*n)*(*n);
    //不回傳值，透過指標改寫元素值
}


//將陣列中的每個元素值+1
void Array_All_Plus_One(int* Array,int size){
    for (int i=0;i<size;i++){
        *(Array+i) = *(Array+i) + 1;  //利用指標改寫陣列的元素值
    }
}


//輸出陣列中的所有元素
void Output_Array(int* Array, int size){
    for (int i=0;i<size;i++){
        cout << *(Array+i) <<' '; //利用i來遍歷陣列(i=0,1,2,3,4)
    }
    cout<<endl;
}


int main(){
    int n=2;
    cout<<"Cube1_CallByValue(n) = "<< Cube1_CallByValue(n) <<endl;
    cout<<"Now n = "<<n<<endl;
    /*
    Cube1_CallByValue(n) = 8
    Now n = 2  可以看到n的值沒有被變更
    */

    Cube2_CallByReference(&n);
    cout<<"After Cube2_CallByReference(n)\nn = "<< n <<endl;
    /*
    After Cube2_CallByReference(&n)
    n = 8  由於Cube2_CallByReference傳入的是指標(&n)，因此會變更到原本的函數值
    */

    int size=5, Array[size]={1,2,3,4,5};
    Output_Array(Array,size); //這裡的Array代表的是指向Array[0]的指標
    cout<<"Array = "<< Array <<endl; //Array = 0x61fef8
    //1 2 3 4 5

    Array_All_Plus_One(Array,size); //使用指標改變陣列的元素值(全部+1)
    Output_Array(Array,size);
    //2 3 4 5 6
}


//本篇筆記參考嘉義大學資訊工程學系許政穆老師的授課內容與講義
//Created by B.J.Wang 2025/11/28