#include <iostream>
using namespace std;

// 成員類別（composition）
class Member {
public:
    Member() {
        cout << "Member constructor\n";
    }
    ~Member() {
        cout << "Member destructor\n";
    }
};

// Base class
class Base {
public:
    Base() {
        cout << "Base constructor\n";
    }
    virtual ~Base() {
        cout << "Base destructor\n";
    }
};

// Derived class
class Derived : public Base {
private:
    Member m;  // ⭐ composition
    int x;
public:
    Derived():x{123456789} {
        cout << "Derived constructor\n";
    }
    ~Derived() {
        cout << "Derived destructor\n";
    }
    void P(){
        cout<<"\n\nHIHIHI"<<x<<"\n\n";
    }
};

int main() {
    Base Jerry;
    cout<<'\n';
    Member Jeffery;
    cout<<'\n';
    Derived Gay;
    cout<<'\n';


    Base* ptr = new Derived();


    cout<<'\n';
    delete ptr;


    Gay.P();
}
