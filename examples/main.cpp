#include "demo/testAll.h"

import <iostream>;
import <format>;

using namespace std;

int main()
{



    //运行所有【第一章】演示测试
    RunTestAllDemos();

    //测试Employee类和Employee结构体
    Test_Employee();

    //测试Database类
    Test_Database();

    //测试用户界面（控制台版）
    Test_UserUI_Console();

    return 0;
}
