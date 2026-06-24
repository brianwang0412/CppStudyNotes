/*
這是一個很棒的學習目標。為了讓你在 VSCode 中能實際敲打程式碼並觀察編譯器的行為，我為你設計了一個以「開放世界遊戲物件」為背景的程式實作練習，並準備了一組觀念測驗來幫助你鞏固理論基礎。

### 程式實作練習題：遊戲實體繼承系統

請在你的開發環境中開啟一個新的 C++ 檔案，並嘗試實作以下三個步驟。這個練習的核心在於**觀察編譯器在哪裡會報錯**，請試著取消註解某些行，看看會發生什麼事。

**第一步：定義基底類別 `GameObject`**
請設計一個 `GameObject`，並包含三種不同存取層級的成員：
* **public**: `std::string name;` (物件名稱)
* **protected**: `int health;` (耐久度或生命值)
* **private**: `int internalID;` (系統內部的流水號，不允許外部直接更動)
請為它寫一個建構子來初始化這三個變數。

**第二步：設計三個衍生類別**
1.  **`Player`（玩家）**：使用 **`public`** 繼承 `GameObject`。
    * 實作一個成員函式 `void TakeDamage(int amount)`，在裡面嘗試減少 `health`。
    * 嘗試在裡面讀取 `internalID`，看看編譯器是否允許。
2.  **`Chest`（寶箱）**：使用 **`protected`** 繼承 `GameObject`。
    * 實作一個成員函式 `void Open()`，在裡面印出 `name` 與 `health`。
3.  **`TriggerArea`（觸發區域）**：使用 **`private`** 繼承 `GameObject`。
    * 實作一個成員函式 `void Activate()`，在裡面印出 `name`。

**第三步：在 `main()` 函式中進行存取測試**
實例化這三個類別的物件，並嘗試在 `main()` 中進行以下操作（預期某些操作會觸發編譯錯誤，請透過這些錯誤來驗證你的理解）：
* 嘗試存取 `Player` 物件的 `name`。
* 嘗試存取 `Player` 物件的 `health`。
* 嘗試存取 `Chest` 物件的 `name`。
* 嘗試存取 `TriggerArea` 物件的 `name`。

---

### 觀念隨堂測驗

除了寫程式，理解這三種繼承的存取權限變化也非常重要。這是一份針對 C++ 繼承機制的測驗，可以幫助你釐清容易混淆的觀念。

*/

#include<iostream>
#include<string>
using namespace std;

class GameObject{
    public:
        string name;
    protected:
        int health;
    private:
        int internalID;
    
    public:
        GameObject(string N, int H, int I)
        :name{N}, health{H}, internalID{I}{}
};

class Player : public GameObject{
    public:
        Player(string N, int H, int I) : GameObject(N, H, I){}

        void TakeDamage(int amount){
            health -= amount;
        }
};

class Chest : protected GameObject{
    public:
    Chest(string N, int H, int I) : GameObject(N, H, I){}

        void Open(){
            cout<<name<<" HP: "<<health<<'\n';
        }
};

class TriggerArea : private GameObject{
    public:
    TriggerArea(string N, int H, int I) : GameObject(N, H, I){}

        void Active(){
            cout << name << '\n';
        }
};

int main(){
    Player P1("Allen", 100, 10001);
    Chest C1("Golden Chest", 1, 10011);
    TriggerArea TA1("Boss Room", 0, 10111);

    cout<<P1.name<<'\n';
    cout<<P1.health

}