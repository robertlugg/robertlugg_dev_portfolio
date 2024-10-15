"""

You have a long flowerbed in which some of the plots are planted, and some are not.
However, flowers cannot be planted in adjacent plots.

Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not empty,
 and an integer n
, return true if n new flowers can be planted in the flowerbed without violating the
no-adjacent-flowers rule and false otherwise.

# Examples

## Example 1:
Input: flowerbed = [1,0,0,0,1], n = 1
Output: true
## Example 2:
Input: flowerbed = [1,0,0,0,1], n = 2
Output: false
 
# Constraints:
1 <= flowerbed.length <= 2 * 104
flowerbed[i] is 0 or 1.
There are no two adjacent flowers in flowerbed.
0 <= n <= flowerbed.length
"""
from dataclasses import dataclass
from typing import List


class Solution:
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        if not flowerbed:
            return False
        skip_an_index=False
        flowers_added=0
        for idx in range(0, len(flowerbed)-2):
            # If space is full, don't do anything and also skip the next space
            if flowerbed[idx]:
                skip_an_index = True
                continue
            if skip_an_index:
                # even though this space is empty, skip it due to previous space either having
                # a flower to begin with or having a flower added.
                skip_an_index = False
                continue
            # If space ahead is also clear, add a flower and skip next space
            if not flowerbed[idx+1]:
                flowers_added += 1
                skip_an_index = True
        # Special case the last location in the flowerbed
        if not flowerbed[-1]:
            if len(flowerbed)>1:
                if not flowerbed[-2]:
                    flowers_added += 1
            else:
                flowers_added += 1

        # print(f'{flowers_added}')
        return flowers_added>=n
    

@dataclass
class TestCase:
    flowerbed: List[int]
    n: int
    golden_answer: bool

def main() -> None:
    testcases = [
        TestCase([1,0,0,0,1], 1, True),
        TestCase([1,0,0,0,1], 2, False),
        TestCase([], 4, False),
        TestCase([1], 1, False),
        TestCase([0], 1, True),
        TestCase([0, 1, 0, 0, 1], 1, False),
        TestCase([1, 1, 1, 1, 1], 4, False),
        TestCase([0, 0, 0, 0, 1], 2, True),
        TestCase([0, 0, 0, 0, 1], 3, False),
        TestCase([0, 0, 0, 0, 1], 4, False),
        TestCase([0, 1, 0], 1, False),
        TestCase([0, 1, 0, 0], 1, True),
    ]
    for testcase in testcases:
        result = Solution().canPlaceFlowers(testcase.flowerbed, testcase.n)
        msg = 'pass' if result == testcase.golden_answer else 'fail'
        msg += f':\n  {result}\n  {testcase}'
        print(msg)

if __name__ == '__main__':
    main()
