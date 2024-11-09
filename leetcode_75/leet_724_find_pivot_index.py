"""
Given an array of integers nums, calculate the pivot index of this array.

The pivot index is the index where the sum of all the numbers strictly to the left
of the index is equal to the sum of all the numbers strictly to the index's right.

If the index is on the left edge of the array, then the left sum
is 0 because there are no elements to the left. This also applies to the right edge of the array.

Return the leftmost pivot index. If no such index exists, return -1.

# Examples

## Example 1:
Input: nums = [1,7,3,6,5,6]
Output: 3
Explanation:
The pivot index is 3.
Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
Right sum = nums[4] + nums[5] = 5 + 6 = 11

## Example 2:
Input: nums = [1,2,3]
Output: -1
Explanation:
There is no index that satisfies the conditions in the problem statement.

## Example 3:
Input: nums = [2,1,-1]
Output: 0
Explanation:
The pivot index is 0.
Left sum = 0 (no elements to the left of index 0)
Right sum = nums[1] + nums[2] = 1 + -1 = 0
 

# Constraints:

1 <= nums.length <= 1e4
-1000 <= nums[i] <= 1000
"""
from typing import List
from dataclasses import dataclass

class Solution:
    def pivotIndex(self, nums: List[int]) -> int:
        total = sum(nums)
        left_sum = 0
        right_sum = total
        for idx, num in enumerate(nums):
            # print(f'{total} {left_sum} {right_sum}')
            right_sum -= num
            if left_sum==right_sum:
                return idx
            left_sum += num
        return -1
    
@dataclass
class TestCase():
    nums: List[int]
    golden: int

def main()->None:
    testcases = [
        TestCase(nums = [1,1], golden=-1),
        TestCase(nums = [0,0,0,0,0], golden=0),
        TestCase(nums = [1,1,1,1,1], golden=2),
        TestCase(nums = [1,1,2], golden=-1),
        TestCase(nums = [2,1,2], golden=1),
        TestCase(nums = [1,7,3,6,5,6], golden=3),
        TestCase(nums = [1,2,3], golden=-1),
        TestCase(nums = [2,1,-1], golden=0),
    ]
    for testcase in testcases:
        result = Solution().pivotIndex(testcase.nums)
        msg = 'pass' if result==testcase.golden else 'fail'
        msg += f': {result} {testcase}'
        print(msg)

if __name__ == '__main__':
    main()
