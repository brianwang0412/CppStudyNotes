#include<utility>
#include<iostream>
using namespace std;

// 補充一 : 實作運算子多載
std::ostream& operator<<(ostream& output, const pair<int, int>& p){
    output<< p.first << ' ' << p.second;
    return output;
}

int main(){
    pair<int, pair<int, int>> p = {1, {2, 3}};
    cout << p.first << ' ' << p.second << endl;  //輸出: 1 2 3
}