#include<vector>

#include<iostream>
using namespace std;

/*
push_back：把元素加到尾巴，必要時會進行記憶體配置
pop_back：移除尾巴的元素
insert：插入元素
erase：移除某個位置元素, 也可以移除某一段範圍的元素
clear：清空容器裡所有元素
size：回傳目前長度
empty：回傳是否為空
[i]：隨機存取索引值為i的元素，跟陣列一樣索引值從 0 開始
at(i)：隨機存取索引值為i的元素，跟上面 operator[] 差異是 at(i) 會作邊界檢查，存取越界會拋出一個例外
reserve()：預先配置大小
*/

int main(){
    // 1. 宣告
    vector<int>v;
    
}