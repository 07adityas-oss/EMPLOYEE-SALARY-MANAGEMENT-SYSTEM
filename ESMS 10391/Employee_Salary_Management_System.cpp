#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Employee class demonstrates encapsulation, constructors and member functions.
class Employee {
private:
    int employeeId;
    string employeeName;
    string designation;
    double basicSalary;
    double taRate;
    double daRate;
    double hraRate;
    int leavesTaken;
    double commissionRate;

public:
    // Default constructor
    Employee() {
        employeeId = 0;
        employeeName = "Not Set";
        designation = "Not Set";
        basicSalary = 0.0;
        taRate = 0.0;
        daRate = 0.0;
        hraRate = 0.0;
        leavesTaken = 0;
        commissionRate = 0.0;
    }

    // Parameterized constructor
    Employee(int id, string name, string post, double basic,
             double ta, double da, double hra, int leaves, double commission) {
        employeeId = id;
        employeeName = name;
        designation = post;
        basicSalary = basic;
        taRate = ta;
        daRate = da;
        hraRate = hra;
        leavesTaken = leaves;
        commissionRate = commission;
    }

    // Member function to calculate salary components
    double calculateTA() const { return basicSalary * taRate / 100.0; }
    double calculateDA() const { return basicSalary * daRate / 100.0; }
    double calculateHRA() const { return basicSalary * hraRate / 100.0; }
    double calculateCommission() const { return basicSalary * commissionRate / 100.0; }

    // Assumption: each unpaid leave deducts 1/30th of basic salary.
    double calculateLeaveDeduction() const {
        return (basicSalary / 30.0) * leavesTaken;
    }

    double calculateGrossSalary() const {
        return basicSalary + calculateTA() + calculateDA()
               + calculateHRA() + calculateCommission();
    }

    double calculateNetSalary() const {
        return calculateGrossSalary() - calculateLeaveDeduction();
    }

    void displaySalarySlip() const {
        cout << "\n====================================================\n";
        cout << "                 EMPLOYEE SALARY SLIP\n";
        cout << "====================================================\n";
        cout << left << setw(25) << "Employee ID:" << employeeId << '\n';
        cout << left << setw(25) << "Employee Name:" << employeeName << '\n';
        cout << left << setw(25) << "Designation:" << designation << '\n';
        cout << "----------------------------------------------------\n";
        cout << fixed << setprecision(2);
        cout << left << setw(35) << "Basic Salary (Rs.):" << basicSalary << '\n';
        cout << left << setw(35) << "Travel Allowance - TA (Rs.):" << calculateTA() << '\n';
        cout << left << setw(35) << "Dearness Allowance - DA (Rs.):" << calculateDA() << '\n';
        cout << left << setw(35) << "House Rent Allowance - HRA (Rs.):" << calculateHRA() << '\n';
        cout << left << setw(35) << "Commission (Rs.):" << calculateCommission() << '\n';
        cout << "----------------------------------------------------\n";
        cout << left << setw(35) << "Gross Salary (Rs.):" << calculateGrossSalary() << '\n';
        cout << left << setw(35) << "Leaves Taken:" << leavesTaken << '\n';
        cout << left << setw(35) << "Leave Deduction (Rs.):" << calculateLeaveDeduction() << '\n';
        cout << "----------------------------------------------------\n";
        cout << left << setw(35) << "NET SALARY (Rs.):" << calculateNetSalary() << '\n';
        cout << "====================================================\n";
    }

    int getId() const { return employeeId; }

    // Destructor
    ~Employee() {
        // No manually allocated memory is used in this class.
    }
};

int main() {
    vector<Employee> employees;
    int choice;

    do {
        cout << "\n========== EMPLOYEE SALARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add employee and generate salary slip\n";
        cout << "2. Display all salary slips\n";
        cout << "3. Search employee by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            int id, leaves;
            string name, post;
            double basic, ta, da, hra, commission;

            cout << "Enter employee ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter employee name: ";
            getline(cin, name);

            cout << "Enter designation: ";
            getline(cin, post);

            cout << "Enter basic salary (Rs.): ";
            cin >> basic;
            cout << "Enter TA rate (% of basic salary): ";
            cin >> ta;
            cout << "Enter DA rate (% of basic salary): ";
            cin >> da;
            cout << "Enter HRA rate (% of basic salary): ";
            cin >> hra;
            cout << "Enter number of unpaid leaves taken: ";
            cin >> leaves;
            cout << "Enter commission rate (% of basic salary): ";
            cin >> commission;

            if (id <= 0 || basic < 0 || ta < 0 || da < 0 || hra < 0 ||
                leaves < 0 || commission < 0) {
                cout << "Invalid values. Please enter positive ID and non-negative amounts/rates.\n";
            } else {
                employees.emplace_back(id, name, post, basic, ta, da, hra, leaves, commission);
                cout << "\nEmployee added successfully.\n";
                employees.back().displaySalarySlip();
            }
        } else if (choice == 2) {
            if (employees.empty()) {
                cout << "No employee records available.\n";
            } else {
                for (const Employee &emp : employees) {
                    emp.displaySalarySlip();
                }
            }
        } else if (choice == 3) {
            int searchId;
            bool found = false;
            cout << "Enter employee ID to search: ";
            cin >> searchId;

            for (const Employee &emp : employees) {
                if (emp.getId() == searchId) {
                    emp.displaySalarySlip();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Employee record not found.\n";
            }
        } else if (choice == 4) {
            cout << "Thank you for using Employee Salary Management System.\n";
        } else {
            cout << "Invalid choice. Please select 1 to 4.\n";
        }
    } while (choice != 4);

    return 0;
}
