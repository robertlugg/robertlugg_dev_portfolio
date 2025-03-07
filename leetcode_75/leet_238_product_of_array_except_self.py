"""
Given an integer array nums, return an array answer such that answer[i] is equal to
the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

# Examples

## Example 1:
Input: nums = [1,2,3,4]
Output: [24,12,8,6]

## Example 2:
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
 

# Constraints:
2 <= nums.length <= 105
-30 <= nums[i] <= 30
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 

# Follow up:
Can you solve the problem in O(1) extra space complexity?
(The output array does not count as extra space for space complexity analysis.)
"""
from typing import List
from dataclasses import dataclass


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        ret = [1] * len(nums)
        forward_product = 1
        for idx in range(0, len(nums)):
            ret[idx] = forward_product
            forward_product *= nums[idx]
        reverse_product = 1
        for idx in range(len(nums)-1, -1, -1):
            ret[idx] *= reverse_product
            reverse_product *= nums[idx]
        return ret
    
@dataclass
class TestCase:
    input: List[int]
    golden_output: List[int]


def main()->None:
    testcases = [
        TestCase([1,2,3,4], [24,12,8,6]),
        TestCase([-1,1,0,-3,3], [0,0,9,0,0]),
        TestCase([], []),
        # TestCase([4], []) ## Not allowed in problem statement
        TestCase([7, 0, 0], [0, 0, 0]),
        TestCase([3, 0, 2], [0, 6, 0]),
    ]
    for testcase in testcases:
        result = Solution().productExceptSelf(testcase.input)
        msg = 'pass' if result==testcase.golden_output else 'fail'
        msg += f': {result}, {testcase}'
        print(msg)

if __name__ == '__main__':
    main()
