#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

int main() {
    vector<int> vec = {10, 20, 30, 40, 50};
    map<string,int> scores = {{"Alice",85},{"Bob",70},{"Carol",92},{"David",60}};

    // 1. 反向迭代器印出 vec
    cout << "1. vec反向輸出: ";
    for (vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;

    // 2. const_iterator 正向遍歷 scores
    cout << "2. scores(依姓名字母排序): ";
    for (map<string,int>::const_iterator cit = scores.cbegin(); cit != scores.cend(); ++cit) {
        cout << cit->first << ":" << cit->second << " ";
    }
    cout << endl;

    // 3. find 30 並在其前插入 25
    vector<int>::iterator it30 = find(vec.begin(), vec.end(), 30);
    if (it30 != vec.end()) {
        vec.insert(it30, 25); // 注意：insert 後 it30 已失效，之後不可再用它
    }
    cout << "3. 插入25後的vec: ";
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 4. 刪除成績 < 70 的學生
    for (map<string,int>::iterator it = scores.begin(); it != scores.end(); ) {
        if (it->second < 70) {
            it = scores.erase(it); // erase 回傳下一個有效的 iterator，避免 iterator 失效問題
        } else {
            ++it;
        }
    }
    cout << "4. 刪除後的scores: ";
    for (map<string,int>::iterator it = scores.begin(); it != scores.end(); ++it) {
        cout << it->first << ":" << it->second << " ";
    }
    cout << endl;

    // 5. accumulate 計算總和
    int sum = accumulate(vec.begin(), vec.end(), 0);
    cout << "5. vec總和: " << sum << endl;

    return 0;
}