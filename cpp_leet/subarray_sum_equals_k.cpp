/*
🔥 Next Problem (Easy-Medium)
📌 Problem: Subarray Sum Equals K

🔹 Description:
Given an array of integers nums and an integer k, return the total number of subarrays
whose sum equals k.

🔹 Examples:
Input: nums = [1,1,1], k = 2
Output: 2
Explanation: The two subarrays that sum to 2 are [1,1] at indices (0,1) and (1,2).

Input: nums = [1,2,3], k = 3
Output: 2
Explanation: The two subarrays are [1,2] and [3].

Input: nums = [3,4,7,2,-3,1,4,2], k = 7
Output: 4

🔹 Constraints:
1 <= nums.length <= 2 * 10⁴
-10⁵ <= nums[i] <= 10⁵
-10⁹ <= k <= 10⁹
*/
#include <iostream>
#include <vector>
#include <unordered_map>

int subarray_sum_equals(const std::vector<int>& nums,int k) {
    std::unordered_map<int, int> sum_distributions;
    int sum=0;
    int counts=0;
    for (auto& num: nums) {
        sum += num;
        auto needed_value = sum-k;
        counts += sum_distributions[needed_value];
        if (sum==k) {
            counts++;
        }
        sum_distributions[sum]++;
    }
    return counts;

}

int main() {
    //auto result = subarray_sum_equals({1,1,1}, 2); // expect 2
    //auto result = subarray_sum_equals({1,2,3}, 3); //expect 2
    auto result = subarray_sum_equals({3,4,7,2,-3,1,4,2}, 7); //expect 4

    std::cout << result << std::endl;
}