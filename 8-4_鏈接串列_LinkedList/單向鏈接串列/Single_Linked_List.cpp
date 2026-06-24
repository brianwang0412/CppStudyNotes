#include<iostream>
using namespace std;

//《1. 定義節點》
struct Node{
    int data;
    Node *next = nullptr;
};
/*
先定義一個結構Node，作為這個鏈接串列的節點
Node內有兩個元素：data與next
data的型別為int，用來儲存整數資料
next為一個Node的指標變數，用來指向下一個Node
(白話：我們用next這個指標變數來儲存下一個節點的記憶體位址)
*/


int main(){
//《2-1. 建立鏈接串列(在「列尾」新增元素)》
    int num;
    Node *root = nullptr;  //root: 根結點、首個節點
    Node *now;

    cout<<"Input numbers, enter 0 to end>>\n";

    while (true){
        cin>>num;
        if (num==0) break;

        Node *newNode = new Node;  //建立一個新結點
        newNode->data = num;  //將輸入的資料存入新結點內    

        //如果root(根結點)還是空的，代表現在正在輸入第一個資料，那麼這個資料就是root(根結點)
        if (root == nullptr) 
            root = newNode;  
        
        //否則將新的節點與上一個節點連接起來
        else 
            now->next = newNode;
            
        now = newNode;  //更新now指向的位址
    }

    /*
    範例輸入
    10
    20
    30
    0
    */


cout<<"\n=================="<<"\n\n";//分隔線==========================================

//《2-1. 在「列首」新增元素》
    //num,now跟root前面已經宣告過了，可以直接用
    now = root;  

    cout<<"Input numbers>>\n";

    while (true){
        cin>>num;
        if (num==0) break;

        Node *newNode = new Node;  //建立一個新結點
        newNode->data = num;  //將輸入的資料存入新結點內    

        //直接在串列最前面插入元素，並更新root
        newNode->next = root;
        root = newNode;  //更新root指向的位址
    }

    /*
    範例輸入
    123
    456
    789
    0
    */

cout<<"\n=================="<<"\n\n";//分隔線==========================================


//《3. 遍歷並輸出整個鏈接串列》
    cout<<"Output : ";
    //從頭開始輸出
    now = root;
    while (now != nullptr){
        cout<<now->data<<' ';
        now = now->next;
    }
    cout<<endl;

    //範例輸出: 789 456 123 10 20 30 

cout<<"\n=================="<<"\n\n";//分隔線==========================================

//《4. 查詢 / 搜尋》
    int target;
    cout<<"Input number to search>>";
    cin>>target;

    now = root;
    int index = 0;
    bool found = false;
    while (now != nullptr){
        if (now->data == target){
            cout<<"Found "<<target<<" at index "<<index<<endl;
            found = true;
            break;
        }
        now = now->next;
        index++;
    }
    if (!found) cout<<"Not found"<<endl;

cout<<"\n=================="<<"\n\n";//分隔線==========================================

//《5. 取得長度》
    int Length=0;
    now = root;
    while (now!=nullptr){
        Length++;
        now = now->next;
    }
    cout<<"Length : "<<Length<<endl;


cout<<"\n=================="<<"\n\n";//分隔線==========================================

//《判斷是否為空》
    if (root == nullptr)
        cout<<"List is Empty"<<endl;
    else
        cout<<"List is not Empty"<<endl;

cout<<"\n=================="<<"\n\n";//分隔線==========================================

//《插入到指定位置》
    int pos, val;
    cout<<"Insert - Input position and value>>";
    cin>>pos>>val;

    if (pos < 0) {
        cout<<"Invalid position"<<endl;
    }
    else if (pos == 0) {
        Node *newNode = new Node;
        newNode->data = val;
        newNode->next = root;
        root = newNode;
    }
    else {
        now = root;
        for(int i=0; i<pos-1 && now!=nullptr; i++){
            now = now->next;
        }
        
        if (now == nullptr){
            cout<<"Position out of range"<<endl;
        }
        else {
            Node *newNode = new Node;
            newNode->data = val;
            newNode->next = now->next;
            now->next = newNode;
        }
    }
    
    // 顯示插入後的結果
    cout<<"List after insertion: ";
    now = root;
    while (now != nullptr){
        cout<<now->data<<' ';
        now = now->next;
    }
    cout<<endl;

cout<<"\n=================="<<"\n\n";//分隔線==========================================

//《修改節點內容》
    int modify_idx, modify_val;
    cout<<"Modify - Input index and new value>>";
    cin>>modify_idx>>modify_val;
    
    now = root;
    for(int i=0; i<modify_idx && now!=nullptr; i++){
        now = now->next;
    }
    
    if (now != nullptr){
        now->data = modify_val;
        cout<<"Modified successfully"<<endl;
    } else {
        cout<<"Index out of range"<<endl;
    }

    // 顯示修改後的結果
    cout<<"List after modification: ";
    now = root;
    while (now != nullptr){
        cout<<now->data<<' ';
        now = now->next;
    }
    cout<<endl;

cout<<"\n=================="<<"\n\n";//分隔線==========================================

//《刪除節點》
    int del_val;
    cout<<"Delete - Input value to delete>>";
    cin>>del_val;

    if (root == nullptr){
        cout<<"List is empty"<<endl;
    }
    else if (root->data == del_val){
        Node *temp = root;
        root = root->next;
        delete temp;
        cout<<"Deleted "<<del_val<<endl;
    }
    else {
        Node *prev = root;
        now = root->next;
        bool deleted = false;
        while (now != nullptr){
            if (now->data == del_val){
                prev->next = now->next;
                delete now;
                deleted = true;
                cout<<"Deleted "<<del_val<<endl;
                break;
            }
            prev = now;
            now = now->next;
        }
        if (!deleted) cout<<"Value not found"<<endl;
    }

    // 顯示刪除後的結果
    cout<<"List after deletion: ";
    now = root;
    while (now != nullptr){
        cout<<now->data<<' ';
        now = now->next;
    }
    cout<<endl;

cout<<"\n=================="<<"\n\n";//分隔線==========================================

//《清空整個Linked List》
    while (root != nullptr){
        Node *temp = root;
        root = root->next;
        delete temp;
    }
    cout<<"List cleared"<<endl;
}

//筆記大綱參考ChatGPT
//本篇筆記參考 台北市立松山高級中學112學年度學科能力競賽程式設計集訓講義 - Chen Haning 2023.07
//Created by B.J.Wang



/*
一個**完整的 Linked List**，除了「加入新節點（insert）」與「全部輸出（print）」之外，通常還應該具備以下功能：

### 1. 刪除節點（Delete）

* 依「值」刪除
* 依「位置（index）」刪除
* 刪除第一個節點（root）
* 刪除最後一個節點（tail）

### 2. 查詢 / 搜尋（Search / Find）

* 依值搜尋是否存在
* 回傳節點位置或指標

### 3. 取得長度（Size / Length)

* 回傳目前 linked list 中節點數量

### 4. 判斷是否為空（Is Empty）

* 常用於避免對空串列做非法操作

### 5. 插入到指定位置（Insert at Position）

* 在第 k 個位置插入新節點

### 6. 修改節點內容（Update）

* 依位置或依值修改節點資料

### 7. 取得特定節點

* 取得第 k 個節點
* 取得第一個 / 最後一個節點

### 8. 清空整個 Linked List（Clear / Destroy）

* 釋放所有節點記憶體

---

### 最基本「必備」版本（作業或考試常見）

通常至少要有：

* insert
* delete
* search
* traverse
* size
* isEmpty

*/