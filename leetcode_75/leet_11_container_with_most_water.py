"""
You are given an integer array height of length n. There are n vertical lines drawn such that
the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that
the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

# Examples

## Example 1:
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7].
In this case, the max area of water (blue section) the container can contain is 49.

## Example 2:
Input: height = [1,1]
Output: 1

# Constraints:

n == height.length
2 <= n <= 105
0 <= height[i] <= 104

"""
from typing import List
from dataclasses import dataclass

# @dataclass
# class WaterContainer:
#     index_left: int
#     height_left: int
#     index_right: int
#     height_right: int
#     area: int = 0

# def area_calculate(heights: List[int], index_left, index_right):
#     return min(heights[index_left], heights[index_right]) * abs(index_left-index_right)

class Solution:
    def maxArea(self, height: List[int]) -> int:
        # Early exit if 0 or one elements in height
        if len(height)<=1:
            return 0

        """
        Begin at far left and far right.  compute area.  Move one side or the other 
        inward looking for a larger area.  Move the side that's lowest."""
        index_left = 0
        index_right = len(height)-1
        max_area = 0
        loops_remaining = len(height)+1; # safety from infinite loops
        while loops_remaining:
            loops_remaining -= 1
            area = min(height[index_left], height[index_right]) * abs(index_left-index_right)
            max_area = max(max_area, area)
            if height[index_left]<height[index_right]:
                index_left += 1
            else:
                index_right -= 1
            if index_left == index_right:
                break
       
        return max_area

@dataclass
class TestCase:
    heights: List[int]
    golden_area: int

def main()->None:
    testcases = [
        TestCase([1,8,6,2,5,4,8,3,7], 49),
        TestCase([1,8,6,2,5,4,8,3,2], 40),
        TestCase([1,1], 1),
        TestCase([1,2,3,4,5,6,7,8,9], 20), # 8, 14, 18, 20, 20, 18, 14, 8
    ]
    for testcase in testcases:
        result = Solution().maxArea(testcase.heights)
        msg = 'pass' if result == testcase.golden_area else 'fail'
        msg += f': {result} {testcase}'
        print(msg)

if __name__ == '__main__':
    main()