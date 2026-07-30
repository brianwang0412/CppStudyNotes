#include<iostream>
#include<string>
#include<map>
using namespace std;

int main(){
    map<char, int> M;
    M['a']=1;
    M['b']++;
    M['b']++;

    auto it=M.begin();
    for (; it!=M.end(); ++it) cout<<it->first<<' '<<it->second<<endl;
}