#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class CommissionEmployee {
private:
    string mFirstName;
    string mLastName;
    double mGrossSales;
    double mCommissionRate;

public:
    CommissionEmployee() {
        mFirstName = "";
        mLastName = "";
        mGrossSales = 0.0;
        mCommissionRate = 0.0;
    }

    CommissionEmployee(string firstName, string lastName, double grossSales, double commissionRate) {
        setFirstName(firstName);
        setLastName(lastName);
        setGrossSales(grossSales);
        setCommissionRate(commissionRate);
    }

    void setFirstName(string firstName) {
        mFirstName = firstName;
    }

    void setLastName(string lastName) {
        mLastName = lastName;
    }

    void setGrossSales(double grossSales) {
        if (grossSales >= 0) {
            mGrossSales = grossSales;
        } else {
            mGrossSales = 0.0;
        }
    }

    void setCommissionRate(double commissionRate) {
        if (commissionRate >= 0 && commissionRate <= 1) {
            mCommissionRate = commissionRate;
        } else {
            mCommissionRate = 0.0;
        }
    }

    string getFirstName() {
        return mFirstName;
    }

    string getLastName() {
        return mLastName;
    }

    double getGrossSales() {
        return mGrossSales;
    }

    double getCommissionRate() {
        return mCommissionRate;
    }

    double earnings() {
        return mGrossSales * mCommissionRate;
    }

    void display() {
        cout << fixed << setprecision(2);
        cout << "Commission Employee" << endl;
        cout << "Name: " << mFirstName << " " << mLastName << endl;
        cout << "Gross Sales: " << mGrossSales << endl;
        cout << "Commission Rate: " << mCommissionRate << endl;
        cout << "Earnings: " << earnings() << endl;
        cout << endl;
    }
};

class BasePlusCommissionEmployee : public CommissionEmployee {
    
    //作答區開始
    private:
        double salary;
    public:
        BasePlusCommissionEmployee(string firstName, string lastName, double grossSales, double commissionRate, double baseSalary)
            : CommissionEmployee(firstName, lastName, grossSales, commissionRate), salary{baseSalary} {}
        
        double earnings(){
            return (salary + CommissionEmployee::earnings());
        }
        
        void display(){
            cout<<fixed<<setprecision(2)
                << "Base Plus Commission Employee\n"
                << "Name: "<< getFirstName() << ' ' << getLastName() <<'\n'
                << "Gross Sales: " << getGrossSales() <<'\n'
                << "Commission Rate: " << getCommissionRate() <<'\n'
                << "Base Salary: " << salary <<'\n'
                << "Earnings: " << earnings() <<endl;
        }

    //作答區結束

};

int main() {
    string firstName, lastName;
    double grossSales, commissionRate, baseSalary;

    cin >> firstName >> lastName >> grossSales >> commissionRate >> baseSalary;

    CommissionEmployee employee(firstName, lastName, grossSales, commissionRate);

    BasePlusCommissionEmployee baseEmployee(
        firstName, lastName, grossSales, commissionRate, baseSalary
    );

    employee.display();
    baseEmployee.display();

    return 0;
}

// 本篇筆記為嘉義大學資訊工程學系物件導向程式設計之課堂題目
// //Created by B.J.Wang 20260609