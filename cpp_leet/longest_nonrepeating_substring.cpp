/*
Problem: Longest Substring Without Repeating Characters
Description:
Given a string s, find the length of the longest substring without repeating characters.

Example Input/Output:

Input: "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Note: The substring must be contiguous, and "pwke" is not a valid answer.

Constraints
The input string consists of only printable ASCII characters.
Length of the string s: 
    0 ≤ ∣𝑠∣ ≤ 5×10^4
 */
#include "iostream"
#include "vector"
#include "string"
#include "iomanip"
#include "unordered_set"

struct Testcase {
    std::string input;
    size_t golden_length;
};

size_t find_longest_substring(std::string input_string) {
    if (!input_string.length()) {
        return 0;
    }
    std::unordered_set<char> found_chars;

    size_t max_length = 0;
    size_t current_length = 0;
    auto tail_it = input_string.begin();
    for (const auto head_char: input_string) {
        if (found_chars.find(head_char) == found_chars.end()) {
            found_chars.insert(head_char);
            current_length++;
            max_length = std::max(max_length, current_length);
            continue;
        }
        do {
            auto found = found_chars.find(head_char);
            found_chars.erase(*tail_it);
            tail_it++;
            current_length--;
        } while (found_chars.find(head_char) != found_chars.end() );

    }
    return max_length;
}

int main() {
    const std::vector<Testcase> testcases = {
        {"abcabcbb", 3},
        {"bbbbb", 1},
        {"pwwkew", 3},
        {"", 0},
        {"abcdef", 6}
    };
    for (const auto& testcase: testcases) {
        std::cout << "Testing: " << std::left << std::setw(14) <<testcase.input << std::flush;
        const auto result = find_longest_substring(testcase.input);
        std:: cout << "   Return= " << result << std::flush;
        if (result == testcase.golden_length) {
            std::cout << "   Passed!" << std::endl;
        } else {
            std::cout << "   FAILED!" << std::endl;
        }
    }
}