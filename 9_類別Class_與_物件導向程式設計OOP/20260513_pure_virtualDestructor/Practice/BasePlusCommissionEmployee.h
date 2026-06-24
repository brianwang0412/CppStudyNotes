// --- BasePlusCommissionEmployee.h ---
#include <string> // C++ standard string class
#include "CommissionEmployee.h" // CommissionEmployee class definition

#ifndef BASEPLUSCOMMISSIONEMPLOYEE_H
#define BASEPLUSCOMMISSIONEMPLOYEE_H

class BasePlusCommissionEmployee : public CommissionEmployee {
public:
    BasePlusCommissionEmployee(const std::string&, const std::string&, const std::string&,
        double = 0.0, double = 0.0, double = 0.0);
    virtual ~BasePlusCommissionEmployee() = default; // virtual destructor
    void setBaseSalary(double); // set base salary
    double getBaseSalary() const; // return base salary
    virtual double earnings() const override; // calculate earnings
    virtual std::string toString() const override; // string representation
private:
    double baseSalary; // base salary per week
};

#endif