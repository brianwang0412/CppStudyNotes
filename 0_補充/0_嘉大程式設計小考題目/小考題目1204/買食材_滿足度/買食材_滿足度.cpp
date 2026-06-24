/*
題目敘述:

輸入:
有N種食材
有m元錢

每種食材分別的
W: 單價(元/公斤)
S: 滿足度(點/每公斤)
R: 庫存(公斤)

輸出:
用m元錢去買食材，最多可以獲得多少滿足度

注意:
不一定要買整數公斤(如:1公斤)，也可以買0.5公斤，0.1公斤等
*/

/*
解題重點: 將錢全部拿來買「性價比」最高的
性價比 = 滿足度 / 價格，(即:花費一元買這個食材可以獲得多少滿足度)
*/

/*
我的作法:

先將所有食材的「價格、滿足度、庫存」以「性價比」由大到小排序

接下來購買性價比最高的食材:
先計算現有的金錢最多可以買多少公斤的該食材(先假設為BUY，BUY=)
若BUY「大於」該食材剩餘的庫存，就買下該食材「剩餘庫存的量」
否則買下「最多能購買的量」(即BUY)
*/



#include<iostream>
#include<iomanip>
using namespace std;

int main(){
    cout<<"Program Start"<<endl;

    int N; //N:有幾種食材
    double money; //money:有多少錢
    cin >> N >> money;

    double W[N],S[N],R[N],S_sum=0; //S_sum:總共獲得的滿足度
    for (int i=0;i<N;i++) cin>>W[i];
    for (int i=0;i<N;i++) cin>>S[i];
    for (int i=0;i<N;i++) cin>>R[i];

    //先用Bubble Sort將W,S,R「以該食材的性價比由大排到小」
    for (int i=0;i<N-1;i++){
        for (int j=0;j<N-1;j++){
            if ( (S[j+1]/W[j+1]) > (S[j]/W[j]) ){
                //swap(a,b):交換a,b的值，在<iostream>內有
                swap(W[j+1],W[j]);
                swap(S[j+1],S[j]);
                swap(R[j+1],R[j]);
            }
        }
    }

    //從性價比最高的食材開始購買
    for (int i=0;i<N;i++){
        if (money<=0) break; //沒有錢，我們就只能回家~

        double buy=money/W[i];
        if (buy>R[i]){
            money -= W[i]*R[i];
            S_sum += S[i]*R[i];
        }
        else{
            money -= W[i]*buy;
            S_sum += S[i]*buy;
        }
    }

    cout <<fixed <<setprecision(2) << S_sum <<endl;
    return 0;
}


/*
第一筆測資
輸入:
3 10
1 2 2
2 4 6
4 10 3

輸出:
26.00
*/


/*
第二筆測資
輸入:
2 5
1 3
2 1
5 10

輸出:
10.00
*/

//Created by B.J.Wang 2025/12/5