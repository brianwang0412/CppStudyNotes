#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;

int main(){
    long long seed,times,count[6]={0};
    cin >> seed >> times;

    srand(seed);

    for (int i=0;i<times;i++){
        count[rand()%6]++;
    }

    double MEAN=0;
    for (int i=0;i<6;i++){
        MEAN += (i+1) * count[i];
    }
    MEAN = MEAN/times;

    int MAX=0,MIN=0; //以index(索引值)表示
    for (int i=1;i<6;i++){
        if (count[i]>count[MAX]) MAX=i;
        if (count[i]<count[MIN]) MIN=i;
    }

    cout<<"COUNT: ";
    for (int i=0;i<6;i++) cout<<count[i]<<" ";

    cout<<"\nMEAN: "<<setprecision(2)<<fixed<<MEAN<<endl;
    cout<<"MAX: "<<MAX+1<<endl;
    cout<<"MIN: "<<MIN+1<<endl;
}


/*測資
輸入:
7777 
7777

輸出:
COUNT: 1297 1300 1304 1297 1304 1275 
MEAN: 3.49
MAX: 3
MIN: 6
*/

//Created by B.J.Wang 2025/11/20