#include<iostream>
#include<iomanip>
using namespace std;

int main(){
  int n;
  char c;
  cin>>n>>c;
  cout<<setw(n-1)<<setfill(' ')<<"";
  cout<<c<<endl;
  for (int i=2;i<=n;i++){
    if (i!=n){
      cout<<setw(n-i)<<setfill(' ')<<"";
      cout<<c;
      cout<<setw(1+(i-2)*2)<<setfill(' ')<<"";
      cout<<c<<endl;
    }
    else{
      for (int j=0;j<(n*2-1);j++) cout<<c;
    }
  }
}