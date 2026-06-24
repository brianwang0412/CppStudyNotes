#include<iostream>
using namespace std;

//a(n) = n*a(n-1), a(1)=1

int Array[41][50];

void Calculate(int num){
    //乘法(a(n) = n*a(n-1))
    for (int i=0;Array[num-1][i]!=-1;i++)
        Array[num][i] = num * Array[num-1][i];

    //找該數字的最大位數
    int index;
    for (index=0;Array[num][index+1]!=-1;index++)

    //進位
    for (; index>=0;index--){
        if (Array[num][index] > 9){
            Array[num][index+1] += Array[num][index]/10;
            Array[num][index] = Array[num][index]%10;
        }
    }
        
}

void Output(int num){
    //找該數字的最大位數
    int index;
    for (index=0;Array[num][index+1]!=-1;index++);

    //由最後開始輸出
    int newline=0;
    for (;index>=0;index--){
        cout << Array[num][index];
        newline++;
        if (newline%5==0) cout<<" ";
    }
}

int main(){
    cout << "Program Start"<<endl;
    //將陣列初始化為-1
    for (int i=0;i<41;i++)
        for (int j=0;j<50;j++)
            Array[i][j]=-1;

    Array[1][0]=1;

    for (int i=2;i<=40;i++){
        Calculate(i);
        cout << i << " : ";
        Output(i);
        cout <<endl;
    }
        
/*
    cout << "Input Ready"<<endl;

    int n;
    while (cin>>n){
        cout << fixed << setprecision(0);
        if (n==1) cout << "The "<< n <<"st factoial number is ";
        else if (n ==2) cout << "The "<< n <<"nd factoial number is ";
        else if (n ==3) cout << "The "<< n <<"rd factoial number is ";
        else cout << "The "<< n <<"th factoial number is ";
        Output(n);
        cout <<'.'<<endl;
    }
*/
}