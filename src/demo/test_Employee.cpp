#include "demo/testAll.h"

import <iostream>;
import employee;

using namespace std;
using namespace Records;

int Test_Employee()
{
    cout << "测试Employee类和Employee结构体" << endl;
    Employee emp { "L", "GW" };  //到栈上，不到堆上不用new
    emp.setFirstName("Larry");
    emp.setLastName("Greenwald");
    emp.setEmployeeNumber(1001);
    emp.setSalary(55000);
    emp.promote();
    emp.promote(5000);
    emp.hire();
    emp.display();

    cin.get();
    return 0;
}