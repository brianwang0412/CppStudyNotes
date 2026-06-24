// --- main.cpp ---
#include <iostream>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "SalariedEmployee.h"
#include "CommissionEmployee.h"
#include "BasePlusCommissionEmployee.h"
using namespace std;

void virtualviaPointer(const Employee* const); // prototype
void virtualviaReference(const Employee&); // prototype

int main() {
    cout << fixed << setprecision(2); // set floating-point formatting
    
    // create derived-class objects
    SalariedEmployee salariedEmployee("John", "Smith", "111-11-1111", 800);
    CommissionEmployee commissionEmployee("Sue", "Jones", "222-22-2222", 10000, .06);
    BasePlusCommissionEmployee basePlusCommissionEmployee("Bob", "Lewis", "333-33-3333", 5000, .04, 300);

    // output each Employee information and earnings using static binding
    cout << "EMPLOYEES PROCESSED INDIVIDUALLY USING STATIC BINDING\n\n"
        << salariedEmployee.toString() << "\nearned $" << salariedEmployee.earnings() << "\n\n"
        << commissionEmployee.toString() << "\nearned $" << commissionEmployee.earnings() << "\n\n"
        << basePlusCommissionEmployee.toString() << "\nearned $" << basePlusCommissionEmployee.earnings() << "\n\n";

    // create and initialize vector of three base-class pointers
    vector<Employee*> employees{ &salariedEmployee, &commissionEmployee,&basePlusCommissionEmployee};

    cout << "EMPLOYEES PROCESSED POLYMORPHICALLY VIA DYNAMIC BINDING\n\n";

    // call virtualviaPointer to print each Employee's information
    // and earnings using dynamic binding
    cout << "VIRTUAL FUNCTION CALLS MADE OFF BASE-CLASS POINTERS\n";

    for (const Employee* employeePtr : employees)
        virtualviaPointer(employeePtr);

    // call virtualviaReference to print each Employee's information
    // and earnings using dynamic binding
    cout << "VIRTUAL FUNCTION CALLS MADE OFF BASE-CLASS REFERENCES\n";

    for (const Employee* employeeRef : employees)
        virtualviaReference(*employeeRef);
}


// call Employee virtual functions toString and earnings off a
// base-class pointer using dynamic binding
void virtualviaPointer(const Employee* const baseClassPtr) {
    cout << baseClassPtr->toString() << "\nearned $" << baseClassPtr->earnings() << "\n\n";
}

// call Employee virtual functions toString and earnings off a
// base-class reference using dynamic binding
void virtualviaReference(const Employee& baseClassRef) {
    cout << baseClassRef.toString() << "\nearned $" << baseClassRef.earnings() << "\n\n";
}
