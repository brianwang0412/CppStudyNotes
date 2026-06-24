#include<iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    char s[n+1];
    cin >> s;
    int mi=n,r=-1,d=-1;
    for (int i=0;i<n;i++){
        if (s[i]=='Z') mi=0;
        else if (s[i]=='R'){
            if (d!=-1){
                mi = min(mi, i-d);
            }
            r=i;
        }
        else if (s[i]=='D'){
            if (r!=-1){
                mi = min(mi, i-r);
            }
            d=i;
        }
    }
    cout<<mi;
}

/*題目敘述
Everybody knows that along the more important highways there are countless fast food restaurants. One can find easily hamburgers, hot dogs, pizzas, sandwiches ... food everywhere.
    Many times the problem isn’t to find a restaurant but a drugstore. After a big lunch with fast food it’s normal that we need a drugstore because our stomach begins to feel pain.
    Given the locations of the restaurants and drugstores on a highway, you want to determine the minimum distance between a restaurant and a drugstore.
大家都知道，在高速公路上旁都有無數的快餐店。
人們可以輕鬆地買到漢堡包，熱狗，比薩，三明治等等食物。
但是很多時候，問題不是找到餐館而是藥局。一頓豐盛的午餐後，我們通常需要去買胃藥，因為我們年紀大了。
給定高速公路上餐廳和藥局的位置，你想要確定餐廳和藥局之間的最短距離。


Input
The first line of each test case gives an integer \(L (1 ≤ L ≤ 2000000)\) indicating the length of the highway.
    The second line of each test case contains a string \(S\) of length \(L\), showing the positions of the restaurants and drugstores along the highway in the following manner:

    • The character ‘R’ represents a place with a restaurant. 
    • The character ‘D’ represents a place with a drugstore. 
    • The character ‘Z’ represents a place with a restaurant and a drugstore. 
    • The character ‘.’ represents an empty place.
測資有兩行，第一行有一個正整數 L (1 <= n <= 2000000)，L代表公路的長度。
第二行為長度L的字串，代表沿著公路的餐廳和藥局的位置。
字串的內容如下：
1. 'R'代表這個位置有餐廳
2. 'D'代表這個位置有藥局
3. 'Z'代表這個位置同時有餐廳和藥局
4. '.'代表這個位置什麼都沒有
每組測資中至少有一間餐廳和一間藥局。
Output
For each case in the input, print one line with the minimum distance between a restaurant and a drugstore.

對於每組測資，輸出餐廳和藥局之間的最短距離。

For example:
輸入1:
2
RD

輸出1:
1

輸入2:
5
..Z..

輸出2:
0

*/