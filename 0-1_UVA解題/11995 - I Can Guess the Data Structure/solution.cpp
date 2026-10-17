#include<iostream>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

// 重點: 取出前先檢查容器是否為empty

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, cmd, x;
    while (cin>>n){
        stack<int> s;
        queue<int> q;
        priority_queue<int> pq;
        vector<int> ans(3,1);
        
        for (int i=0; i<n; i++){
            cin>>cmd>>x;
            if (cmd==1){
                s.push(x);
                q.push(x);
                pq.push(x);
            }
            else{
                if (ans[0]){
                    if (s.empty()||s.top() != x) ans[0]=0; 
                    s.pop();  
                }
                if (ans[1]){
                    if (q.empty()||q.front() != x) ans[1]=0;
                    q.pop();
                }
                if (ans[2]){
                    if (pq.empty()||pq.top() != x) ans[2]=0;
                    pq.pop();
                }
            }
        }

        switch (ans[0]+ans[1]+ans[2]){
            case 2: case 3:
                cout<<"not sure\n";
                break;
            case 0:
                cout<<"impossible\n";
                break;
            case 1:
                if (ans[0]) cout<<"stack\n";
                else if(ans[1]) cout<<"queue\n";
                else cout<<"priority queue\n";
                break;
        }
    }
}