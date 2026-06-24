#include<iostream>
using namespace std;

struct Node{
    int data = NULL;
    Node *prev = nullptr;
    Node *next = nullptr;
};


int main(){
    int num;
    Node *root = new Node;
    Node *now = root;

    cout<<"Input numbers>>\n";

    while (cin>>num){
        if (now->data == NULL){ //代表現在正要加入第一個元素
            now->data=num;
        }

        else{ //代表前面已經加入過元素
            //先搞定這個節點，再去跟前面的接起來
            Node *newNode = new Node;
            newNode->data = num;
            newNode->prev = now;

            now->next = newNode;
            now=newNode; //此時now指向的位址的data有東西,next是nullptr
        }
    }

    Node *tail = now; //將最後一個節點的位址存起來

    cout<<"Output"<<endl;
    //從頭開始輸出
    now = root;
    while (now != nullptr){
        cout<<now->data<<endl;
        now = now->next;
    }

    cout<<"\nOutput"<<endl;
    //從尾開始輸出
    now = tail;
    while (now != nullptr){
        cout<<now->data<<endl;
        now = now->prev;
    }
}

//Created by B.J.Wang