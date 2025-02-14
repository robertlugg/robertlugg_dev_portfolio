/*

g++ -std=c++20 valid_parentheses.cpp

📌 Problem: Valid Parentheses
🔹 Description:
Given a string containing only the characters '(', ')', '{', '}', '[', and ']', determine if the input string is valid.

A string is valid if:

Open brackets are closed by the same type of bracket.
Open brackets are closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
🔹 Examples:

Input: s = "()"
Output: true

Input: s = "()[]{}"
Output: true

Input: s = "(]"
Output: false

Input: s = "([)]"
Output: false

Input: s = "{[]}"
Output: true

*/
#include <iostream>
#include <string>
#include <stack>

bool valid_parentheses(const std::string& paren) {
    if (paren.empty()) return true;
    std::stack<char> parse_stack;
    for(const auto& ch: paren) {
        if (ch=='(' || ch== '[' || ch=='{') {
            parse_stack.push(ch);
            continue;
        }
        if (ch==')' || ch==']' || ch=='}') {
            if (parse_stack.empty()) return false;
            auto other = parse_stack.top();
            parse_stack.pop();
            if (ch==')' && other=='(') continue;
            if (ch==']' && other=='[') continue;
            if (ch=='}' && other=='{') continue;
            return false;
        }
    }
    return parse_stack.empty();
}

int main() {
    std::cout << std::boolalpha << valid_parentheses("()[{}") << std::endl;
}
