//可遍歷解

#include<iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int i, j;
    while (cin >> i >> j){
        int mx = 0;
        for (int n = min(i, j); n <= max(i, j); n++){
            int temp = n, n_len = 1;
            while (temp != 1){
                if (temp % 2) temp = 3 * temp + 1;
                else temp /= 2;
                n_len++;
            }
            mx = max(mx, n_len);
        }
        cout << i << " " << j << " " << mx << "\n";
    }
    return 0;
}

//答案參考: https://yuihuang.com/zj-c039/
//AC