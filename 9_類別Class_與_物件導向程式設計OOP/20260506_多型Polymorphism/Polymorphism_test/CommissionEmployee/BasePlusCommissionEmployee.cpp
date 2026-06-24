#include <string> // C++ standard string class
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>


#include "BasePlusCommissionEmployee.h"

using namespace std;

// constructor                                                        
BasePlusCommissionEmployee::BasePlusCommissionEmployee(const string& first,
   const string& last, const string& ssn, double sales, double rate, double salary) 
   : CommissionEmployee(first, last, ssn, sales, rate){

   // 用superclass的constructor來簡化
   setBaseSalary(salary);
}
/*
// set first name
void BasePlusCommissionEmployee::setFirstName(const string& first) {
   firstName = first; // should validate
}

// return first name
string BasePlusCommissionEmployee::getFirstName() const { return firstName; }

// set last name
void BasePlusCommissionEmployee::setLastName(const string& last) {
   lastName = last; // should validate
}

// return last name
string BasePlusCommissionEmployee::getLastName() const { return lastName; }

// set social security number
void BasePlusCommissionEmployee::setSocialSecurityNumber(const string& ssn) {
   socialSecurityNumber = ssn; // should validate
}

// return social security number
string BasePlusCommissionEmployee::getSocialSecurityNumber() const {
   return socialSecurityNumber;
}

// set gross sales amount
void BasePlusCommissionEmployee::setGrossSales(double sales) {
   if (sales < 0.0) {
      throw invalid_argument("Gross sales must be >= 0.0");
   }

   grossSales = sales;
}

// return gross sales amount
double BasePlusCommissionEmployee::getGrossSales() const { return grossSales; }

// set commission rate
void BasePlusCommissionEmployee::setCommissionRate(double rate) {
   if (rate <= 0.0 || rate >= 1.0) {
      throw invalid_argument("Commission rate must be > 0.0 and < 1.0");
   }

   commissionRate = rate;
}

// return commission rate
double BasePlusCommissionEmployee::getCommissionRate() const {
   return commissionRate;
}
*/

// set base salary
void BasePlusCommissionEmployee::setBaseSalary(double salary){
   if (salary < 0.0){
      throw invalid_argument("Salary must be >= 0.0");
   }
   baseSalary = salary;
}

// return base salary
double BasePlusCommissionEmployee::getBaseSalary() const{
   return baseSalary;
}


// calculate earnings
double BasePlusCommissionEmployee::earnings() const {
    return getBaseSalary() + CommissionEmployee::earnings();
}

// return string representation of BasePlusCommissionEmployee object
string BasePlusCommissionEmployee::toString() const {
    ostringstream output;
    output << "base-salaried " << CommissionEmployee::toString()
        << "\nbase salary: " << getBaseSalary();
    return output.str();
}