#include "demo/test_Array.h"

import <format>;
import <iostream>;
import <array>;

namespace demo {

    void test_Array() 
    {
        int myArray1[3];
        myArray1[0] = 0;
        myArray1[1] = 1;
        myArray1[2] = 2;
        std::cout << std::format("直接赋值数组元素 myArray1: [{}, {}, {}]\n", myArray1[0], myArray1[1], myArray1[2]);

        int myArray2[3] = {0};
        std::cout << std::format("零初始化 myArray2: [{}, {}, {}]\n", myArray2[0], myArray2[1], myArray2[2]);

        int myArray3[3] = {};
        std::cout << std::format("默认初始化为空 myArray3: [{}, {}, {}]\n", myArray3[0], myArray3[1], myArray3[2]);

        int myArray4[3]  {};
        std::cout << std::format("列表初始化为空 myArray4: [{}, {}, {}]\n", myArray4[0], myArray4[1], myArray4[2]);

        int myArray5[3]  {10};
        std::cout << std::format("列表初始化部分赋值 myArray5: [{}, {}, {}]\n", myArray5[0], myArray5[1], myArray5[2]);

        int myArray6[]  {10, 20, 30};
        std::cout << std::format("列表初始化编译器自动推断数组大小 myArray6: [{}, {}, {}]\n", myArray6[0], myArray6[1], myArray6[2]);

        size_t arraySize1 { std::size(myArray6) };
        std::cout << std::format("使用 std::size 获取数组大小 myArray6 大小: {}\n", arraySize1);

        size_t arraySize2 { sizeof(myArray6) / sizeof(myArray6[0]) };
        std::cout << std::format("使用 sizeof 计算数组大小 myArray6 大小: {}\n", arraySize2);

        char myArray7[3][3];
        myArray7[2][2] = 'o'; 
        std::cout << std::format("二维数组元素 myArray7[2][2]: {}\n", myArray7[2][2]);
    }
    

}