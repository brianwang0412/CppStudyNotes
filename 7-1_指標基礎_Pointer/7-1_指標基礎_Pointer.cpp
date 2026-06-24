#include<iostream>
using namespace std;

int main(){
    //不管是指向什麼型態的指標，其大小皆為4 byte
    // 1.《定義一個指標變數》

    //指標變數: 專門用來儲存一個變數的記憶體位置 的變數
    //語法: 「想指向的變數」的資料型態 *指標變數名稱;
    //      DataType *Name;
    
    int *pointer1; 
    //建立一個指標變數，名稱為pointer，它可以用來儲存一個int變數的位址
    //即可以用來「指向」一個int變數
    
    int *pointer2 = nullptr;
    //可以先將指標的值設為nullptr,NULL或0，之後再賦予變數位址

//======================================分隔線=========================================
{

    // 2.《取址運算子「&」與 間接取值運算子「*」》

    //取址運算子「&」: 用來取得一個「變數」的「記憶體位址」   (address-of operator)
    //間接取值運算子「*」: 用來提取一個「記憶體位址」儲存的「值」 (indirection operator)

    int num=12345;
    //使用 & 取得num的記憶體位址
    cout<< &num <<endl; //輸出: 0x61ff04，由此可得知num存在記憶體中的位址為0x61ff04

    int *ptr = &num; //定義一個指標變數ptr來儲存num的記憶體位置

    cout<< ptr <<endl; //輸出: 0x61ff04
    //代表我們成功用「指標變數ptr」將「num的記憶體位址」儲存起來了
    //現在ptr的「值」就是num的「記憶體位址」
    //ptr = 0x61ff04

    cout<< *ptr <<endl; //輸出: 12345
    //透過間接取值運算子「*」，我們成功提取出「ptr指向的記憶體位址」儲存的「值」
    //這裡的 *ptr 代表的是儲存在 0x61ff04 裡的值，也就是12345

}
cout<<"\n=================="<<"\n\n";//分隔線==========================================
{

    // 3.《依址操作》

    float num = 3.14;
    cout<<"value of num : "<< num <<endl;    //輸出: value of num : 3.14
    cout<<"address of num : "<< &num <<endl; //輸出: address of num : 0x61ff00

    float *ptr; //先建立一個指向float的指標變數 ptr
    ptr = &num; //將ptr的值改為num的記憶體位址

    cout<<"\nvalue of ptr : "<< ptr <<endl;  //輸出: value of ptr : 0x61ff00
    cout<<"address of ptr : "<< &ptr <<endl; //輸出: address of ptr : 0x61fefc

    //開始依址操作: 利用*ptr「間接修改」num的值
    *ptr = *ptr + 3330;
    //等同於 num = num + 3330;

    cout<<"\nAfter"<<endl;
    cout<<"num = "<< num <<endl;   //輸出: num = 3333.14
    cout<<"*ptr = "<< *ptr <<endl; //輸出: *ptr = 3333.14

}
cout<<"\n=================="<<"\n\n";//分隔線==========================================
{

    // 4.《用指標存取陣列》
    int Array[5]={10,20,30,40,50};
    //注意: 陣列的名稱會自動退化成指標，並「指向陣列的第一個元素」
    
    //比較記憶體位置
    cout<<"Array = "<< Array <<endl; //輸出: Array = 0x61fee0
    cout<<"&Array[0] = "<< &Array[0] <<endl; //輸出: &Array[0] = 0x61fee0

    //比較儲存的值
    cout<<"*Array = Array[0] = "<< *Array <<endl; //輸出: *Array = Array[0] = 10


    int *ptr=Array;
    //注意!! 對指標變數做加減法時，要考慮到它是指向什麼型態的指標變數
    //如Array是int，ptr是指向整數變數的指標
    //每個int佔4bytes，所以ptr+1不是0x61fee1，而是0x61fee4
    cout << ptr <<endl;   //輸出: 0x61fee0
    cout << ptr+1 <<endl; //輸出: 0x61fee4
    //更多可參考《0_補充 - sizeof_variables》


    //利用offset來遍歷陣列({10,20,30,40,50})
    for (int offset=0 ; offset<5 ; offset++){
        cout<<"offset = "<<offset<<" , ";
        cout<<"(ptr + offset) = " << ptr + offset<<" , ";
        cout<<"*(ptr + offset) = " << *(ptr + offset) << endl;
        
    }
    /*
    輸出:
    offset = 0 , (ptr + offset) = 0x61fee0 , *(ptr + offset) = 10
    offset = 1 , (ptr + offset) = 0x61fee4 , *(ptr + offset) = 20
    offset = 2 , (ptr + offset) = 0x61fee8 , *(ptr + offset) = 30
    offset = 3 , (ptr + offset) = 0x61feec , *(ptr + offset) = 40
    offset = 4 , (ptr + offset) = 0x61fef0 , *(ptr + offset) = 50
    */
}
}

//本篇筆記參考《C&C++完美經典》7-10~7-18
//本篇筆記參考嘉義大學資訊工程學系許政穆老師的授課內容與講義
//Created by B.J.Wang 2025/11/27