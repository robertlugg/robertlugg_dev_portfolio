"""
You are given an integer array nums and an integer k.

In one operation, you can pick two numbers from the array whose sum equals k
and remove them from the array.

Return the maximum number of operations you can perform on the array.

# Examples 

## Example 1:
Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Starting with nums = [1,2,3,4]:
- Remove numbers 1 and 4, then nums = [2,3]
- Remove numbers 2 and 3, then nums = []
There are no more pairs that sum up to 5, hence a total of 2 operations.

## Example 2:
Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Starting with nums = [3,1,3,4,3]:
- Remove the first two 3's, then nums = [1,4,3]
There are no more pairs that sum up to 6, hence a total of 1 operation.

# Constraints:

1 <= nums.length <= 1e5
1 <= nums[i] <= 1e9
1 <= k <= 1e9

"""
from typing import List, Dict
from dataclasses import dataclass

class Solution:
    def maxOperations(self, nums: List[int], k: int) -> int:
        if len(nums) < 2:
            return 0
        seen_numbers:Dict[int, int] = dict()
        operation_count = 0
        for num in nums:
            if num>k-1:
                continue
            other_num = k - num
            other_num_count = seen_numbers.setdefault(other_num, 0)
            if other_num_count >=1:
                seen_numbers[other_num] -= 1
                operation_count += 1
                continue
            if num not in seen_numbers.keys():
                seen_numbers[num] = 0
            seen_numbers[num] += 1
        return operation_count

@dataclass
class TestCase:
    nums: List[int]
    k: int
    golden_max_operations: int

def main()->None:
    testcases = [
        TestCase([1,2,3,4], 5, 2),
        TestCase([3,1,3,4,3], 6, 1),
        TestCase([4,1]*10123, 5, 10123),
    ]
    for testcase in testcases:
        result = Solution().maxOperations(testcase.nums, testcase.k)
        msg = 'pass' if result==testcase.golden_max_operations else 'fail'
        msg += f': {result} {testcase.nums[:20]} {testcase.k} {testcase.golden_max_operations}'
        print(msg)

if __name__ == '__main__':
    main()

