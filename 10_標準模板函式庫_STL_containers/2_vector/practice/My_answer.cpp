#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
using namespace std;

int main(){
    // 步驟一
    int n;
    cin>>n;
    vector<int> score(n);
    for (int i=0; i<n; i++){
        cin>>score[i];
    }

    // 步驟二
    score.push_back(100);

    // 步驟三
    sort(score.begin(), score.end(), [](int a, int b){return a>b;});

    // 步驟四
    score.erase(score.end());

    cout<<"排序後(含轉學生，已刪除最低分): ";
    for (const int& num:score) cout<<num<< ' '; cout<<endl;

    // 步驟五
    int sum=0;
    double avg;
    for (const int& num:score){
        sum += num;
    }
    avg = sum / score.size();

    cout<<"平均分數: "<<fixed<<setprecision(2)<<avg<<endl;

    // 步驟六
    vector<int>::iterator it;
    cout<<"迭代器輸出: ";
    for (it=score.begin() ; it!=score.end(); ++it){
        cout<<*it<<' ';
    }cout<<endl;

    // 步驟七
    cout<<"90分是否存在: ";
    if (find(score.begin(), score.end(), 90) != score.end()){
        cout<<"存在"<<endl;
    }
    else{
        cout<<"不存在"<<endl;
    }

    // 步驟八
    cout<<"Size: "<< score.size();
    cout<<", Capacity: "<< score.capacity()<<endl;

    return 0;
}

/*
範例輸入:
5
70 85 60 95 100

範例輸出:
排序後(含轉學生，已刪除最低分): 100 100 95 85 70 
平均分數: 90.00
迭代器輸出: 100 100 95 85 70 
90分是否存在: 不存在
Size: 5, Capacity: 10
*/

// Created by B.J.Wang 2026/7/28