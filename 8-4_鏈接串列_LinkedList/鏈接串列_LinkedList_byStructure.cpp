#include<iostream>
using namespace std;

//linked list 可以將資料儲存在「不連續」的記憶體空間中

//本篇目標：建立一個「單向」的Linked List


//《1. 定義一個結構》
struct Node{
    int data;   //用來儲存這個元素的值
    Node* next; //建立一個指向「下一個元素」的指標
};


//《2. 建立新的節點》
Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;  //「->」專門用在指標，這行程式代表取出newNode中的data這個元素，並將其賦值為value
    newNode->next = nullptr;
    return newNode;
}


//《3. 在串首插入新節點》
void insertFront(Node*& head, int value) {
    Node* newNode = createNode(value);
    newNode->next = head;  // 新節點指向原本的head
    head = newNode;        // head 指到新節點
}


//《4. 輸出整個linked list》
void printList(Node* head) {
    Node* current = head; //從頭開始輸出
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}


//《5. 刪除整個linked list》
void deleteList(Node*& head) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;        // 釋放節點
    }
    head = nullptr;
}


int main() {
    Node* head = nullptr;   // 空的 linked list

    insertFront(head, 10);
    insertFront(head, 20);
    insertFront(head, 30);

    printList(head);   // 輸出：30 20 10

    deleteList(head);  // 釋放記憶體

    return 0;
}



//本篇筆記參考ChatGPT
//Created by B.J.Wang




/*
(by ChatGPT)
Q: struct Node 算是定義了一個新的資料型態嗎

是，但我幫你拆成幾個觀點讓你更準確理解，不會只停在「是/不是」這種粗略回答。

---

# **1. 語言層面：是的，它定義了一個新的型別（user-defined type）**

```cpp
struct Node {
    int data;
    Node* next;
};
```

這行結束後：

* `Node` 就成為 C++ 中一個 **新的資料型別名稱**。
* 你可以像用 `int`、`double` 一樣用它：

  ```cpp
  Node a;        // 用 Node 宣告變數
  Node* p;       // 指向 Node 的指標
  Node arr[10];  // Node 陣列
  ```

所以在語意上，`Node` 就是 **你自己創造的型別**。

---

# **2. 與內建型別的差異**

雖然 `Node` 是一個新型別，但它不是原生型別（primitive），而是**複合型別（composite type）**：

* 內部可以包含多個成員（data + next）
* 編譯器自動生成建構子、copy/move、destructor（若你沒有自訂）
* 有自己的大小（`sizeof(Node)`）
* 可以被當作函式參數、回傳值、模板參數

它的本質與 class 沒差，只是預設成員可見性不同。

---

# **3. 型別層級結論**

當你寫：

```cpp
struct Node { ... };
```

你做了三件事：

1. **建立一個型別名稱: `Node`**
2. **定義這個型別的記憶體結構（layout）**
3. **定義這個型別的成員（data members, function members 也可以有）**

這和：

```cpp
class Node { ... };
```

除了默認 public / private 不同外，語意完全一致。

---

# **4. 多方觀點整理（依照你要求的多角度）**

### ✦ 使用者角度（寫程式的人）

是「自訂型別」，用來描述你要的資料結構。

### ✦ 編譯器角度

它是 **一個新的 type name** 加上一份 **layout 描述**。
編譯器會：

* 分配記憶體大小
* 決定對齊（alignment）
* 自動生成 copy/move/destructor（如果需要）

### ✦ 記憶體觀點

`Node` 的大小 = 成員大小 + padding（編譯器為對齊加入的空隙）
例如：

```
int data;    // 4 bytes
Node* next;  // 8 bytes (on 64-bit)
Total: 16 bytes (通常)
```

### ✦ 程式設計觀點

是「用程式語言擴充語言本身型別系統」的方式。

---

# **總結**

**是，`struct Node` 的確是在 C++ 裡定義了一個新的資料型態。**
而且它與 `class` 能做的事情一樣，只是預設成員可見性是 public。
*/