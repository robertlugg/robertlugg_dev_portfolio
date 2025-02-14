// Implement reverse string again for practice
#include <iostream>
#include <string>
#include <vector>

void reverse_string(std::string& user_string) {
    auto head = user_string.begin();
    auto tail = user_string.end() - 1;
    while (head < tail) {
        //std::cout << *head << *tail << std::endl;
        std::swap(*head, *tail);
        //std::cout << "afer:" << *head << *tail << std::endl;
        head++;
        tail--;
    }
}

int main() {
    std::cout << "Welcome to reverse a string" << std::endl;
    std::vector<std::pair<std::string, std::string>> testcases{
        {"abc", "cba"},
        {"even", "neve"},
        {"odd", "ddo"},
        {"", ""}
    };

    for (auto testcase: testcases) {
        std::cout << "Input: " << testcase.first << std::endl;
        reverse_string(testcase.first);
        std::cout << "Output: " << testcase.first << std::endl;
        std::cout << "Golden: " << testcase.second << std::endl;

        if (testcase.first == testcase.second) {
            std::cout << "Pass!" << std::endl;
        } else {
            std::cout << "Fail!" << std::endl;
        }
    }
}
