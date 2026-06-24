// https://zerojudge.tw/ShowProblem?problemid=d784

/*
題目說明:
已知一n個元素的整數數列，找出該數列連續元素的和的最大值。

輸入:
第一行的數字，代表有幾組測試資料，第二行開始的每一行即為一筆測試資料。
每一筆測試資料以空格分開數字：
第一個整數為數列長度n，其範圍為[1,100]的整數；
接下來的n個整數，其範圍為[-10000, 10000]的整數。

輸出:
對每一筆測試資料，以一行輸出最大連續元素的和。
*/


/*
讀入測資，順便加總，並紀錄出現過的最大和 (mx)。
當目前累計和 (sum) 變成負值時，就將其重置為零，因其對後續的結果沒有貢獻。
*/
#include <iostream>
using namespace std;
 
int main() {
    int n, m, mx, sum, tmp;
    while (cin >> n){
        while (n--){
            cin >> m;
            mx = -10000;
            sum = 0;
            for (int i = 0; i < m; i++){
                cin >> tmp;
                sum += tmp;
                mx = max(mx, sum);
                if (sum < 0) sum = 0;
            }
            cout << mx << "\n";
        }
    }
}

// 來源: https://yuihuang.com/zj-d784/