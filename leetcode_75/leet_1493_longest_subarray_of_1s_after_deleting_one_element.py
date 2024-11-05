"""
Given a binary array nums, you should delete one element from it.

Return the size of the longest non-empty subarray containing only 1's in the resulting array.
Return 0 if there is no such subarray.

# Examples
## Example 1:
Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.
## Example 2:
Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray with value of 1's is [1,1,1,1,1].
## Example 3:
Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.

# Constraints:
1 <= nums.length <= 1e5
nums[i] is either 0 or 1.
"""
from typing import List
from dataclasses import dataclass

class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        longest_subarray = 0
        num_zeros = 0
        tail_idx = 0
        for head_idx, head in enumerate(nums):
            if head==0:
                num_zeros += 1
            while num_zeros>1:
                if nums[tail_idx]==0:
                    num_zeros -= 1
                tail_idx += 1
            subarray_length = head_idx-tail_idx
            longest_subarray = max(longest_subarray, subarray_length)
        return longest_subarray

@dataclass
class TestCase():
    nums: List[int]
    golden: int

def main()->None:
    testcases = [
        TestCase(nums = [1,1,0,1], golden=3),
        TestCase(nums = [0,1,1,1,0,1,1,0,1], golden=5),
        TestCase(nums = [1,1,1], golden=2),
        TestCase(nums = [0], golden=0),
        TestCase(nums = [1], golden=0),
        TestCase(nums = [1,1], golden=1),
        TestCase(nums = [1,1,0], golden=2),
        TestCase(nums = [1,1,0,0], golden=2),
    ]
    for testcase in testcases:
        result = Solution().longestSubarray(testcase.nums)
        msg = 'pass' if result==testcase.golden else 'fail'
        msg += f': {result} {testcase}'
        print(msg)

if __name__ == '__main__':
    main()
