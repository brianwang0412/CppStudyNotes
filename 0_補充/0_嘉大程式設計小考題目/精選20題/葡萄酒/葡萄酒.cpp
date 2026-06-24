#include<iostream>
using namespace std;

//參考ChatGPT的解釋
//https://chatgpt.com/share/693a3115-998c-8009-b4ac-4a8fa62b7828

/*
解題思路
把自己當成一個配送專員
自己身上(carry)不管是正的(購買訂單)還是負的(賣出訂單)都視為工作量(abs(carry))
當carry>0：還欠別人酒（前面的人還有需求沒被滿足，之後拿到酒要搬回去）
當carry<0：身上有多餘的酒（前面的人賣出的酒你正幫忙往後送）
這些都需要搬的動作 -> 代表都需要工作量

為何從頭走到尾就是最省力的方法 

因為 carry 表示「前面多出的量」或「前面欠的量」，
而距離就是「這些量必須跨越多少位置」。
sum += abs(carry) 的意思是：
你每走到下一個房子時
你身上仍要搬著前面未處理完的酒瓶
每跨一步，那些酒瓶都要被搬一次 → 增加工作量
也就是說：
carry 多少，就代表這些瓶子要跟你一起走到下一個位置，那就是工作量。
所以你從「頭走到尾」，每一步「把前面的需求消化掉」，就是最省的一條路。
*/

int main(){
    long long n;
    while (true){
        cin>>n;
        if (n==0) break;

        long long carry=0,get, sum=0; //carry:訂單總和，get:現在取得的訂單，sum:工作量總和
        for (long long i=0;i<n;i++){
            cin>>get;
            carry+=get;
            sum+=abs(carry);
        }        
        cout<<sum<<endl;
    }
}

/*題目敘述
As you may know from the comic “Asterix and the Chieftain’s Shield”, Gergovia consists of one street, and every inhabitant of the city is a wine salesman. You wonder how this economy works? Simple enough: everyone buys wine from other inhabitants of the city. Every day each inhabitant decides how much wine he wants to buy or sell. Interestingly, demand and supply is always the same, so that each inhabitant gets what he wants.
    There is one problem, however: Transporting wine from one house to another results in work. Since all wines are equally good, the inhabitants of Gergovia don’t care which persons they are doing trade with, they are only interested in selling or buying a specific amount of wine. They are clever enough to figure out a way of trading so that the overall amount of work needed for transports is minimized.
    In this problem you are asked to reconstruct the trading during one day in Gergovia. For simplicity we will assume that the houses are built along a straight line with equal distance between adjacent houses. Transporting one bottle of wine from one house to an adjacent house results in one unit of work.

您可能會從漫畫"Asterix and the Chieftain's Shield"中了解到，Gergovia由一條街道組成，每個城市的居民都是葡萄酒推銷員。
您想知道這種經濟如何運作嗎？
每個人都從城市的其他居民那裡購買葡萄酒。每位居民每天都要決定要購買或出售多少酒。
有趣的是，供需始終是相同的，因此每個居民都能得到自己想要的東西。
但是有一個問題，將葡萄酒從一所房子運到另一所房子會導致工作量上升。
由於所有葡萄酒的品質都一樣，因此，Gergovia的居民不在乎與之交易的人，他們只對出售或購買特定數量的葡萄酒感興趣。
他們足夠聰明，可以找到一種交易方式，從而使運輸所需的總工作量最小化。
在這個問題上，您需要重建Gergovia的一天中的交易路線。為簡單起見，我們假設房屋是沿著一條直線建造的，相鄰房屋之間的距離相等
將一瓶葡萄酒從一棟房子運送到相鄰的房子需要一個單位的工作量。

Input
The input consists of several test cases. Each test case starts with the number of inhabitants \(n (2 ≤ n ≤ 100000)\). The following line contains n integers \(a_i (−1000 ≤ a i ≤ 1000)\). If \(a_i ≥ 0\), it means that the inhabitant living in the \(i\)-th house wants to buy a[ i ] bottles of wine, otherwise if \(a_i < 0\), he wants to sell \(−a_i\) bottles of wine. You may assume that the numbers a[ i ] sum up to \(0\). The last test case is followed by a line containing ‘0’.
輸入包含多組測資。每組測資的開始是居民數 n(2≤n≤100000)n。接下來的一行包含 n 個整數 a[ i ](−1000≤a[ i ]≤1000)。如果 a[ i ]≥0​，表示第 i 戶居民想購買 a[ i ] 瓶葡萄酒；如果 a[ i ]<0，表示第 ii 戶居民想賣出 −a[ i ]瓶葡萄酒。可以假設所有 a[ i ] 的總和為 0。最後一組測資後，會有一行僅包含 ‘0’。

Output
For each test case print the minimum amount of work units needed so that every inhabitant has his demand fulfilled. You may assume that this number fits into a signed 64-bit integer (in C/C++ you can use the data type “long long”, in JAVA the data type “long”).
對於每組測資，請輸出滿足每個居民需求所需的最小工作量。可以假設這個數字可以存入有號 64 位元整數（在 C/C++ 中可使用資料型態 “long long”，在 JAVA 中可使用資料型態 “long”）。


For example:

輸入1:
5
5 -4 1 -3 1
0

輸出1:
9

輸入1:
6
-1000 -1000 -1000 1000 1000 1000
0

輸出1:
9000


*/