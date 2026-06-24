#include<iostream>
#include<string>
using namespace std;

/*我的看法
Q: 什麼是structure(結構)?
A: 就是一種自定義的資料型態，跟int,float,bool等同個用法
    不同的地方在於結構內能「存放多個不同型態的元素」(甚至是別的結構)，不像int只能儲存整數...
*/

/*語法

struct 結構名稱{
    資料型態 成員1;
    資料型態 成員2;
    ...
};

*/

//《建立結構》

//建立一個結構Student，其中有整數型態的Student_ID與字串name
struct Student{
    int Student_ID; //學號
    string name; //名字
};

//建立一個結構ExamScore，其中有兩個整數元素Cpp與Python
struct ExamScore{
    int Cpp;
    int Python;
};

//建立一個結構FullRecord，其中有兩個「結構」Student類別的info與Examscore類別的score
//info內有Student_ID與name, score內有Cpp與Python
struct FullRecord{
    Student info;
    ExamScore score;
};

int main(){
//《使用結構》

    Student me; //或 struct Student me;
    me.Student_ID=1142935;
    me.name="Brian";
    ExamScore final;
    final.Cpp=100;
    final.Python=100;

    cout<<"Name : "<<me.name<<endl;
    cout<<"ID : "<<me.Student_ID<<endl;
    cout<<"Cpp score : "<<final.Cpp<<endl;
    cout<<"Python score : "<<final.Python<<endl;
    /*
    輸出:
    Name : Brian
    ID : 1142935
    Cpp score : 100
    Python score : 100
    */

    cout<<"\n===================\n\n";

    FullRecord Paul;
    Paul.info.Student_ID = 1142911;
    Paul.info.name = "Other Guy";
    Paul.score.Cpp = 0;
    Paul.score.Python = 70;

    cout<<"Name : "<<Paul.info.name<<endl;
    cout<<"ID : "<<Paul.info.Student_ID<<endl;
    cout<<"Cpp score : "<<Paul.score.Cpp<<endl;
    cout<<"Python score: "<<Paul.score.Python<<endl;
    /*
    輸出:
    Name : Other Guy
    ID : 1142911
    Cpp score : 0
    Python score: 70
    */


    cout<<"\n===================\n\n";
//《比較結構內的元素》

    //結構只能用裡面的每一項單獨拿出來比較，不能直接用兩個結構來比
    cout<<"Is our ID the same?  "<<(me.Student_ID==Paul.info.Student_ID)<<endl;
    cout<<"Is my Cpp score better?  "<<(final.Cpp>Paul.score.Cpp)<<endl;

    /*輸出
    Is our ID the same?  0
    Is my Cpp score better?  1
    */
}

//本篇筆記參考嘉義大學資訊工程學系許政穆老師的授課內容與講義
//Created by B.J.Wang 2025/12/16