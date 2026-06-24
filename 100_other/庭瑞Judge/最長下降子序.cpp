#include<iostream>
using namespace std;

int main(){
  int n;
  cin>>n;
  int *arr=new int[n], M=0, count=1;
  for (int i=0;i<n;i++){
    cin>>arr[i];
    if (i==0) continue;
    if (arr[i]<=arr[i-1]) count++;
    else count=1;
    M = max(M,count);
  }
  cout<<M<<endl;
}