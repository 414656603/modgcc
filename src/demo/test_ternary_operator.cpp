#include <demo/test_ternary_operator.h>

import <format>;
import <iostream>;

namespace demo {
void RunTernaryOperatorDemo(int i)
{
    using namespace std;

    cout << format("三目运算符输出，与2比较: {}\n", (i > 2) ? "正数" : (i > 2) ? "大于2" : "小于等于2");
}
} // namespace demo