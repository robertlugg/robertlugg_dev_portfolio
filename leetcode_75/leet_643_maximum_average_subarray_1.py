"""
You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k that has the maximum
average value and return this value. Any answer with a calculation
error less than 1e-5 will be accepted.

# Examples

## Example 1:
Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

## Example 2:
Input: nums = [5], k = 1
Output: 5.00000

# Constraints:

n == nums.length
1 <= k <= n <= 1e5
-1e4 <= nums[i] <= 1e4
"""
from dataclasses import dataclass
from typing import List

class Solution:
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        # (k-1) is used to reference a zero-based index.
        head = min(k-1, len(nums)-1)
        tail = max(head-(k-1), 0)
        total = sum(nums[tail:head+1])
        avg = total/k
        #print(f'{head} {tail} {total} {avg}')
        if head < k-1:
            return avg
        max_avg = avg
        for idx in range(head+1, len(nums)):
            total += -nums[idx-k] + nums[idx]
            avg = total/k
            max_avg = max(max_avg, avg)
        return max_avg

@dataclass
class TestCase:
    nums: List[int]
    k: int
    golden: float

def main()->None:
    testcases = [
        TestCase(nums = [1,12,-5,-6,50,3], k = 4, golden=12.75),
        TestCase(nums = [5], k = 1, golden=5.0)
    ]
    for testcase in testcases:
        result = Solution().findMaxAverage(testcase.nums, testcase.k)
        msg = 'pass' if result==testcase.golden else 'fail'
        msg += f': {result}, {testcase}'
        print(msg)

if __name__ == '__main__':
    main()
