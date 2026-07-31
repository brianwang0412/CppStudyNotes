#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>  //std::find 定義在此
#include<numeric>    //std::accumulate 定義在此
using namespace std;

int main(){
    vector<int> vec = {10, 20, 30, 40, 50};
    map<string, int> scores = {{"Alice",85},{"Bob",70},{"Carol",92},{"David",60}};
    
    // 1. 使用反向迭代器 (reverse_iterator) 由後往前印出 vec 的所有元素
    cout<<"1. vec反向輸出: ";
    for (vector<int>::reverse_iterator it=vec.rbegin(); it!=vec.rend(); ++it){
        cout<< *it << ' ';
    }
    cout<<endl;

    // 2. 使用 const_iterator 正向遍歷 scores，印出每位學生的姓名與成績
    cout<<"2. scores(依姓名字母排序): ";
    for (map<string, int>::const_iterator it=scores.begin(); it!=scores.end(); ++it){
        cout<< it->first << ':' << it->second << ' ';
    }
    cout<<endl;

    // 3. 使用 std::find 搭配 iterator，在 vec 中找到數值 30 的位置，並在該位置「之前」插入新元素 25，
    //    接著印出插入後 vec 的完整內容。（須注意 insert 後 iterator 失效的問題）
    cout<< "3. 插入25後的vec: ";
    vector<int>::iterator pos=find(vec.begin(), vec.end(), 30);
    vec.insert(pos, 25);
    for (auto it=vec.begin(); it!=vec.end(); ++it){
        cout<< *it << ' ';
    }
    cout<<endl;


    // 4. 使用 iterator 遍歷 scores，將所有成績低於 70 分的學生刪除，
    //    並正確處理 map::erase 導致的 iterator 失效問題，最後印出剩餘學生資料。
    cout<< "4. 刪除後的scores: ";

    // 4-1 利用scores.erase(iterator)會回傳被刪除的元素的下一個元素的迭代器的特性
    for (auto it=scores.begin(); it!=scores.end();){
        if (it->second<70){
            it = scores.erase(it);
        }
        else{
            ++it;
        }
    }
    //遍歷
    for (auto it=scores.begin(); it!=scores.end(); ++it){
        cout<< it->first << ':' << it->second << ' ';
    }
    cout<<endl;

    //初始化
    scores = {{"Alice",85},{"Bob",70},{"Carol",92},{"David",60}};

    // 4-2 我嘗試使用反向迭代器來遍歷並刪除
    cout<< "4. 刪除後的scores: ";
    for (auto it=scores.rbegin(); it!=scores.rend(); ++it){
        if (it->second<70) scores.erase(it->first); //這裡用指定key的方式刪除
    }
    //遍歷
    for (auto it=scores.begin(); it!=scores.end(); ++it){
        cout<< it->first << ':' << it->second << ' ';
    }
    cout<<endl;


    //5. 使用 std::accumulate 搭配 iterator，計算 vec 所有元素的總和並印出
    cout<<"5. vec總和: ";
    cout<< accumulate(vec.begin(), vec.end(), 0) <<endl;

    return 0;
}