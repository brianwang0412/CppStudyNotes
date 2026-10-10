#include<bits/stdc++.h>
using namespace std;

#define Traversal cout<<"\nstep "<<step++<<endl;for (const auto& i:fl){cout<<i<<' ';}cout<<endl;

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
    cout<<"\nstep "<<step<<endl;
    cout<<"length of fl : "<<distance(fl.begin(), fl.end())<<endl;
    step++;
    
    // 7.
    forward_list<int> fl2 = {100, 200, 300};
    int n = distance(fl.begin(), fl.end());
    fl.splice_after(next(fl.begin(), n-1), fl2);
    Traversal

    // 8.
    fl.emplace_front(0);
    fl.emplace_after(fl.begin(), -1);
    Traversal
    
    // 9.
    fl.sort(greater<int>()); // 由大到小排序
    Traversal
    
    // 10.
    fl.reverse();
    Traversal
    
    // 11.
    fl.remove_if([](int x){return x>=100;});
    Traversal
    
    // 12.
    cout<<"\nstep "<<step++<<endl;
    if (find(fl.begin(), fl.end(), 3)!=fl.end()){
        cout<<"Found at index "<<distance(fl.begin(), find(fl.begin(), fl.end(), 3))<<'\n';
    }
    else{
        cout<<"Not Found"<<endl;
    }
    
    // 13.
    cout<<"\nstep "<<step++<<endl;
    cout<<"Sum of fl = "<<accumulate(fl.begin(), fl.end(), 0)<<'\n';
    
    // 14.
    
    
    // 15.

    
    // 16.

    
    // 17.

    
    // 18.

    
    
}