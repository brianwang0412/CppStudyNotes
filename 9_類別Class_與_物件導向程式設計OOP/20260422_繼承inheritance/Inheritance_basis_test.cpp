#include <iostream>
using namespace std;

/*
較公開 <---------------> 較私人
public    protected    private
*/

// 基類
class Base {
public:
    int publicVar = 1;
protected:
    int protectedVar = 2;
private:
    int privateVar = 3;
};

//繼承方式預設為private

/*
衍生類別不會繼承
1. 基類別的建構子、解構子和複製建構子
2. 基類別的重載運算子
3. 基類別的 Friend Function
*/

// 公有(public)繼承
// 最高層級為public
/*
public    -> public
protected -> protected
private   -> private  (衍生類別無法存取基類別的private)
*/
class PublicDerived : public Base {
public:
    void show() {
        cout << "Public Inheritance:" << endl;
        cout << "publicVar = " << publicVar << endl;      // 還是 public
        cout << "protectedVar = " << protectedVar << endl; // 還是 protected
        // cout << "privateVar = " << privateVar; // 無法存取
        cout << endl;
    }
};

// 保護(protected)繼承
// 最高層級為protected
/*
public    -> protected
protected -> protected
private   -> private  (衍生類別無法存取基類別的private)
*/
class ProtectedDerived : protected Base {
public:
    void show() {
        cout << "Protected Inheritance:" << endl;
        cout << "publicVar = " << publicVar << endl;      // 變成 protected
        cout << "protectedVar = " << protectedVar << endl; // 還是 protected
        // cout << "privateVar = " << privateVar; // 無法存取
        cout << endl;
    }
};

// 私有(private)繼承
// 最高層級為private
/*
public    -> private
protected -> private
private   -> private (衍生類別無法存取基類別的private)
*/
class PrivateDerived : private Base {
public:
    void show() {
        cout << "Private Inheritance:" << endl;
        cout << "publicVar = " << publicVar << endl;      // 變成 private
        cout << "protectedVar = " << protectedVar << endl; // 變成 private
        // cout << "privateVar = " << privateVar; // 無法存取
        cout << endl;
    }
};

int main() {
    PublicDerived pub;
    ProtectedDerived prot;
    PrivateDerived priv;

    pub.show();
    // cout << pub.publicVar; // 可直接存取 public 成員
    // cout << pub.protectedVar; // 無法存取 (因為 protected)

    prot.show();
    // cout << prot.publicVar; // 無法存取 (因為變 protected)

    priv.show();
    // cout << priv.publicVar; // 無法存取 (因為變 private)

    return 0;
}

// 本篇筆記參考 https://hackmd.io/@LukeTseng/ByMEuaKoJe