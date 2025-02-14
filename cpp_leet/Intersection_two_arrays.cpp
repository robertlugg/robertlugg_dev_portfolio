/*
🔥 Next Question (Easy - Hashing Pattern)
📌 Problem: Intersection of Two Arrays
🔹 Description:
Given two integer arrays, return an array of their intersection. Each element in the result must be unique and appear in both input arrays.

🔹 Examples:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]

🔹 Constraints:

You may return the result in any order.
Each element in the result must be unique.
*/
#include <iostream>
#include <vector>
#include <unordered_set>
std::vector<int> intersect(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    //std::unordered_set<int> s1(nums1.begin(), nums1.end());
    //Create fast lookup of nums2
    std::unordered_set<int> s2(nums2.begin(), nums2.end());
    // result_set is unordered_set to auto remove duplicates
    std::unordered_set<int> result_set;
    for(auto num: nums1) {
        if (s2.contains(num)) {
            result_set.emplace(num);
        }
    }
    // Convert to vector to comply with question
    return std::vector<int>(result_set.begin(), result_set.end());
}


int main() {
    //auto result = intersect({1,2,2,1}, {2,2});
    auto result = intersect({4,9,5}, {9,4,9,8,2});
    //auto result = intersect({1,2,2,1}, {3,4});
    //auto result = intersect({}, {3,4});
    //auto result = intersect({3,4}, {});
    //auto result = intersect({}, {});
    for(auto val:result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}