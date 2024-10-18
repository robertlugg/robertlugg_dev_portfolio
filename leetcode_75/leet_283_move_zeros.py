"""
283. Move Zeroes

Given an integer array nums, move all 0's to the end of it while maintaining
the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

# Examples

## Example 1:
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]

## Example 2:
Input: nums = [0]
Output: [0]
 
# Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
 

Follow up: Could you minimize the total number of operations done?
"""
from typing import List
from dataclasses import dataclass

class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        insert_index = 0
        number_of_zeros = 0
        for num in nums:
            if num==0:
                number_of_zeros += 1
                continue
            nums[insert_index] = num
            insert_index += 1
        for counter in range(number_of_zeros):
            idx = len(nums)-counter-1
            nums[idx] = 0

@dataclass
class TestCase:
    nums: List[int]
    golden: List[int]

def main() -> None:
    testcases = [
        TestCase([0,1,0,3,12], [1,3,12,0,0] ),
        TestCase([0], [0])
    ]
    for testcase in testcases:
        original_nums = list(testcase.nums)
        Solution().moveZeroes(testcase.nums)
        msg = 'pass' if testcase.nums == testcase.golden else 'fail'
        msg += f': {testcase.nums}, {original_nums}, {testcase}'
        print(msg)

if __name__ == '__main__':
    main()
