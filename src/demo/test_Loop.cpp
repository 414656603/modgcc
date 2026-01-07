#include "demo/test_Loop.h"

import <iostream>;
import <format>;
import <array>;

namespace demo {
void RunTest_Loop()
{
    using namespace std;
    int i {0};
    while ( i < 5 ) {
        cout << "while循环。重复执行5次" << endl;
        ++i;
    }

    int j { 100 };
    do {
        cout << "do...while循环。错也要执行1次：" << endl;
        ++j;
    } while ( j < 5 );

    for (int i { 0 }; i < 5; ++i) {
     cout << "for循环。重复执行5次" << endl;
    }

    array <int,5> arr = {1,2,3,4,5};
    for ( int i : arr ) { cout << format("范围for循环，当前元素值为：{}",i) << endl; }

    cout << "给予范围的for循环的初始化器：" << endl;
    for (array myarr {1,2,3,4,5}; int i : myarr ) { cout << format("当前元素值为：{}",i) << endl; }
}

} // namespace demo

