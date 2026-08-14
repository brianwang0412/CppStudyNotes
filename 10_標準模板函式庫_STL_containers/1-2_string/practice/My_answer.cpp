#include<bits/stdc++.h>
using namespace std;

int main(){
    string info = "Amy,88,92,foo;Bob,75,68,90;Cindy,100,59,77";
    
    vector<string> temp;
    vector<string> validStudent;
    
    // 1. 
    string token;
    stringstream ss(info);
    while (getline(ss, token, ';')){
        temp.push_back(token);
    }

    // 2~5
    for (const string& s:temp){
        stringstream scores(s);
        string name, Chinese, English, Math;
        getline(scores, name, ',');
        getline(scores, Chinese, ',');
        getline(scores, English, ',');
        getline(scores, Math, ',');

        try{
            int C = stoi(Chinese),
                E = stoi(English),
                M = stoi(Math);

            int avg = (C+E+M)/3;
            string grade;
            if (avg>=90) grade="A";
            else if (avg>=80) grade="B";
            else if (avg>=70) grade="C";
            else if (avg>=60) grade="D";
            else grade="E";

            cout<< name <<" 平均:"<< avg <<" 等第:" <<grade<<endl;
            validStudent.push_back(name);
        }
        catch(std::invalid_argument){
            cout<<"資料錯誤: "<< name <<" 的成績格式不正確"<<endl;
        }
    }

    // 6.
    string minName('Z',99);
    for (const string& s:validStudent){
        minName = min(minName, s);
    }
    cout<< "字典順序最小的姓名: "<< minName <<endl;

    // 7.
    string output;
    for (const string& s:validStudent){
        output+=s;
        if (s != validStudent[validStudent.size()-1]){
            output+="、";
        }
    }
    cout<<"全體學生: "<< output << endl;

    // 8.
    while (info.find(',') != string::npos){
        info.replace(info.find(','), 1, " ");
    }
    cout<< info <<endl;

}

/*
輸出:
資料錯誤: Amy 的成績格式不正確
Bob 平均:77 等第:C
Cindy 平均:78 等第:C
字典順序最小的姓名: Bob
全體學生: Bob、Cindy
Amy 88 92 foo;Bob 75 68 90;Cindy 100 59 77
*/

// Created by B.J.Wang 20260814