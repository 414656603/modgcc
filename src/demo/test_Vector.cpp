#include "demo/test_Vector.h"

import <vector>;
import <format>;
import <iostream>;

namespace demo {

void test_vector()
{
    using namespace std;
    //Create a vector of integers.
    vector<int> myVector1 {11, 22};
    //Add some more integers to the vector using push back().
    myVector1.push_back(33);
    myVector1.push_back(44);
    //Access elements.
    cout << format("lst element:{}",myVector1[0])<< endl;

    //Create and initialize a vector using an initializer list.
    vector myVector2 {100, 200, 300, 400};
    cout << format("2nd element:{}",myVector2[1])<< endl;
}

}