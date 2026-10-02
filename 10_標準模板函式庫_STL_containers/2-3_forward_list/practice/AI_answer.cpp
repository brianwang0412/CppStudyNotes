
#include<forward_list>
#include<iostream>
#include<algorithm>
#include<numeric>
#include<iterator>
using namespace std;

// ------------------------------------------------------------------
// 以下為參考解答，建議先自行嘗試作答後，再對照下方程式碼與輸出
// ------------------------------------------------------------------

int main(){
    forward_list<int> fl;

    // (1)
    cout<<"(1) ";
    fl.push_front(5);
    fl.push_front(4);
    fl.push_front(3);
    fl.push_front(2);
    fl.push_front(1);
    for (const int& i:fl) cout<<i<<' ';
    cout<<endl;
    // 輸出: (1) 1 2 3 4 5

    // (2)
    cout<<"(2) ";
    fl.insert_after(find(fl.begin(), fl.end(), 3), 999);
    for (const int& i:fl) cout<<i<<' ';
    cout<<endl;
    // 輸出: (2) 1 2 3 999 4 5

    // (3)
    cout<<"(3) ";
    fl.insert_after(fl.before_begin(), 0);
    for (const int& i:fl) cout<<i<<' ';
    cout<<endl;
    // 輸出: (3) 0 1 2 3 999 4 5

    // (4)
    cout<<"(4) ";
    fl.erase_after(fl.before_begin());
    for (const int& i:fl) cout<<i<<' ';
    cout<<endl;
    // 輸出: (4) 1 2 3 999 4 5

    // (5)
    cout<<"(5) ";
    fl.remove(999);
    for (const int& i:fl) cout<<i<<' ';
    cout<<endl;
    // 輸出: (5) 1 2 3 4 5

    // (6)
    cout<<"(6) "<<distance(fl.begin(), fl.end())<<endl;
    // 輸出: (6) 5

    // (7)
    forward_list<int> fl2 = {100, 200, 300};
    {
        auto last = fl.before_begin();
        for (auto it = fl.begin(); it != fl.end(); it++) last = it;  // 走訪到最後一個元素的iterator
        fl.splice_after(last, fl2);
    }
    cout<<"(7) fl: "; for (const int& i:fl) cout<<i<<' '; cout<<endl;
    cout<<"    fl2: "; for (const int& i:fl2) cout<<i<<' '; cout<<endl;
    // 輸出: (7) fl: 1 2 3 4 5 100 200 300
    //          fl2: (空)

    // (8)
    cout<<"(8) ";
    fl.emplace_front(0);
    fl.emplace_after(fl.begin(), -1);
    for (const int& i:fl) cout<<i<<' ';
    cout<<endl;
    // 輸出: (8) 0 -1 1 2 3 4 5 100 200 300

    // (9)
    cout<<"(9) ";
    fl.sort(greater<int>());
    for (const int& i:fl) cout<<i<<' ';
    cout<<endl;
    // 輸出: (9) 300 200 100 5 4 3 2 1 0 -1

    // (10)
    cout<<"(10) ";
    fl.reverse();
    for (const int& i:fl) cout<<i<<' ';
    cout<<endl;
    // 輸出: (10) -1 0 1 2 3 4 5 100 200 300

    // (11)
    cout<<"(11) ";
    fl.remove_if([](int x){ return x >= 100; });
    for (const int& i:fl) cout<<i<<' ';
    cout<<endl;
    // 輸出: (11) -1 0 1 2 3 4 5

    // (12)
    {
        auto it = find(fl.begin(), fl.end(), 3);
        if (it != fl.end()){
            cout<<"(12) Found at index "<<distance(fl.begin(), it)<<endl;
        } else {
            cout<<"(12) Not Found"<<endl;
        }
    }
    // 輸出: (12) Found at index 4

    // (13)
    {
        int oddCnt = count_if(fl.begin(), fl.end(), [](int x){ return x % 2 != 0; });
        cout<<"(13) "<<oddCnt<<endl;
    }
    // 輸出: (13) 4   ( -1, 1, 3, 5 共4個奇數 )

    // (14)
    cout<<"(14) "<<accumulate(fl.begin(), fl.end(), 0)<<endl;
    // 輸出: (14) 14   ( -1+0+1+2+3+4+5 = 14 )

    // (15)
    forward_list<int> flA = {1,4,7}, flB = {2,5,8};
    flA.merge(flB);
    cout<<"(15) flA: "; for (const int& i:flA) cout<<i<<' '; cout<<endl;
    cout<<"    flB: "; for (const int& i:flB) cout<<i<<' '; cout<<endl;
    // 輸出: (15) flA: 1 2 4 5 7 8
    //          flB: (空)

    // (16)
    forward_list<int> flC = {1,2,3,4,5}, flD = {10,20,30,40,50};
    flC.splice_after(flC.begin(), flD, flD.begin());
    cout<<"(16) flC: "; for (const int& i:flC) cout<<i<<' '; cout<<endl;
    cout<<"    flD: "; for (const int& i:flD) cout<<i<<' '; cout<<endl;
    // 輸出: (16) flC: 1 20 2 3 4 5
    //          flD: 10 30 40 50

    // (17)
    forward_list<forward_list<int>> ff;
    ff.push_front(forward_list<int>{4,5,6});
    ff.push_front(forward_list<int>{1,2,3});
    cout<<"(17)"<<endl;
    for (const auto& row : ff){
        for (const int& j : row) cout<<j<<' ';
        cout<<endl;
    }
    /*
    輸出:
    (17)
    1 2 3
    4 5 6
    */

    // (18)
    ff.front().push_front(0);
    cout<<"(18)"<<endl;
    for (const auto& row : ff){
        for (const int& j : row) cout<<j<<' ';
        cout<<endl;
    }
    /*
    輸出:
    (18)
    0 1 2 3
    4 5 6
    */

    return 0;
}
