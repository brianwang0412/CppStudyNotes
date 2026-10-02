#include<bits/stdc++.h>
using namespace std;

#define Traversal cout<<"step "<<step<<endl;for (const auto& i:fl){cout<<i<<' ';}cout<<endl;

int main(){
    int step=1;

    // 1.
    forward_list<int> fl;
    fl.push_front(5);
    fl.push_front(4);
    fl.push_front(3);
    fl.push_front(2);
    fl.push_front(1);
    Traversal
        
    // 2.
    fl.insert_after(find(fl.begin(), fl.end(), 3), 999);
    Traversal
    
    // 3.
    fl.insert_after(fl.before_begin(), 0);
    Traversal
    
    // 4.
    fl.erase_after(fl.before_begin());
    Traversal
    
    // 5.
    fl.remove(999);
    Traversal
    
    // 6.
    cout<<"step "<<step<<endl;
    cout<<"length of fl : "<<distance(fl.begin(), fl.end())<<endl;
    step++;
    
    // 7.

    
    // 8.

    
    // 9.

    
    // 10.

    
    // 11.

    
    // 12.

    
    // 13.

    
    // 14.

    
    // 15.

    
    // 16.

    
    // 17.

    
    // 18.

    
    
}