/*
🔥 Next Question (Easy - Different Pattern)
📌 Problem: Remove Duplicates from Sorted Array
🔹 Description:
Given a sorted array nums, remove duplicates in-place such that each unique element appears only once, and return the new length.

Modify nums in-place without allocating extra space.

🔹 Example:
Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]

Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_]

🔹 Constraints:
You must modify the array in place.
The relative order of elements should be maintained.
You don’t need to remove trailing elements after the unique ones.
*/
#include <iostream>
#include <vector>

int remove_duplicates(std::vector<int>& nums) {
    if (nums.size()<2) return nums.size();
    size_t fill_index = 0;
    for(size_t i=0; i<nums.size()-1; ++i) {
        if (nums[i]==nums[i+1]) {
            continue;
        }
        nums[fill_index] = nums[i];
        fill_index++;
        continue;
    }
    nums[fill_index] = nums[nums.size()-1];
    fill_index++;
    return fill_index;
}

int main() {
    //std::vector<int> nums{1,1,2};
    std::vector<int> nums{0,0,1,1,1,2,2,3,3,4};
    auto length = remove_duplicates(nums);
    std::cout << "Length: " << length << std::endl;
    for(auto& num: nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}