/*
題目解析:
一個陣列做BubbleSort，要交換幾次
*/

#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int N;
    cin >> N;
    int Arr[N];
    for (int i=0;i<N;i++) cin >> Arr[i];

    int count=0;
    for (int i=0;i<N-1;i++){
        for (int j=0;j<N-1;j++){
            if (Arr[j]>Arr[j+1]){
                swap(Arr[j],Arr[j+1]);
                count++;
            }
        }
    }

    cout << "\nMinimum exchange operations : " <<count<<endl;
    return 0;
}