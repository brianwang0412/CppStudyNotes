#include<iostream>
using namespace std;

/*
Q: 什麼時候需要使用new?
A:  1. 當你不確定一個陣列的大小時。(int *arr = new int[N]; N在編譯時不確定，等待輸入)
    2. 需要使一個變數的生命週期能跨越函式範圍
    3. 可用來實作如 linked-list, trees 等這些資料結構。
    4. 於需要高效率的記憶體管理的複雜程式當中。

Q: new的運作原理為何?
A: new會在Heap區域找到一塊足夠大的空間建立物件，並回傳該空間的記憶體位置
    注意: Heap的空間是有限的，所以在使用完物件後要用delete釋放空間，並把原本的指標設為nullptr，避免指標亂指
*/

/*
疑問:
我在程式執行時輸入一個數字N
要用這個N來當作陣列的長度
我之前用 int arr[N]; 也沒錯過啊
為什麼現在說要用 int *arr = new int[N];

解答:
在「標準C++」中寫 int arr[N]; 是會報錯的
能用是因為我們的GCC等編譯器默認支援VLA(可變長度陣列)
要用的話還是 int *arr = new int[N]; 更安全
*/

int main(){
//《1. new 與 delete》

    //有new就要有delete，避免Memory Leak
    //delete後立即將指標設為nullptr

    int *ptr = new int;  //使用new動態配置一個int的空間，並用指標ptr將這個空間的記憶體位址儲存起來

    //存入數值
    *ptr = 100;
    cout<<"address : "<<ptr<<endl; //address : 0x1121858
    cout<<"value : "<<*ptr<<endl;  //value : 100

    //釋放記憶體
    delete ptr;
    ptr=nullptr;

    cout<<"\n=================="<<"\n\n";//分隔線==========================================

//《2. new[] 配置動態陣列》

    int size;
    cout<<"Input the size of an array>> ";
    cin>>size; //輸入: 5

    int *arr = new int[size]; //用new動態配置size個int大小的連續記憶體空間，並用指標arr將這個空間的起始位置儲存起來

    int num;
    cout<<"Input numbers"<<endl;
    for (int i=0;i<size;i++){
        cin>>num; //輸入: 1 2 3 4 5
        *(arr+i) = num;
    }

    for (int i=0;i<size;i++) 
        cout<<*(arr+i)<<' '; 
    //輸出: 1 2 3 4 5

    cout<<"\nsizeof(arr) = "<<sizeof(arr)<<endl;  //輸出: sizeof(arr) = 4
    //sizeof(arr)指的是指向陣列開頭的「指標的大小」

    //釋放記憶體
    //期末考必考!!
    delete[] arr; //注意不要寫成 delete arr;
    arr = nullptr;

    return 0;
}

//本篇筆記參考嘉義大學資訊工程學系許政穆老師的授課內容與講義
//本篇筆記參考【C++ 筆記】動態記憶體（new / delete） - part 29 by Luke Tseng on hackmd
//https://hackmd.io/@LukeTseng/BJWlObgHxg#%E5%8B%95%E6%85%8B%E8%A8%98%E6%86%B6%E9%AB%94%EF%BC%88Dynamic-Memory%EF%BC%89
//Created by B.J.Wang 2025/12/11