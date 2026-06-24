#include<iostream>
using namespace std;

int main(){
    int N;
    cin >> N;
    cout << "N=" << N<<endl;
    for (int i=0;i<=N;i++){
        if (i%2==0){
            for (int j=0;j<i;j++) cout << "*";
            cout <<endl;
        }
    }
}
