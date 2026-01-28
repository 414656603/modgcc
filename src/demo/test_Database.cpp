#include "demo/testAll.h"

import <iostream>;
import database;
import employee;

using namespace std;
using namespace Records;

int Test_Database()
{
    cout << "测试Database类" << endl;
    Database empDB;

    empDB.addEmployee("Larry", "Greenwald");
    empDB.addEmployee("Jane", "Smith");
    empDB.addEmployee("John", "Doe");

    empDB.getEmployee(1001).promote(5000);
    empDB.getEmployee("Jane", "Smith").promote(7000);
    empDB.getEmployee("John", "Doe").demote(2000);
    empDB.getEmployee("John", "Doe").fire();

    cout << "\n显示所有员工：" << endl;
    empDB.displayAll();

    cout << "\n显示现有员工：" << endl;
    empDB.displayCurrent();

    cout << "\n显示前员工：" << endl;
    empDB.displayFormer();



    cout << "测试Database类2" << endl;
    Employee& emp1 = empDB.addEmployee("Alice", "Johnson");
    emp1.fire();

    Employee& emp2 = empDB.addEmployee("Bob", "Brown");
    emp2.setSalary(60000);

    Employee& emp3 = empDB.addEmployee("Charlie", "Davis");
    emp3.setSalary(1);
    emp3.promote();

    cout << "\n显示所有员工：" << endl;
    empDB.displayAll();

    cout << "\n显示现有员工：" << endl;
    empDB.displayCurrent();
    cout << "\n显示前员工：" << endl;
    empDB.displayFormer();


    cin.get();
    return 0;
}