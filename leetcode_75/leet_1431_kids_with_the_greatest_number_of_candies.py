"""
There are n kids with candies. You are given an integer array candies, where each candies[i]
represents the number of candies the ith kid has,
and an integer extraCandies, denoting the number of extra candies that you have.

Return a boolean array result of length n,
where result[i] is true if, after giving the ith kid all the extraCandies, 
they will have the greatest number of candies among all the kids, or false otherwise.

Note that multiple kids can have the greatest number of candies.

# Examples

## Example 1:
Input: candies = [2,3,5,1,3], extraCandies = 3
Output: [true,true,true,false,true] 
Explanation: If you give all extraCandies to:
- Kid 1, they will have 2 + 3 = 5 candies, which is the greatest among the kids.
- Kid 2, they will have 3 + 3 = 6 candies, which is the greatest among the kids.
- Kid 3, they will have 5 + 3 = 8 candies, which is the greatest among the kids.
- Kid 4, they will have 1 + 3 = 4 candies, which is not the greatest among the kids.
- Kid 5, they will have 3 + 3 = 6 candies, which is the greatest among the kids.

## Example 2:
Input: candies = [4,2,1,1,2], extraCandies = 1
Output: [true,false,false,false,false] 
Explanation: There is only 1 extra candy.
Kid 1 will always have the greatest number of candies, even if a different kid is given the extra candy.

## Example 3:
Input: candies = [12,1,12], extraCandies = 10
Output: [true,false,true]
 

# Constraints:

n == candies.length
2 <= n <= 100
1 <= candies[i] <= 100
1 <= extraCandies <= 50
"""
from typing import List
from dataclasses import dataclass

@dataclass
class TestCase:
    candies: List[int]
    extraCandies: int
    golden_most_candies: List[bool]


class Solution:
    def kidsWithCandies(self, candies: List[int], extraCandies: int) -> List[bool]:
        if not len(candies):
            return []
        most_candies = max(candies)
        result = [ (x+extraCandies)>=most_candies for x in candies]
        return result


def main() -> None:
    testcases = [
        TestCase([5, 5], 1, [True, True]),
        TestCase([2,3,5,1,3], 3, [True, True, True, False, True]),
        TestCase([4,2,1,1,2], 1, [True, False, False, False, False]),
        TestCase([12,1,12], 10, [True, False, True]),
        TestCase([], 1, []),
    ]
    for testcase in testcases:
        result = Solution().kidsWithCandies(testcase.candies, testcase.extraCandies)
        if result == testcase.golden_most_candies:
            msg = 'pass'
        else:
            msg = 'fail'
        msg += f',\n  {result}\n  {testcase}'
        print(msg)

if __name__ == '__main__':
    main()

