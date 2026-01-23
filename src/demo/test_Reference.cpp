#include "demo/test_Reference.h"

import <iostream>;
import <string>;
import <vector>;

using namespace std;


//测试：引用************************************************
    //  临时对象  也是如此。不能为  临时对象  创建  对非const的  引用  ，但是  const引用  是可以的。
    string createTemporaryString() { return "fuckuworld"; }

    class MyClass_ref
    {
        public:
            //引用数据成员  不能在  类构造函数  的 函数体 内部进行初始化，必须在所谓的  构造函数初始化器  中进行初始化
            MyClass_ref(int& ref) : m_ref{ref} {}   
        private:
            int& m_ref;
    };

    void addOne_value (int i)
    {
        i++; // Has no real effect because this is a copy of the original
    }
    void addOne_ref (int& i)
    {
        i++; // Actually changes the original variable
    }

    void swap_ref (int& first, int& second)
    {
        int temp ( first );
        first = second;
        second = temp;
    }

    void printString_ref (const string& str)
    {
        cout << str << endl;
    }

    //C风格数组分离奇偶数
    void separateOddsAndEvens(const int arr[], size_t size, 
        int** odds,  size_t* numOdds, int** evens, size_t* numEvens)
    {
        // First, count the number of odds and evens
        *numOdds = *numEvens = 0;
        for (size_t i = 0; i < size; ++i)
        {
            if (arr[i] % 2 == 0)
                (*numEvens)++;
            else
                (*numOdds)++;
        }

        //Allocate two new arrays of the appropriate sizes.
        *odds = new int[*numOdds];
        *evens = new int[*numEvens];

        // Copy the odds and evens into their respective arrays.
        size_t oddIndex = 0, evenIndex = 0;
        for (size_t i = 0; i < size; ++i)
        {
            if (arr[i] % 2 == 0)
                (*evens)[evenIndex++] = arr[i];
            else
                (*odds)[oddIndex++] = arr[i];
        }
    }


    //使用引用编写相同的函数，以获得真正的引用传递语义。
    void separateOddsAndEvens_ref(const int arr[], size_t size, 
        int*& odds,  size_t& numOdds, int*& evens, size_t& numEvens)
    {
        // First, count the number of odds and evens
        numOdds = numEvens = 0;
        for (size_t i = 0; i < size; ++i)
        {
            if (arr[i] % 2 == 0)
                numEvens++;
            else
                numOdds++;
        }

        //Allocate two new arrays of the appropriate sizes.
        odds = new int[numOdds];
        evens = new int[numEvens];

        // Copy the odds and evens into their respective arrays.
        size_t oddIndex = 0, evenIndex = 0;
        for (size_t i = 0; i < size; ++i)
        {
            if (arr[i] % 2 == 0)
                evens[evenIndex++] = arr[i];
            else
                odds[oddIndex++] = arr[i];
        }
    }


    //使用标准库容器vector ，可将separateOddsAndEvens()函数重写为：更安全、更短、更美观并且更具可读性
    void separateOddsAndEvens_vector(const vector<int>& arr, 
        vector<int>& odds, vector<int>& evens)
    {
        for (int num : arr)
        {
            if (num % 2 == 0)
                evens.push_back(num);
            else
                odds.push_back(num);
        }
    }


    //返回一个简单的  包含两个vector的  结构体  ，而不是接收  两个  输出向量  作为  参数  。它也使用了C++20的  指派初始化器  。
    struct OddEvenVectors { vector<int> odds; vector<int> evens; };
    OddEvenVectors separateOddsAndEvens_struct(const vector<int>& arr)
    {
        vector<int> odds, evens;
        for (int num : arr)
        {
            if (num % 2 == 0)
                evens.push_back(num);
            else
                odds.push_back(num);
        }
        return OddEvenVectors{
            .odds = odds,
            .evens = evens
        };
    }


