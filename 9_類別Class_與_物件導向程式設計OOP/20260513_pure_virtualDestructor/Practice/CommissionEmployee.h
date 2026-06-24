// --- CommissionEmployee.h ---
#include <string> // C++ standard string class
#include "Employee.h"

#ifndef COMMISSIONEMPLOYEE_H
#define COMMISSIONEMPLOYEE_H

class CommissionEmployee : public Employee {
public:
    CommissionEmployee(const std::string&, const std::string&, const std::string&,
        double = 0.0, double = 0.0);
    virtual ~CommissionEmployee() = default; // virtual destructor
    void setCommissionRate(double); // set commission rs
    double getCommissionRate() const; // return commission rate
    void setGrossSales(double); // set gross sales amount
    double getGrossSales() const; // return gross sales amount
    virtual double earnings() const override; // calculate earnings
    virtual std::string toString() const override; // string representation
private:
    double grossSales; // gross weekly sales
    double commissionRate; // commission percentage
};

#endif