#include<iostream>
#include<string>
using namespace std;

int main(){
    string s;
    getline(cin,s);

    bool A=true;

    for (int i=0,j=(s.size()-1) ; i<j ; i++,j--){
        if (s[i]!=s[j]){
            A=false;
            break;
        }
    }
    cout << (A? "Good":"NotGood")<<endl;
    return 0;
}