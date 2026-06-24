// --- SalariedEmployee.cpp ---
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "SalariedEmployee.h" // SalariedEmployee class definition
using namespace std;

SalariedEmployee::SalariedEmployee(const string& first, const string& last,
    const string& ssn, double salary) : Employee(first, last, ssn) {
    setWeeklySalary(salary);
}

void SalariedEmployee::setWeeklySalary(double salary) {
    if (salary < 0.0)
        throw invalid_argument("Weekly salary must be >= 0.0");
    weeklySalary = salary;
}

double SalariedEmployee::getWeeklySalary() const { return weeklySalary; }

double SalariedEmployee::earnings() const { return getWeeklySalary(); }

string SalariedEmployee::toString() const {
    ostringstream output;
    output << fixed << setprecision(2);
    output << "salaried employee: " << Employee::toString() <<
        "\nweekly salary: " << getWeeklySalary();
    return output.str();
}