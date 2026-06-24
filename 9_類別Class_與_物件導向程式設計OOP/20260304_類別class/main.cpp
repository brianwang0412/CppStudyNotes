#include<iostream>
#include<string>
using namespace std;

class Account{
private:
    string name = "Default";
    int balance = 0;
public:
    Account(){}
    //可以初始化，Account(){name="unknow";}
    Account(string accountName) : name{accountName} {}
    Account(string accountName, int initialBalance){
        name = accountName;
        if (initialBalance > 0)
            balance = initialBalance;
    }
    /*
    Contructor可多型
    同時可以用
    Account myAccount;
    Account myAccount1{"City Boy"};
    Account myAccount2{"Rich Guy", 1000000};
    */


    void setName(string accountName){
        name = accountName;
    }
    string getName() const{
        return name;
    }
    int getBalance() const{
        return balance;
    }
    void deposit(int depositAmount){
        //存款(需>0)
        if (depositAmount>0){
            balance += depositAmount;
        }
    }
};

int main(){
    Account myAccount;
    
    cout<<"Initial account Name: "<<myAccount.getName()<<endl;
    myAccount.setName("Brian");
    cout<<"After setName: "<<myAccount.getName()<<endl<<endl;

    Account myAccount1{"City Boy"};
    cout<<myAccount1.getName()<<endl<<endl;

    Account myAccount2{"Rich Guy", 1000000};
    cout<<myAccount2.getName()<<endl;
    cout<<myAccount2.getBalance()<<endl;
    myAccount2.deposit(1);
    cout<<myAccount2.getBalance()<<endl;
}