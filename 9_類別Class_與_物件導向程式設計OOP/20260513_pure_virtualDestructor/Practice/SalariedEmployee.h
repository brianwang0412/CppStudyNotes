// --- SalariedEmployee.h ---
#include <string> // C++ standard string class
#include "Employee.h"

#ifndef SALARRIEDEMPLOYEE_H
#define SALARRIEDEMPLOYEE_H

class SalariedEmployee : public Employee {
public:
    SalariedEmployee(const std::string&, const std::string&, const std::string&,
        double = 0.0);
    virtual ~SalariedEmployee() = default; // virtual destructor
    void setWeeklySalary(double); // set weekly salary
    double getWeeklySalary() const; // return weekly salary
    virtual double earnings() const override; // calculate earnings
    virtual std::string toString() const override; // string representation
private:
    double weeklySalary; // salary per week
};

#endif