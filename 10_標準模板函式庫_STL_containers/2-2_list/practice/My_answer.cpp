#include<bits/stdc++.h>
using namespace std;

#define Traversal cout<<"step "<<step<<endl;for(const auto& i:waitList){cout<<i<<' ';}cout<<endl;step++;

int main(){
    int step=1;

    // 1.
    list<int> waitList;
    waitList.push_back(101);
    waitList.push_back(102);
    waitList.push_back(103);
    waitList.push_back(104);
    waitList.push_back(105);
    Traversal

    // 2.
    waitList.insert(waitList.begin(), 999);
    Traversal

    // 3.
    waitList.erase(find(waitList.begin(), waitList.end(), 103));
    Traversal

    // 4.
    waitList.remove_if([](int x){return x%2==0;});
    Traversal

    // 5.
    list<int> waitList2 = {201, 203, 205};
    waitList.splice(waitList.end(), waitList2);
    Traversal

    // 6.
    waitList.push_back(201);
    Traversal

    // 7.
    waitList.sort();
    Traversal

    // 8.
    waitList.unique();
    Traversal;

    // 9.
    list<int> vipList = {50, 80};
    waitList.merge(vipList);
    Traversal

    // 10.
    waitList.reverse();
    Traversal

    // 11.
    cout<<"step 11"<<endl;
    cout<<"第一個: "<< waitList.front() <<endl;
    cout<<"最後一個: "<< waitList.back() <<endl;
    cout<<"病患人數: "<< waitList.size() <<endl;
    cout<<"waitList是否為空: "<< waitList.empty() <<endl;

    // 12.
    cout<<"step 12"<<endl;
    int sum = accumulate(waitList.begin(), waitList.end(), 0); //糾正: 加總要從0開始
    double avg = (double)sum / waitList.size();
    cout<<"總和: "<< sum <<endl;
    cout<<"平均值: " << avg <<endl;

    // 13.
    cout<<"step 13"<<endl;
    cout<<"正向: ";
    for (list<int>::iterator it=waitList.begin(); it!=waitList.end(); it++){
        cout<< *it << ' ';
    }cout<<endl;

    cout<<"反向: ";
    for (list<int>::reverse_iterator rit=waitList.rbegin(); rit!=waitList.rend(); rit++){
        cout<< *rit << ' ';
    }cout<<endl;
}

/*
輸出:
step 1
101 102 103 104 105 
step 2
999 101 102 103 104 105 
step 3
999 101 102 104 105 
step 4
999 101 105 
step 5
999 101 105 201 203 205 
step 6
999 101 105 201 203 205 201 
step 7
101 105 201 201 203 205 999 
step 8
101 105 201 203 205 999 
step 9
50 80 101 105 201 203 205 999 
step 10
999 205 203 201 105 101 80 50 
step 11
第一個: 999
最後一個: 50
病患人數: 8
waitList是否為空: 0
step 12
總和: 1944
平均值: 243
step 13
正向: 999 205 203 201 105 101 80 50 
反向: 50 80 101 105 201 203 205 999 
*/