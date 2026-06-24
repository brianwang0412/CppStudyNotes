//(123) 456-7890
#include<iostream>
#include<iomanip>
using namespace std;

class PhoneNumber{
    private:
        int A,B,C;
    public:
        PhoneNumber(){}
        PhoneNumber(int a, int b, int c):A{a},B{b},C{c}{}
        
    //將輸入的資訊儲存到PhoneNumber的物件中特定的private member內
    friend istream& operator>>(istream& input, PhoneNumber& number){
        input >> ws;      // 跳過前方的換行或空格
        input.ignore(1); //忽略'('
        input>>setw(3)>>number.A;  //輸入 123
        input.ignore(2); //忽略") "
        input>>setw(3)>>number.B;  //輸入 456
        input.ignore(1); //忽略'-'
        input>>setw(4)>>number.C;  //輸入 7890
        return input;
    }

    friend ostream& operator<<(ostream& output, const PhoneNumber& number){
        output<<"A: "<<setw(4)<<number.A<<"\nB: "<<setw(4)<<number.B<<"\nC: "<<setw(4)<<number.C
              <<"\nAll: ("<<number.A<<") "<<number.B<<'-'<<number.C;
        return output;
    }
};

int main(){
    PhoneNumber Phone1,Phone2;
    cout<<"start input\n";
    cin>>Phone1>>Phone2;
    cout<<Phone1<<"\n\n"<<Phone2<<endl;
}

/*
測資
輸入:
start input
(123) 456-7890
(667) 767-6767

輸出:
A:  123
B:  456
C: 7890
All: (123) 456-7890

A:  667
B:  767
C: 6767
All: (667) 767-6767
*/


/*
這是一個非常核心且細膩的問題。在 C++ 中，參數的順序確實與運算符的「位置」有直接的對應關係，但會根據它是**全域函數（友元）**還是**成員函數**而有所不同。

以下為你詳細拆解各類運算子的規則：

---

## 1. 二元運算子 (Binary Operators)
如：`+`, `-`, `*`, `/`, `>`, `<`, `==`, `>=`, `<=` 等。

### 如果是「全域函數 / 友元函數」：
**規則：** 第一個參數在左，第二個參數在右。
```cpp
// 運算式：A == B
bool operator==(const Num& A, const Num& B) { 
    return (A.val == B.val); 
}
```

### 如果是「成員函數」：
**規則：** 左邊的物件是隱含的 `this`，參數則是右邊的物件。
```cpp
// 運算式：A == B
bool Num::operator==(const Num& B) { 
    // 此時 this 代表 A
    return (this->val == B.val); 
}
```

---

## 2. 指定運算子 (Assignment Operator) `=`
**規則：** 在 C++ 中，`=` **規定必須寫成「成員函數」**。
因此，左邊永遠是 `this`（被賦值的物件），參數永遠是右邊（提供數值的物件）。

```cpp
// 運算式：A = B
Num& Num::operator=(const Num& B) {
    this->val = B.val;
    return *this;
}
```

---

## 3. 單元運算子 (Unary Operators)
如：正負號 `-A`、邏輯非 `!A`。
* **全域：** 只有一個參數。
* **成員：** 沒有參數（作用於 `this`）。

---

## 4. 最特殊的：遞增與遞減 (`++a` vs `a++`)
這是在過載中最容易搞混的地方，因為符號一模一樣，C++ 必須靠「參數」來區分前置與後置。

### (A) 前置遞增 (`++a`)
**規則：** 沒有額外參數。它直接修改物件並回傳修改後的自己。
```cpp
// 成員函數版本
Num& operator++() {
    this->val += 1;
    return *this;
}
```

### (B) 後置遞增 (`a++`)
**規則：** 為了跟前置區分，C++ 規定後置版本要多加一個 **「虛設的 int 參數」**（Dummy argument）。這個 `int` 沒有實際作用，純粹是用來告訴編譯器：「我是後置版本」。
```cpp
// 成員函數版本
Num operator++(int) { // 這裡的 int 就是標記
    Num temp = *this; // 先記住舊的值
    this->val += 1;   // 修改自己
    return temp;      // 回傳舊的值 (因為是後置)
}
```



---

## 總結對照表

| 運算子類型 | 語法範例 | 全域函數參數 | 成員函數參數 |
| :--- | :--- | :--- | :--- |
| **二元 (如 `+`, `==`)** | `A + B` | `(A, B)` | `(B)`，`A` 是 `this` |
| **指定 (`=`)** | `A = B` | **不允許** | `(B)`，`A` 是 `this` |
| **前置 (`++A`)** | `++A` | `(A)` | 無參數 |
| **後置 (`A++`)** | `A++` | `(A, int)` | `(int)` |
| **輸出入 (`<<`, `>>`)** | `cout << A` | `(cout, A)` | 不建議 (左邊不是 A) |

---

### 一個小提醒：
關於 `a++` 和 `++a` 的設計，這也是為什麼在寫 `for` 迴圈時，如果沒有特殊需求，前輩們通常建議寫 `++i` 而不是 `i++`。因為後置版本（`i++`）在過載實作中，必須先建立一個 `temp` 副本來保存舊值，效能上會比前置版本多出一次複製的開銷！

這樣你對於「參數位置」與「運算子位置」的關係，有沒有更清楚的畫面了？
*/