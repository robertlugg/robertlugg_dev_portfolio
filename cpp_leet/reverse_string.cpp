#include <iostream>
#include <string>
#include <vector>

// Reverse inputString.  Return if successful.
bool reverse_string(std::string& inputString) {
    auto front = inputString.begin();
    auto back = inputString.rbegin();
    while ( front != back.base() ) {
        std::swap(*front, *back);
        front++;
        back++;
    }
    return true;
}

// Reverse inputString.  Return if successful.
bool reverse_string2(std::string& inputString) {
    auto front = inputString.begin();
    auto back = inputString.end()--;
    while ( front != back ) {
        std::swap(*front, *back);
        front++;
        back--;
    }
    return true;
}

int main() {
    std::vector<std::pair<std::string, std::string>> testcases{}; 
    testcases.push_back(std::pair<std::string, std::string>{"abc", "cba"});
    std::cout << "Running some reverses:\n";
    for (auto testcase: testcases) {
        std::cout << "Orig: " << testcase.first << "\n";
        reverse_string2(testcase.first);
        std::cout << "Revr: " << testcase.first << std::endl;
        if (testcase.first == testcase.second) {
            std::cout << "Passed!" << std::endl;
        } else {
            std::cout << "Failed!" << std::endl;
        }
    }
}