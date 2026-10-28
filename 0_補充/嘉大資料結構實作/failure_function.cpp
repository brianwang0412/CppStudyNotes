#include<bits/stdc++.h>
using namespace std;

/*
 * 失效函數 (failure function)  --  簡報第 70~73 頁
 *
 * 定義(簡報第 71 頁):
 *   f(j) = 最大的 i < j,使得 p[0..i] == p[j-i..j];若不存在則為 -1
 *
 * 換句話說:f(j) 是 p[0..j] 中「最長的 真前綴 = 真後綴」的【結尾索引】
 * (也就是長度減 1)。
 *
 * 例:p = abcabcacab
 *   j    : 0  1  2  3  4  5  6  7  8  9
 *   p[j] : a  b  c  a  b  c  a  c  a  b
 *   f(j) :-1 -1 -1  0  1  2  3 -1  0  1
 *   f(6) = 3 因為 "abca" 的前綴 abca 與後綴 abca 相同,結尾索引為 3
 */

// ---------------------------------------------------------------
// 程式 2.15:計算失效函數
// 時間複雜度 O(m),m = strlen(pat)
// ---------------------------------------------------------------
void fail(const string& pat, vector<int>& failure){
    int n = pat.size();
    failure.assign(n, -1);

    failure[0] = -1;   // 只有一個字元,沒有「真前綴」,固定為 -1

    for(int j = 1; j < n; j++){            // 依序算 f(1), f(2), ..., f(n-1)

        // i 代表「目前已經相符的前綴」的結尾索引。
        // 先從 f(j-1) 出發:p[0..i] 已經等於 p[j-1-i..j-1],
        // 現在只要檢查能不能再延長一格。
        int i = failure[j-1];

        // 若 p[j] 與前綴的下一個字元 p[i+1] 不相等,延長失敗。
        // 此時不從頭重來,而是退到「次長的前綴」:i = f(i)。
        // 這個前綴本來就是 p[0..i] 的前綴兼後綴,所以仍然成立。
        // 一直退到相等,或退到 i < 0(完全沒有前綴可用)為止。
        while(i >= 0 && pat[j] != pat[i+1])
            i = failure[i];

        // 迴圈結束只有兩種情況:
        if(pat[j] == pat[i+1])
            failure[j] = i + 1;   // (1) 找到相等:前綴多延長一格
        else
            failure[j] = -1;      // (2) i 已退到 -1 且 p[j] != p[0]:沒有前綴
    }

    /*
     * 為什麼是 O(m)?
     * i 在每次 for 迴圈中最多增加 1(failure[j] = i+1),
     * 而 while 裡每退一次 i 就變小,所以「退的總次數」不會超過「增加的總次數」,
     * 整體最多 2m 步(攤銷分析)。
     */
}

// ---------------------------------------------------------------
// 程式 2.14:KMP 字串比對
// 時間複雜度 O(n + m),n = strlen(string),m = strlen(pat)
// 成功回傳 pat 在 string 中第一次出現的起始索引,失敗回傳 -1
// ---------------------------------------------------------------
int pmatch(const string& str, const string& pat, const vector<int>& failure, bool verbose = false){
    int i = 0, j = 0;                 // i:string 的索引,j:pat 的索引
    int lens = str.size();
    int lenp = pat.size();

    while(i < lens && j < lenp){
        if(str[i] == pat[j]){
            // 相符:兩個索引一起前進
            i++;
            j++;
        }
        else if(j == 0){
            // 第一個字元就不符:pat 無處可退,只能把 string 往後移一格
            i++;
        }
        else{
            // 失配發生在 pat 的第 j 個字元,代表前 j 個字元(p[0..j-1])已相符。
            // 這 j 個字元的「最長前綴 = 後綴」結尾索引是 failure[j-1],
            // 所以 pat[0..failure[j-1]] 已經和 string 目前位置之前的字元對齊。
            // 下一個要比的是 pat[failure[j-1] + 1]。
            // 注意:i 完全不動,string 的指標永遠不會往回退。
            if(verbose)
                cout << "  失配: string[" << i << "]=" << str[i]
                     << " vs pat[" << j << "]=" << pat[j]
                     << " -> j = failure[" << j-1 << "]+1 = "
                     << failure[j-1] + 1 << "\n";
            j = failure[j-1] + 1;
        }
    }

    // j == lenp 表示 pat 整個比對完成,起始位置是 i - lenp
    return (j == lenp) ? (i - lenp) : -1;
}

void print_failure(const string& pat, const vector<int>& f){
    cout << "j    : ";
    for(size_t j = 0; j < pat.size(); j++) cout << setw(3) << j;
    cout << "\np[j] : ";
    for(char c : pat) cout << setw(3) << c;
    cout << "\nf(j) : ";
    for(int v : f) cout << setw(3) << v;
    cout << "\n";
}

int main(){
    vector<int> failure;

    // ---- 測試 1:簡報第 71 頁的範例 ----
    string pat1 = "abcabcacab";
    fail(pat1, failure);
    cout << "[測試1] 簡報第 71 頁\n";
    print_failure(pat1, failure);      // 預期 -1 -1 -1 0 1 2 3 -1 0 1

    string s1 = "abcabcabcacab";
    cout << "在 \"" << s1 << "\" 中搜尋 \"" << pat1 << "\":\n";
    int r1 = pmatch(s1, pat1, failure, true);   // 先執行,避免輸出交錯
    cout << "結果 = " << r1 << "\n\n";           // 預期 3

    // ---- 測試 2:期中考第 3 題 ----
    string pat2 = "abcdabcabcdabcdabc";
    string s2   = "abcdabcabcdabcabcda";
    fail(pat2, failure);
    cout << "[測試2] 期中考第 3 題\n";
    print_failure(pat2, failure);      // 預期 ... 6 3 4 5 6

    cout << "在 \"" << s2 << "\" 中搜尋 \"" << pat2 << "\":\n";
    // j=14 失配時,j = failure[13]+1 = 7,string 的 i 維持 14
    int r2 = pmatch(s2, pat2, failure, true);
    cout << "結果 = " << r2 << "\n";                // 預期 -1

    return 0;
}
