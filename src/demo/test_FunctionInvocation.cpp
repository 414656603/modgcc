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
} // namespace demo