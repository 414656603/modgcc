#include "demo/testAll_Demos.h"

#include <demo/test_switch.h>
#include <demo/test_ternary_operator.h>
#include <demo/test_ThreewayComparisonOperator.h>
#include "demo/test_FunctionInvocation.h"
#include "../src/console_utf8.h"
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


    // 测试：作用域和命名空间************************************************
    class test_scope
    {
        public:
            int get_a_value() { return 42; }
    };

    int get_a_value() { return 43; }

    namespace NS
    {
        int get_a_value() { return 44; }
    }
    
    // 测试：窄化************************************************
    void Test_Narrowing(int ) { }

    // 测试：常量表达式************************************************
    const int getArraySize () { return 32; }
    constexpr int getArraySize_constexpr () { return 32; }
    class Rect
    {
        public:
            //构造函数初始化列表（constructor member initializer list / initializer list）
            //冒号 : 后面这一串 m_width{w}, m_height{h} 就是“初始化列表”
            constexpr Rect(size_t w, size_t h) : m_width{w}, m_height{h} {}  
            constexpr size_t getarea() const { return m_width * m_height; }

        private:
            size_t m_width { 0 }, m_height { 0 };

    };
    constexpr double inchToMm(double inch) { return inch * 25.4; }
    consteval double inchToMm_consteval(double inch) { return inch * 25.4; }


