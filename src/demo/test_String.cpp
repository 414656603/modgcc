#include "demo/test_String.h"

import <iostream>;
import <format>;
import <string>;

using namespace std;

namespace demo {

void Runtest_String() {
    string str1 = "Hello, ";
    string str2 = "World!";
    string str3 = str1 + str2;
    cout << format("Concatenated String: {}", str3) << endl;

    size_t length = str3.length();
    cout << format("Length of String: {}", length) << endl;

    string substring = str3.substr(7, 5);
    cout << format("Substring: {}", substring) << endl;

    size_t pos = str3.find("World");
    if (pos != string::npos) {
        cout << format("'World' found at position: {}", pos) << endl;
    } else {
        cout << "'World' not found" << endl;
    }

    cout << str3[1] << endl; // Output character at index 1
}

} // namespace demo