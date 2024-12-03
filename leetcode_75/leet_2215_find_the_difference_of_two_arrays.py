"""
Given two 0-indexed integer arrays nums1 and nums2, return a list answer of size 2 where:

answer[0] is a list of all distinct integers in nums1 which are not present in nums2.
answer[1] is a list of all distinct integers in nums2 which are not present in nums1.
Note that the integers in the lists may be returned in any order.

 
# Examples

## Example 1:
Input: nums1 = [1,2,3], nums2 = [2,4,6]
Output: [[1,3],[4,6]]
Explanation:
For nums1, nums1[1] = 2 is present at index 0 of nums2, whereas nums1[0] = 1 and nums1[2] = 3 are not present in nums2. Therefore, answer[0] = [1,3].
For nums2, nums2[0] = 2 is present at index 1 of nums1, whereas nums2[1] = 4 and nums2[2] = 6 are not present in nums2. Therefore, answer[1] = [4,6].

## Example 2:
Input: nums1 = [1,2,3,3], nums2 = [1,1,2,2]
Output: [[3],[]]
Explanation:
For nums1, nums1[2] and nums1[3] are not present in nums2. Since nums1[2] == nums1[3], their value is only included once and answer[0] = [3].
Every integer in nums2 is present in nums1. Therefore, answer[1] = [].
 

# Constraints:

1 <= nums1.length, nums2.length <= 1000
-1000 <= nums1[i], nums2[i] <= 1000
"""
from dataclasses import dataclass
from typing import List

class Solution:
    def findDifference(self, nums1: List[int], nums2: List[int]) -> List[List[int]]:
        set1 = set(nums1)
        set2 = set(nums2)
        only1 = set1-set2
        only2 = set2-set1
        return [list(only1), list(only2)]
    
@dataclass
class TestCase():
    nums1: List[int]
    nums2: List[int]
    golden: List[List[int]]

def main()->None:
    testcases = [
        TestCase(nums1 = [1,2,3], nums2 = [2,4,6], golden=[[1,3],[4,6]]),
        TestCase(nums1 = [1,2,3,3], nums2 = [1,1,2,2], golden=[[3],[]]),
    ]
    for testcase in testcases:
        result = Solution().findDifference(testcase.nums1, testcase.nums2)
        msg = 'pass' if result==testcase.golden else 'fail'
        msg += f': {result} {testcase}'
        print(msg)

if __name__ == '__main__':
    main()
    