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
import <optional>;
import <memory>;
import employee;
import airline_ticket;


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

    cout << "现在测试AirlineTicket模块相关内容" << endl;
    // 【基于栈】进入作用域：自动构造和析构AirlineTicket对象
    AirlineTicket ticketStack;
    AirlineTicketInline ticketInline;
    ticketStack.setPassengerName("John Q. Public");
    ticketStack.setNumberOfMiles(500);
    ticketStack.setEliteSuperRewardsStatus(false);
    cout << format("Ticket for {} costs ${}", ticketStack.getPassengerName(), ticketStack.calculatePriceInDollars()) << endl;
    // 离开作用域（main结束/return/异常）：自动析构AirlineTicket对象
    cout << ticketInline.getPassengerName() << endl;


    //特点：对象在堆上；仍然不需要手动 delete（RAII）；可以转移所有权
    //适用：对象要跨作用域保存、放到容器里、需要多态（unique_ptr<Base> 指向 Derived）等
    auto ticketPtr = make_unique<AirlineTicket>();
    ticketPtr->setPassengerName("lgw_auto");
    cout << ticketPtr->getPassengerName() << endl;
    // 自动释放：unique_ptr 析构时 delete


    //特点：对象在堆上；需要手动 delete；“老式写法”，不推荐
    AirlineTicket* pTicket = new AirlineTicket();
    pTicket->setPassengerName("lgw_old");
    cout << pTicket->getPassengerName() << endl;
    delete pTicket; //手动释放内存。容易忘，导致内存泄漏。


    //特点：通常不走堆；你可以“先不创建对象”，【需要时】再 emplace 出来
    //适用：对象是可选的；延迟构造；但你不想用指针
    optional<AirlineTicket> optTicket;
    optTicket.emplace(); // 【这里才构造】AirlineTicket
    optTicket->setPassengerName("lgw_optional");
    cout << optTicket->getPassengerName() << endl;
    // 可随时销毁对象
    optTicket.reset();

    cin.get();
    return 0;
}