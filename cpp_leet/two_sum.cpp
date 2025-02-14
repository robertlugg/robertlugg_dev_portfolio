/*
two sum

Given an array of integers `nums` and an integer `target`, return the indices of the two 
numbers such that they add up to the `target`.

Example 1:
nums = [2, 7, 11, 15], target = 9
Output: [0, 1]

Constraints:
Each input has exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

*/
#include <iostream>
#include <vector>
#include <unordered_map>

struct SearchResult {
    size_t begin_index = 0;
    size_t end_index = 0;
};

SearchResult two_sum(const std::vector<int> nums, int target) {
    std::unordered_map<int, size_t> found_values = {};
    for (std::size_t index=0; index < nums.size();++index) {
        const int alt_num = target - nums[index];
        if (const auto it = found_values.find(alt_num); it != found_values.end()) {
            const size_t found_index = it->second;
            const SearchResult return_value = {found_index, index};
            return return_value;
        }
        found_values[nums[index]] = index;
    }
    // Can't reach
    return {1, 0}; //Invalid case
}

int main() {
    const std::vector<int> nums = {2, 7, 11, 15};
    int target = 22;
    const auto result = two_sum(nums, target);
    if (result.begin_index > result.end_index) {
        std::cout << "No values found." << std::endl;
        return 1;
    }
    std::cout << "[" << result.begin_index << ", " << result.end_index << "]"  << std::endl;
    return 0;
}