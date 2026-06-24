#include<iostream>
using namespace std;

int main(){
    int N=5,Array[N]={5, 1, 3, 4, 2};
    
    for (int i=0 ; i<N-1 ; i++){
        for (int j=0 ; j<N-1-i ; j++){
            if (Array[j]>Array[j+1]){
                int temp = Array[j];
                Array[j] = Array[j+1];
                Array[j+1] = temp;
            }
        }
    }

    for (int i=0 ; i<N ; i++) cout << Array[i] << " ";
    return 0;
}
