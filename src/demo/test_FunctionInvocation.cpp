#include "demo/test_ThreewayComparisonOperator.h"

import <format>;
import <iostream>;

namespace demo {
void myFunction1(int i, char c)
{
    using namespace std;
    cout << "myFunction1 called" << endl;
    cout << format("the value of i is {}", i) << endl;
    cout << format("the value of c is {}", c) << endl;
    cout << format("Entering function {}", __func__) << endl;
}

int addNumbers(int a, int b) { return a + b; }
double addNumbers(double a,double b) { return a+ b; }

int myFunction2()
 {
    return 42;
}

int myFunction3(int param1, [[maybe_unused]] double param2)
 {
    return 100;
}



[[noreturn]]void forceProgramTermination()
{
    std::exit(1);    //Defined in <cstdlib>
}

bool isDongleAvailable()
{
    bool isAvailable { true };    //Check whether a licensing dongle is available...
    return isAvailable;
}

bool isFeatureLicensed(int featureId)
{
    if(!isDongleAvailable()){
        //No licensing dongle found,abort program execution!
        forceProgramTermination();
    } else {
        bool isLicensed{ featureId==42 };//Dongle available, perform license check of the qiven feature...
        return isLicensed;
    }
}


 [[deprecated("This function is deprecated and should not be used.lgw")]] void myFunction3()
{
    //测试[[deprecated]]属性
} 

}// namespace demo

