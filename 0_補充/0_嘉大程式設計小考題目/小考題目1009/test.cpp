#include <iostream>
using namespace std;
int main (){
    int N;
    cin >> N;
    cout << "N=" << N;
    cout << endl;
    for(int i=1;i<=N;i++){
        for (int j=N-i;j>=1;j--){
            cout<<" ";
        }
        for(int k=1;k<=i*2-1;k++){
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}
/*
n=3
  *    
 ***
*****
*/