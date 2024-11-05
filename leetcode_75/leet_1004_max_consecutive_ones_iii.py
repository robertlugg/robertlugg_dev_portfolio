"""
1004. Max Consecutive Ones III

Given a binary array nums and an integer k, return
the maximum number of consecutive 1's in the array
if you can flip at most k 0's.

# Examples

## Example 1:
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
                       1,1
                       -----------
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

## Example 2:
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
                      1,1       1
                  -------------------
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

# Constraints:

1 <= nums.length <= 1e5
nums[i] is either 0 or 1.
0 <= k <= nums.length
"""
from typing import List
from dataclasses import dataclass

class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        max_length = 0
        tail_idx = 0
        for head_idx, head in enumerate(nums):
            if head==0:
                k -= 1
            # If k<0, we need to advance tail until k==0
            while k < 0:
                if nums[tail_idx]==0:
                    k += 1
                tail_idx += 1
            max_length = max(max_length, head_idx-tail_idx+1)
            # print(f'{tail_idx}-{head_idx}, {k}  {max_length}')
        return max_length

@dataclass
class TestCase:
    nums: List[int]
    k: int
    golden: int

def main()->None:
    testcases = [
        TestCase(nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2, golden=6),
        TestCase(nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3, golden=10),
        TestCase(nums = [0], k = 3, golden=1),
        TestCase(nums = [0], k = 0, golden=0),
        TestCase(nums = [1], k = 0, golden=1),
        TestCase(nums = [1], k = 1, golden=1),
        TestCase(nums = [0,0,0,0,1,0,1,0,1,0,1,0,0,0,0], k = 3, golden=7),
        TestCase(nums = [0,0,0,0,1,0,1,0,1,0,1,0,0,0,0], k = 2, golden=5),
        TestCase(nums = [0,0,0,0,1,0,1,0,1,0,1,1,0,0,0], k = 0, golden=2),
        TestCase(nums = [0,1], k = 0, golden=1),
        TestCase(nums = [0,1], k = 1, golden=2),
        TestCase(nums = [0,1], k = 2, golden=2),
        TestCase(nums = [0,0,1], k = 0, golden=1),
        TestCase(nums = [0,0,1], k = 1, golden=2),
        TestCase(nums = [0,0], k = 1, golden=1),
        TestCase(nums = [0,1], k = 1, golden=2),
        TestCase(nums = [1,0], k = 1, golden=2),
        TestCase(nums = [0,0,1], k = 1, golden=2),
        TestCase(nums = [0,0,1,0], k = 1, golden=2),
        TestCase(nums = [0,0,1,1], k = 1, golden=3),
        TestCase(nums = [0,0,1,0], k = 2, golden=3),
    ]
    for testcase in testcases:
        result = Solution().longestOnes(testcase.nums, testcase.k)
        msg = 'pass' if result == testcase.golden else 'fail'
        msg += f': {result} {testcase}'
        print(msg)

if __name__ == '__main__':
    main()


