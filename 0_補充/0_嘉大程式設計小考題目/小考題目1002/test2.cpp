//兩個女團分數分別加總

#include<iostream>
using namespace std;
/*
int main(){
    int T,H;
    int T_sum=0,H_sum=0;
    cin >> T;
    T_sum += T;
    cin >> H;
    H_sum += H;
    cin >> T;
    T_sum += T;
    cin >> H;
    H_sum += H;
    cin >> T;
    T_sum += T;
    cin >> H;
    H_sum += H;
    cin >> T;
    T_sum += T;
    cin >> H;
    H_sum += H;

    cout << T_sum << " " << H_sum << endl;
}
*/

int main(){
    int T,H;
    int T_sum=0,H_sum=0;

    int i=0;
    while (i<4){
        cin >> T;
        T_sum += T;
        cin >> H;
        H_sum += H;
        i++;
    }

    cout << T_sum << " " << H_sum << endl;
}


//T_sum += T;
//T_sum = T_sum+T;
