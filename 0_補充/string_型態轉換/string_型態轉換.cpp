#include<iostream>
#include<string>
#include<typeinfo>
using namespace std;

int int_reverse(int);

int main(){
    int num=123456;
    float pi=3.14;
    string s_num,s_pi;
    s_num = to_string(num); //將int轉換為string
    s_pi = to_string(pi); //將float轉換為string

    cout<<"s_num = "<<s_num<<", type is : "<<typeid(s_num).name()<<endl;
    //s_num = 123456, type is : NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE 就是string
    
    cout<<"s_pi = "<<s_pi<<", type is : "<<typeid(s_pi).name()<<endl;
    //s_pi = 3.140000, type is : NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
    //預設顯示六位小數

    cout<< int_reverse(987654321) <<endl; //123456789

}

//數字反轉
int int_reverse(int num){
    string temp = to_string(num);
    for (int i=0,j=temp.size()-1 ; i<j ; i++,j--){
        swap(temp[i],temp[j]);
    }
    num = stoi(temp); //將string轉換為int，(stoi = string to int)
    //也可以轉成其他型別，如stol，stof，stod，即long，float，double
    return num;
}

//Created by B.J.Wang 2025/11/13