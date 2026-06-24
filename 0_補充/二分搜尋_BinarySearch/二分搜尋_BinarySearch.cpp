#include<iostream>
#include<algorithm>
using namespace std;

int BinarySearch(int L, int R, int Array[], int ans){

}

int main(){
    int N;
    cout << "How long is this array>> ";
    cin >> N;

    int Array[N];
    for (int i=0;i<N;i++){
        cout << "Number" << i+1 << "is>> ";
        cin >> Array[i];
    }

    sort(Array[0],Array[N-1]);

    cout << "\nThe Array: {";
    for (auto i:Array) cout << Array[i] << ',';
    cout << '}' <<endl;

    int ans;
    cout << "Which number do you want to search>> ";
    cin >> ans;
    BinarySearch(0, N-1, Array, ans);
}