#include <demo/test_switch.h>
#include <demo/test_ternary_operator.h>
#include "console_utf8.h"

import <iostream>;
import <format>;
import employee;

using namespace std;

int main()
{
    //运行编译后的exe时，控制台使用UTF-8编码。
    demo::InitConsoleUtf8();

    //Create and populate an employee.
    Employee anEmployee;
    anEmployee.firstInitial='J';
    anEmployee.lastInitial='D';
    anEmployee.employeeNumber = 42;
    anEmployee.salary=80000;
    //Output the values of an employee.
    cout << format("Employee:{}{}",anEmployee.firstInitial,anEmployee.lastInitial) << endl;
    cout << format("Number:{}",anEmployee.employeeNumber) << endl;
    cout << format("Salary:${}",anEmployee.salary) << endl;

    demo::RunTestSwitch();
    demo::RunTernaryOperatorDemo(5);

    cin.get();
    return 0;
}