void Runtest_Reference()
{
    cout << "测试【引用】：" << endl;
    int originalValue {  10 };
    int& refToValue ={  originalValue }; //refToValue 是 originalValue 的引用
    refToValue = 20; //通过引用修改 originalValue
    cout << "originalValue:" << originalValue << endl; //输出 20

    //不允许在  类  定义之外   声明  一个引用而不对其进行初始化：引用变量必须总是在创建时被初始化。
    //int& refToUninitializedValue; //编译错误：引用必须在声明时初始化

    //- 如果在声明  引用  时将  变量  赋值给  引用  ，则  引用  指向该  变量  。
    //但是，如果之后将  变量  赋值给  引用  ，则  引用  所指向的  变量  会更改为赋值的  变量  的值。原来的  引用  不会改为指向  新的    变量  。
    int x_ref { 3 }, y_ref { 4 };
    int& ref_test = x_ref; //ref_test 引用 x_ref
    cout << "ref_test:" << ref_test << endl; //输出 3
    ref_test = y_ref; //将 y_ref 的值赋给 ref_test（即 x_ref）
    cout << "x_ref:" << x_ref << endl; //输出 4

    //可以尝试使用：y的  地址  对xRef赋值来规避此限制。
    //ref_test = &y_ref; //将 ref_test 指向 y_ref 的地址（错误用法）。编译失败。
    //这句代码会编译失败。y的  地址  是一个  指针  ，但是xRef被声明为一个对int的引用，而不是对指针的引用。

    int z_ref { 5 };
    int& ref_testz = z_ref; //ref_test2 引用 z_ref
    ref_testz = ref_test; //将 ref_test 的值赋给 ref_test2（即 z_ref）
    cout << "z_ref:" << z_ref << endl; //输出 4.不会更改为引用ref_test所引用的变量x_ref的地址，而是将ref_test的值赋给了z_ref

    //因此，当C+程序员提起  const  引用  时，他们的意思是这样的：
    int another_originalValue {  30 };
    const int& constRefToValue = another_originalValue; //constRefToValue 是 originalValue 的 const 引用
    another_originalValue = 40; //【可以通过原始变量修改值】
    cout << "constRefToValue:" << constRefToValue << endl; //输出
    //constRefToValue = 50; //编译错误：【不能通过 const 引用修改值】

    //不能创建  对未命名值的  引用  ，例如：整数  字面量  ，除非该  引用  是：  const值  。
    //int& unnamedRef1 { 5 }; //编译错误：不能引用字面量
    const int& unnamedRef2 { 5 }; //有效：const引用可以引用字


    //  临时对象  也是如此。不能为  临时对象  创建  对非const的  引用  ，但是  const引用  是可以的。
    //string& tempStringRef = createTemporaryString();  //编译错误：不能为临时对象创建对非const的引用
    const string& constTempStringRef { createTemporaryString() }; //有效：【const引用】可以引用【临时对象,std::string对象】


    //引用指针
    int* intP_testref {  nullptr };
    int*& ptr_testref { intP_testref }; //ptr_testref 是 intP_testref 的引用
    ptr_testref = new int;//通过引用【修改 intP_testref 指针本身】
    *ptr_testref = 60; //通过引用【修改 指针指向的值】
    cout << "*intP_testref:" << *intP_testref << endl; //输出 60
    delete ptr_testref; //释放通过 new 分配的内存
    ptr_testref = nullptr;

    //取一个  引用的  地址  与取  该引用所指向的  变量的  地址  得到的结果是相同的。
    int x_refaddr { 100 };
    int& ref_x_refaddr { x_refaddr };
    int* p_x_refaddr { &ref_x_refaddr }; //取变量的地址
    *p_x_refaddr = 200; //通过指针修改变量值
    cout << "x_refaddr:" << x_refaddr << endl; //输出 200

    //结构化绑定
    pair pair_testref { "hello", 42 };
    //auto [str_testref, int_testref] {pair_testref};      //结构化绑定
    auto& [str_testref, int_testref] {pair_testref};       //结构化绑定，使用引用
    const auto& [const_str_testref, const_int_testref] {pair_testref}; //结构化绑定，使用const引用
    cout << "str_testref:" << str_testref << ", int_testref:" << int_testref << endl;
    cout << "const_str_testref:" << const_str_testref << ", const_int_testref:" << const_int_testref << endl;

    int value1 { 10 };
    int& ref1 { value1 };
    cout << "value1 before addOne_value:" << value1 << endl;
    addOne_value(ref1); //传递引用的副本
    cout << "value1 after addOne_value:" << value1 << endl;
    addOne_ref(ref1); //传递引用
    cout << "value1 after addOne_ref:" << value1 << endl;

    int a_swap { 1 }, b_swap { 2 };
    cout << "Before swap: a_swap=" << a_swap << ", b_swap=" << b_swap << endl;
    swap_ref(a_swap, b_swap);
    cout << "After swap: a_swap=" << a_swap << ", b_swap=" << b_swap << endl;

    string helloStr { "Hello, World!" };
    printString_ref(helloStr);
    printString_ref( "Hello, World!" ); //传递临时对象

    cout << "C风格数组分离奇偶数" << endl;
    int unSplitArray[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int* oddsArray {  nullptr };
    int* evensArray {  nullptr };
    size_t numOdds { 0 }, numEvens { 0 };
    separateOddsAndEvens(unSplitArray, size(unSplitArray),
        &oddsArray, &numOdds, &evensArray, &numEvens);
    cout << "Odd numbers:" << endl;
    for (size_t i = 0; i < numOdds; ++i)
    {
        cout << oddsArray[i] << " ";
    }
    cout << endl;
    cout << "Even numbers:" << endl;
    for (size_t i = 0; i < numEvens; ++i)
    {
        cout << evensArray[i] << " ";
    }
    cout << endl;
    //用完以后销毁函数产生的数组
    delete[] oddsArray;
    delete[] evensArray;

    cout << "使用引用编写相同的函数，以获得真正的引用传递语义。" << endl;
    int* oddsArray_ref {  nullptr };
    int* evensArray_ref {  nullptr };
    size_t numOdds_ref { 0 }, numEvens_ref { 0 };
    separateOddsAndEvens_ref(unSplitArray, size(unSplitArray),
        oddsArray_ref, numOdds_ref, evensArray_ref, numEvens_ref);
    cout << "Odd numbers (ref):" << endl;
    for (size_t i = 0; i < numOdds_ref; ++i)
    {
        cout << oddsArray_ref[i] << " ";
    }
    cout << endl;
    cout << "Even numbers (ref):" << endl;
    for (size_t i = 0; i < numEvens_ref; ++i)
    {
        cout << evensArray_ref[i] << " ";
    }
    cout << endl;
    //用完以后销毁函数产生的数组
    delete[] oddsArray_ref;
    delete[] evensArray_ref;

    cout << "使用标准库容器vector ，可将separateOddsAndEvens()函数重写为：更安全、更短、更美观并且更具可读性" << endl;
    vector<int> unSplitVector = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<int> oddsVector;
    vector<int> evensVector;
    separateOddsAndEvens_vector(unSplitVector, oddsVector, evensVector);
    cout << "Odd numbers (vector):" << endl;
    for (int num : oddsVector)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "Even numbers (vector):" << endl;
    for (int num : evensVector)
    {
        cout << num << " ";
    }
    cout << endl;


    //返回一个简单的  包含两个vector的  结构体  ，而不是接收  两个  输出向量  作为  参数  。它也使用了C++20的  指派初始化器  。
    cout << "返回一个简单的 包含两个vector的 结构体 ，而不是接收 两个 输出向量 作为 参数 。它也使用了C++20的 指派初始化器 。" << endl;
    vector<int> vecUnsplit = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto OddEvenResult1 { separateOddsAndEvens_struct(vecUnsplit) };
    cout << "Odd numbers (struct):" << endl;
    for (int num : OddEvenResult1.odds)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "Even numbers (struct):" << endl;
    for (int num : OddEvenResult1.evens)
    {
        cout << num << " ";
    }
    cout << endl;
}