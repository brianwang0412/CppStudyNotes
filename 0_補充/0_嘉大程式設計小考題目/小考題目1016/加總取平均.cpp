#include<iostream>
using namespace std;

int main(){
    int N;
    cin >> N;
    int sum = 0;
    int a;
for(int i = 1;i <= N;i++){
    cin >> a;
    sum += a;
}
cout << sum / N;
}