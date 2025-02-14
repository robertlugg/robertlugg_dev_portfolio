/*
📌 Problem: Single Number
🔹 Description:
Given a non-empty array of integers where every element appears twice except for one, find that single number.

You must implement a solution with a linear runtime complexity (O(N)) and O(1) extra space.

🔹 Examples:
Input: nums = [2,2,1]
Output: 1

Input: nums = [4,1,2,1,2]
Output: 4

Input: nums = [1]
Output: 1

🔹 Constraints:
1 <= nums.length <= 10⁵
-10⁵ <= nums[i] <= 10⁵
Every element appears twice except for one.

*/
#include <iostream>
#include <vector>
#include <optional>

std::optional<int> find_single_number(const std::vector<int>& nums) {
    if (nums.empty()) return std::nullopt; 
    int acc = 0;
    for(auto& num: nums) {
        acc = acc ^ num;
    }
    return acc;
}

int main() {
    //auto result = find_single_number({4,1,2,1,2});
    auto result = find_single_number({});
    if (result.has_value()) {
        std::cout << result.value() << std::endl;
    } else {
        std::cout << "Zero-length vector." << std::endl;
    }
}