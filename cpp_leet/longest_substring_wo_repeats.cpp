/* 
🔥 Next Question (Easy-Medium)
📌 Problem: Longest Substring Without Repeating Characters

🔹 Description:
Given a string s, find the length of the longest substring without repeating characters.

🔹 Examples:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with a length of 3.

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with a length of 1.

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with a length of 3.
🔹 Constraints:

0 <= s.length <= 5 * 10⁴
s consists of English letters, digits, symbols, and spaces.
*/
#include <iostream>
#include <vector>
#include <unordered_map>

int longest_substring_wo_repeats(const std::string& input) {
    std::unordered_map<char, int> chars;
    int follow_index = 0;
    int max_length{};
    for(int i=0; i<input.size();++i) {
        if (chars.contains(input[i])) {
            follow_index = std::max(follow_index, chars[input[i]]+1);
        }
        chars[input[i]] = i;
        max_length = std::max(max_length, (i-follow_index)+1);
        std::cout << "Doesn't contain:" << follow_index << i << max_length << std::endl;
    }
    return max_length;
}

int main() {
    //auto result = longest_substring_wo_repeats("abcabcbb");
    //auto result = longest_substring_wo_repeats("bbbbb");
    auto result = longest_substring_wo_repeats("pwwkew");
    
    std::cout << result << std::endl;
}
