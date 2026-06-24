#include<iostream>
#include<cstring>
using namespace std;

int main(){
    char s[101];
    cout << "Enter a string>> ";
    cin.getline(s,101); 
    //cin.getline(字元陣列, 可讀取的最大長度);
    //專門用於C-style string的char[]

    int L=strlen(s); //strlen定義在<cstring>中

    for (int i=0,j=L-1 ; i<j ; i++,j--){
        //s[i]與s[j]互換
        char temp=s[i];
        s[i]=s[j];
        s[j]=temp;
    }

    /*
    i=0 : 字串的第一個字元的index
    j=L-1 : 字串的最後一個字元的index
    由字串的兩側逐漸向中間靠攏(i++,y--)，並互換經過的字元
    當i=j或i>j時，表示它們已經抵達或通過字串中心的字元了，即已完成反轉，結束迴圈
    */
    cout << s << endl;

    /*
    範例輸入與輸出:
    Enter a string>> I love coding
    gnidoc evol I
    */
    return 0;
}

//本篇筆記參考嘉義大學資訊工程學系許政穆老師的授課內容與講義
//Created by B.J.Wang 2025/10/16