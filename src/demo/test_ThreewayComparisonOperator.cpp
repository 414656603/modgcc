#include "demo/test_ThreewayComparisonOperator.h"

import <compare>;
import <format>;
import <iostream>;

namespace demo {
void RunThreewayComparisonOperatorDemo(int i)
{
    using namespace std;
    cout << format("三向比较运算符输出，与0比较: {}\n", (i <=> 0) == strong_ordering::less ? "less" : (i <=> 0) == strong_ordering::greater ? "greater" : "equal");
    strong_ordering result { i <=> 0 };
    if ( result == strong_ordering::less ) { cout << "less" << endl; }
    if ( result == strong_ordering::greater ) { cout << "greater" << endl; }
    if ( result == strong_ordering::equal ) { cout << "equal" << endl; }
    if (is_lt(result)) { cout << "is less" << endl; }
    if (is_gt(result)) { cout << "is greater" << endl; }
    if (is_eq(result)) { cout << "is equal" << endl; }
}
} // namespace demo