#include <string> // C++ standard string class
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

#include "CommissionEmployee.h"

using namespace std;



int main() {
   // instantiate a CommissionEmployee object     
   CommissionEmployee employee{"Sue", "Jones", "222-22-2222", 10000, .06};

   // get commission employee data
   cout << fixed << setprecision(2); // set floating-point formatting
   cout << "Employee information obtained by get functions: \n"
      << "\nFirst name is " << employee.getFirstName()
      << "\nLast name is " << employee.getLastName()
      << "\nSocial security number is "
      << employee.getSocialSecurityNumber()
      << "\nGross sales is " << employee.getGrossSales()
      << "\nCommission rate is " << employee.getCommissionRate() << endl;

   employee.setGrossSales(8000); // set gross sales      
   employee.setCommissionRate(.1); // set commission rate
   cout << "\nUpdated employee information from function toString: \n\n"
      << employee.toString();

   // display the employee's earnings
   cout << "\n\nEmployee's earnings: $" << employee.earnings() << endl;
}