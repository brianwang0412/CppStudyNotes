#include<string>
#include "CommissionEmployee.h"

#ifndef BASEPLUSCOMMISSONEMPLOYEE_H
#define BASEPLUSCOMMISSONEMPLOYEE_H

class BasePlusCommissionEmployee : public CommissionEmployee{
   public:
      BasePlusCommissionEmployee(const std::string&, const std::string&,
         const std::string&, double = 0.0, double = 0.0, double =  0.0);
      /*
      void setFirstName(const std::string&); // set first name
      std::string getFirstName() const; // return first name

      void setLastName(const std::string&); // set last name
      std::string getLastName() const; // return last name

      void setSocialSecurityNumber(const std::string&); // set SSN
      std::string getSocialSecurityNumber() const; // return SSN

      void setGrossSales(double); // set gross sales amount
      double getGrossSales() const; // return gross sales amount

      void setCommissionRate(double); // set commission rate (percentage)
      double getCommissionRate() const; // return commission rate
      */
      void setBaseSalary(double); // set base salary
      double getBaseSalary() const; // return base salary
   
      virtual double earnings() const override; // calculate earnings
      virtual std::string toString() const override; // string representation
      // pure virtual 
   private:
   
      /*
      std::string firstName;
      std::string lastName;
      std::string socialSecurityNumber;
      double grossSales; // gross weekly sales
      double commissionRate; // commission percentage
      */
      double baseSalary; // base salary
    };

#endif