int RunTestAllDemos()
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


    // 测试作用域和命名空间************************************************
    test_scope ts;
    cout << "类作用域中的get_a_value()返回值：" << ts.get_a_value() << endl;
    cout << "全局作用域中的get_a_value()返回值：" << ::get_a_value() << endl;
    cout << "全局作用域中的get_a_value()返回值：" << get_a_value() << endl;
    cout << "命名空间NS中的get_a_value()返回值：" << NS::get_a_value() << endl;


    //测试：【统一初始化】
    cout << "测试：【统一初始化】" << endl;

    struct CircleStruct
    {
        int x, y;
        double radius;
    };

    class CircleClass
    {
        public:
            CircleClass(int x, int y, double radius) 
                : m_x{x}, m_y{y}, m_radius{radius} {}
        public:
            int m_x, m_y;
            double m_radius;
    };

    CircleStruct mycircle1 = { 10, 10, 2.5 }; // 传统写法
    CircleClass mycircle2(20, 20, 5.0); // 传统写法
    /*C++11以后的统一初始化写法：*/
    CircleStruct mycircle3 = { 10, 10, 2.5 }; // 传统写法
    CircleClass mycircle4 = { 20, 20, 5.0 };  // 统一初始化写法，自动调用：构造函数
    /*统一初始化 语法，甚至可以省略“ = ”。*/
    CircleStruct mycircle5{ 10, 10, 2.5 }; // 统一初始化写法
    CircleClass mycircle6{ 20, 20, 5.0 };  // 统一初始化写法，自动调用：构造函数

    //统一初始化语法 可用于C++中 任何内容：
    int a = 3;
    int b(3);
    int c = { 3 };    // Uniform initialization
    int d { 3 };    // Uniform initialization
    int e {};        // Uniform initialization, e will be 0

    cout << mycircle1.x << endl;
    cout << mycircle2.m_x << endl;
    cout << mycircle3.x << endl;
    cout << mycircle4.m_x << endl;
    cout << mycircle5.x << endl;
    cout << mycircle6.m_x << endl;
    cout << a << b << c << d << e << endl;


    int* UninformedArray1 = new int[5] { 1, 2, 3, 4, 5 }; //统一初始化语法
    cout << UninformedArray1[2] << endl;
    delete[] UninformedArray1;

    int* UninformedArray2 = new int [] { 1, 2, 3, 4, 5 }; //统一初始化语法，省略大小
    cout << UninformedArray2[2] << endl;
    delete[] UninformedArray2;

    class MyClass_initializer
    {
        public:
            MyClass_initializer(): m_array{1,2,3,4,5} {} //在构造函数初始化器中  使用：  统一初始化语法。
        private:
            int m_array[5];
    };

    //测试：窄化，使用统一初始化语法时，编译器会报错
    //int n1{3.14}; // 编译错误：不能将 double 窄化转换为 int
    //Test_Narrowing(3.14); // 编译错误：不能将 double 窄化转换为 int


    //测试【指派初始化器】
    cout << "测试指派初始化器" << endl;
    Employee empolyee1 = {'J', 'D', 42, 80000};   //传统初始化写法，统一初始化语法。
    Employee employee2{         //使用 【指派初始化器】
        .firstInitial = 'J',
        .lastInitial = 'D',
        .employeeNumber = 42,
        .salary = 80000
    };
    Employee employee3{         //使用 【指派初始化器】，跳过 employeeNumber。
        .firstInitial = 'J',
        .lastInitial = 'D',
        .salary = 80000
    };
    cout << format("Employee1:{}{}",empolyee1.firstInitial,empolyee1.lastInitial) << endl;
    cout << format("Employee2:{}",employee2.employeeNumber) << endl;
    cout << format("Employee3:{}",employee3.employeeNumber) << endl; //未初始化，值未定义。


    cout << "测试指针：" << endl;
    int* myintegerPointer_no;  //别这样，会忘记初始化！使用后程序要崩溃。
    int* myintegerPointer { nullptr }; //推荐，初始化为 nullptr。申明最好和初始化同时进行。
    if (myintegerPointer ) { cout << "空指针自动转换为false" << endl; }

    myintegerPointer = new int; //在【堆】上分配【内存】
    *myintegerPointer = 42;  //【解引用】赋值

    delete myintegerPointer; //释放【堆】上的内存
    myintegerPointer = nullptr; //释放后，置空指针，避免悬空指针。
    if (myintegerPointer == nullptr ) { cout << "指针置空后，等于nullptr" << endl; }

    Employee* employeePointer { &anEmployee }; //指向栈上对象的指针
    cout << format("通过指针访问Employee:{}",(*employeePointer).employeeNumber) << endl;
    cout << format("通过指针访问Employee:{}",employeePointer->employeeNumber) << endl;

    //短路逻辑：
    bool isValidSalary1( (employeePointer && employeePointer->salary) );
    bool isValidSalary2( (employeePointer != nullptr && employeePointer->salary) );

    //动态分配的数组
    int arraySize { 8 };
    int* myVariableSizedArray { new int[arraySize] }; //分配并初始化为0

    myVariableSizedArray[3] = 2;  //使用基于栈的数组语法
    *(myVariableSizedArray + 3) = 3;  //使用指针算术运算语法，与上面那条语句【等价】

    cout << "动态分配的数组元素myVariableSizedArray[3]：" << myVariableSizedArray[3] << endl;
    delete[] myVariableSizedArray; //释放动态分配的数组内存
    myVariableSizedArray = nullptr;
    

    cout << "测试const指针和指向const的指针" << endl;
    const int versionNumberMajor { 2 }; //指向const的指针，指向的值不可变
    const int versionNumberMinor = 1;
    const string productName = "MyProduct";
    const double PI {  3.14159  }; //指向const的指针，指向的值不可变


    //一层或多层间接 指针变量
    int* ip1;   
    ip1 = new int[10]; //动态分配一个int数组
    ip1[4] = 5;
    cout << "可以通过ip1修改 指向的值,ip1[4]:" << ip1[4] << endl;
    delete[] ip1; //释放动态分配的数组内存


     //防止指向的值被修改(如第三行所示)：
    const int* ip2;  //现在，你无法更改：【ip指向的值】。
    ip2 = new int[10]; //动态分配一个int数组
    //ip2[4] = 6; //编译错误，不能通过ip2修改 指向的值

    //等效写法
    int const* ip3;  //现在，你无法更改：【ip指向的值】。
    ip3 = new int[10]; //动态分配一个int数组
    //ip3[4] = 7; //编译错误，不能通过ip3修改 指向的值c


    //如果想将ip本身标记为  const  ，而不是它指向的值，需要这样写
    int* const ip4 {  nullptr }; //【指针本身是const】，指针的值不可变。
    //ip4 = new int[10]; //编译错误，不能修改指针本身的值
    //ip4[4] = 8; //错误，引用了一个空指针。 Error: dereferencing a null pointer

    //// 编译器要求：你在声明它时对其进行初始化
    int* const ip5 {  new int[10] }; //【指针本身是const】，指针的值不可变.
    ip5[4] = 9; //可以通过ip5修改 指向的值
    cout << "可以通过ip5修改 指向的值,ip5[4]:" << ip5[4] << endl;
    delete[] ip5; //释放动态分配的数组内存


    //也可以像下面这样，将  指针本身  和  指针所指的值  都标记为：  const  。
    const int* const ip6 {  new int[10] }; //【指针本身是const】，指针的值不可变；指向的值也是const，不能修改。
    int const* const ip7 {  new int[10] }; //等效写法



    ////易于记忆的规则，可以用于读懂复杂的变量声明：  从右向左读：
    //int * const ip8;  // ip8 是一个 const 指针，指向一个 int 值。【ip是指向int的const指针】。
    int const * ip9;  // ip9 是一个指向 const int 值的指针。【ip是指向const int的指针】，
    //const int * const ip10; // ip10 是一个 const 指针，指向 const int 值。【ip是指向int常量的指针】。【不能只申明不初始化。】


    //还可以在  原始类型  参数 【非类型的指针】  上使用  const  ，以防止在函数体中意外更改它们。
    //例如，以下函数具有const整数参数。在函数体中，无法修改整数param。如果尝试对其进行修改，则编译器将生成错误。
    //void func (const int param) ( /* Not allowed to change param... */ )
    


