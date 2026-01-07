#include <demo/test_switch.h>
#include <demo/test_ternary_operator.h>
#include <demo/test_ThreewayComparisonOperator.h>
#include "demo/test_FunctionInvocation.h"
#include "console_utf8.h"
#include "demo/test_Array.h"
#include "demo/test_Vector.h"
#include "demo/test_Optional.h"
#include "demo/test_Loop.h"
#include "demo/test_InitializerList.h"
#include "demo/test_String.h"

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

    using namespace demo;

    RunTestSwitch();
    RunTernaryOperatorDemo(5);
    RunThreewayComparisonOperatorDemo(5);

    int someInt = 10;
    char someChar = 'z';
    myFunction1(8, 'a');
    myFunction1(someInt, 'b');
    myFunction1(5, someChar);
    cout << addNumbers(1, 2) << endl;    //Calls the integer version
    cout << addNumbers(1.11, 2.22) << endl;    //Calls the double version   

    cout << "现在测试编译器警告：[[nodiscard]]属性" << endl;
    [[nodiscard("Return value of myFunction2() should not be ignored")]] myFunction2();

    cout << "现在测试编译器警告：[[maybe_unused]]属性" << endl;

    cout << "现在测试编译器警告：[[noreturn]]属性" << endl;
    bool isLicensed { isFeatureLicensed(42) };

    cout << "现在测试编译器警告：[[deprecated]]属性" << endl;
    myFunction3();

    cout << "现在测试数组相关内容" << endl;
    test_Array();

    cout << "现在测试vector相关内容" << endl;
    test_vector();

    cout << "现在测试optional相关内容" << endl;
    RunTest_Optional();

    cout << "现在测试pair相关内容" << endl;
    RunTest_Pair();

    cout << "测试结构化绑定相关内容" << endl;
    Test_StructuredBindings();

    cout << "测试结构化绑定分解相关内容" << endl;
    Test_StructuredBindings_fenjie();

    cout << "现在测试各种循环语句相关内容" << endl;
    RunTest_Loop();

    cout << "现在测试initializer_list相关内容" << endl;
    Runtest_InitializerList();

    cout << "现在测试string相关内容" << endl;
    Runtest_String();

    cin.get();
    return 0;
}