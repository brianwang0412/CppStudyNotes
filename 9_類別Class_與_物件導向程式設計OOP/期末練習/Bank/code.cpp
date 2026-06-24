#include <iostream>
#include <string>
using namespace std;


// 作答區開始
class BankAccount{
    private:
        string name;
        int balance;
    public:
        BankAccount(string Name, int Balance) : name{Name}, balance{Balance} {}
        
        string getName(){return name;}
        int getBalance(){return balance;}
        
        
        void deposit(int money){
            balance += money;
        }
        
        bool withdraw(int money){
            if (money<=balance){
                balance-=money;
                return true;
            }
            else return false;
        }
};
// 作答區結束

int main() {
    string name;
    int balance, depositMoney, withdrawMoney;

    cin >> name >> balance >> depositMoney >> withdrawMoney;

    BankAccount acc(name, balance);

    acc.deposit(depositMoney);

    if (!acc.withdraw(withdrawMoney)) {
        cout << "Withdraw failed" << endl;
    }

    cout << "Name: " << acc.getName() << endl;
    cout << "Balance: " << acc.getBalance() << endl;

    return 0;
}

// 本篇筆記為嘉義大學資訊工程學系物件導向程式設計之課堂題目
// //Created by B.J.Wang 20260609