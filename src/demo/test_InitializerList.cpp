#include "demo/test_InitializerList.h"

import <iostream>;
import <format>;
import <initializer_list>;

using namespace std;

namespace demo {
int makeSum(initializer_list<int> list) {
    int sum = 0;
    for (int value : list) {
        sum += value;
    }
    return sum;
}

void Runtest_InitializerList() {
    int a { makeSum({1, 2, 3, 4, 5}) };
    int b { makeSum({10, 20, 30}) };
    //int c { makeSum({1, 2, 3.0}) };   // 编译错误：窄化。Error: narrowing conversion from 'double' to 'int'
    cout << format("a = {}, b = {}", a, b) << endl;
}

} // namespace demo