#include<bits/stdc++.h>
using namespace std;

#define Now_Patients {cout<<"目前病患: ";for (const string& s:patients){cout<< s <<' ';}cout<<endl;}

int main(){
    // 1.
    deque<string> patients;

    // 2.
    patients.push_back("王小明");
    patients.push_back("陳美麗");
    patients.push_back("林大同");
    Now_Patients;

    // 3.
    patients.push_front("張醫生的家屬");
    Now_Patients;

    // 4.
    deque<string>::iterator it = find(patients.begin(), patients.end(), "陳美麗");
    patients.erase(it);
    patients.insert(patients.begin()+1, "陳美麗");
    Now_Patients;

    // 5.
    cout<<"第一位病患: "<< patients.front() <<endl;
    cout<<"最後一位病患: "<< patients.back() <<endl;

    // 6.
    cout<<"開始叫號:\n";
    while (patients.size() > 2){
        cout<<"正在為 "<< patients.front() <<"看診"<<endl;
        patients.pop_front();
    }
    Now_Patients;

    // 7.
    patients.push_back("李四");
    Now_Patients;
    try{
        cout<<"index=5 的病患是: ";
        cout<<patients.at(5)<<endl;
    }
    catch (std::out_of_range& e){
        cout<<"錯誤: "<<e.what()<<endl;
    }

    // 8.
    cout<<"目前佇列人數: "<<patients.size()<<endl;
    cout<<"佇列是否為空: "<<boolalpha<< patients.empty()<<endl;

    // 9.
    patients.clear();
    cout<<"清空後是否為空: "<<patients.empty()<<endl;

    // 10.
    deque<int> waitTimes = {15, 5, 30, 10, 20};
    sort(waitTimes.begin(), waitTimes.end());
    cout<<"排序後的等待時間: ";
    for (const int& i:waitTimes){
        cout<< i <<' ';
    }cout<<endl;

    int Total = accumulate(waitTimes.begin(), waitTimes.end(), 0);
    cout<<"總等待時間: "<<Total<<" 分鐘"<<endl;

}

// Created by B.J.Wang 20260824