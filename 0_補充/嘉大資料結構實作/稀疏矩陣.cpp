#include<bits/stdc++.h>
using namespace std;

/*
 * 稀疏矩陣以三元組 <row, col, value> 表示(簡報第 34~35 頁)
 *   a[0] = {總列數, 總行數, 非零項數}   <- 標頭
 *   a[1..n] 依 row 遞增、同 row 內 col 遞增排列
 */

// 程式 2.8:依 a 的 column 順序掃描,時間 O(columns * elements)
void transpose(vector<vector<int>>& a, vector<vector<int>>& b){
    int n = a[0][2];                 // 非零項總數
    b[0][0] = a[0][1];               // b 的列數 = a 的行數
    b[0][1] = a[0][0];               // b 的行數 = a 的列數
    b[0][2] = n;

    if(n > 0){
        int currentb = 1;
        for(int i = 0; i < a[0][1]; i++){        // 對 a 的每個 column
            for(int j = 1; j <= n; j++){         // 掃過全部非零項
                if(a[j][1] == i){                // 這一項屬於目前的 column
                    b[currentb][0] = a[j][1];    // row, col 對調
                    b[currentb][1] = a[j][0];
                    b[currentb][2] = a[j][2];
                    currentb++;
                }
            }
        }
    }
}

// 程式 2.9:先算各 column 的項數與起始位置,一次掃描完成,時間 O(columns + elements)
void fast_transpose(vector<vector<int>>& a, vector<vector<int>>& b){
    int num_cols = a[0][1], num_terms = a[0][2];
    b[0][0] = num_cols;
    b[0][1] = a[0][0];
    b[0][2] = num_terms;

    if(num_terms > 0){
        vector<int> row_terms(num_cols, 0), starting_pos(num_cols, 0);

        for(int i = 1; i <= num_terms; i++)      // 統計 a 每個 column 的項數
            row_terms[a[i][1]]++;

        starting_pos[0] = 1;                     // b 各 row 的起始索引
        for(int i = 1; i < num_cols; i++)
            starting_pos[i] = starting_pos[i-1] + row_terms[i-1];

        for(int i = 1; i <= num_terms; i++){     // 直接放到最終位置
            int j = starting_pos[a[i][1]]++;
            b[j][0] = a[i][1];
            b[j][1] = a[i][0];
            b[j][2] = a[i][2];
        }
    }
}

void print_triples(const string& name, vector<vector<int>>& m){
    cout << name << "\n";
    cout << "      row col value\n";
    for(size_t i = 0; i < m.size(); i++){
        cout << name[0] << "[" << i << "]  "
             << setw(3) << m[i][0] << setw(4) << m[i][1] << setw(6) << m[i][2] << "\n";
    }
    cout << "\n";
}

int main(){
    int max_row=6, max_col=6, max_items=8;

    // 多一列給標頭 a[0],所以大小是 max_items + 1
    vector<vector<int>> a(max_items + 1, vector<int>(3));

    // 圖 2.5(a)
    a = {
        {6, 6,   8},
        {0, 0,  15},
        {0, 3,  22},
        {0, 5, -15},
        {1, 1,  11},
        {1, 2,   3},
        {2, 3,  -6},
        {4, 0,  91},
        {5, 2,  28}
    };
    (void)max_row; (void)max_col;

    vector<vector<int>> b1(max_items + 1, vector<int>(3, 0));
    vector<vector<int>> b2(max_items + 1, vector<int>(3, 0));

    transpose(a, b1);
    fast_transpose(a, b2);

    print_triples("a (original)", a);
    print_triples("b1 (transpose)", b1);
    print_triples("b2 (fast_transpose)", b2);

    cout << (b1 == b2 ? "兩種方法結果相同" : "結果不同") << "\n";
    return 0;
}