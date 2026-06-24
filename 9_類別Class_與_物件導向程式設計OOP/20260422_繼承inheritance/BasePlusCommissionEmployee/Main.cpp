#include <string> // C++ standard string class
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

#include "BasePlusCommissionEmployee.h"

using namespace std;



int main() {
   // instantiate a CommissionEmployee object     
   BasePlusCommissionEmployee employee{"Bob", "Lewis", "333-33-3333", 5000, .04, 300};

   // get commission employee data
   cout << fixed << setprecision(2); // set floating-point formatting
   cout << "Employee information obtained by get functions: \n"
      << "\nFirst name is " << employee.getFirstName()
      << "\nLast name is " << employee.getLastName()
      << "\nSocial security number is "
      << employee.getSocialSecurityNumber()
      << "\nGross sales is " << employee.getGrossSales()
      << "\nCommission rate is " << employee.getCommissionRate() 
      << "\nBase Salary is "<< employee.getBaseSalary() << endl;
   employee.setBaseSalary(1000);
   cout << "\nUpdated employee information from function toString: \n\n"
      << employee.toString();

   // display the employee's earnings
   cout << "\n\nEmployee's earnings: $" << employee.earnings() << endl;
}