// 已经验证到了：它“能编过”是 GCC 的扩展，但在严格标准模式下会报错。
// 你看我刚才用同一条命令额外加了 -Wvla -Wpedantic -pedantic-errors 之后，GCC 明确报：
// 关键错误：error: ISO C++ forbids variable length array 'myarray_testConstexpr' [-Wvla]
// 也就是：int myarray_testConstexpr[getArraySize()]; 在标准 C++ 里被当作 VLA（变长数组），而 VLA 不是标准 C++（GCC 只是“默认允许的扩展”），所以你平时不加严格选项时它会“看起来有效”。
// 如果你要自己复现验证点：
// 保持代码不变
// 编译时加 -pedantic-errors -Wvla（这俩就够了）
    cout << "测试：常量表达式" << endl;
    int myarray_testConstexpr[getArraySize()]; // Invalid in C++【能编译通过是因为：GCC的扩展，详见上面的注释】
    int myarray_testConstexpr2[getArraySize_constexpr()]; // Valid in C++
    int myarray_testConstexpr3[getArraySize_constexpr() + 1]; // Valid in C++
    myarray_testConstexpr[10] = 42;
    cout << "myarray_testConstexpr[10]:" << myarray_testConstexpr[10] << endl;
    cout << "myarray_testConstexpr[11]:" << myarray_testConstexpr[11] << endl;

    constexpr Rect myrect(10, 20);
    int myarray_rectArea[myrect.getarea()]; // Valid in C++
    myarray_rectArea[50] = 99;
    cout << "myarray_rectArea[50]:" << myarray_rectArea[50] << endl;


    constexpr double const_inch { 6.0 };
    double dynamic_inch { 8.0 };
    constexpr double mm1 = inchToMm(const_inch); // at compile time
    double mm2 = inchToMm(dynamic_inch); // at runtime
    cout << "mm1:" << mm1 << endl;
    cout << "mm2:" << mm2 << endl;
    
    constexpr double mm3 = inchToMm_consteval(const_inch); // 第一次调用仍然可以正常编译，并且可以在编译期进行求值
    //double mm4 = inchToMm_consteval(dynamic_inch);       // 第二个调用现在会导致编译错误，因为无法在编译期对其进行求值。






    cin.get();
    return 0;
}
