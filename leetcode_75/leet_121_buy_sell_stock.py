"""
leetcode 121

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different
day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit,
return 0.

 
# Examples
## Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

## Example 2:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
 
# Constraints:
1 <= prices.length <= 105
0 <= prices[i] <= 104
"""
from typing import List
from dataclasses import dataclass

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if len(prices)==1:
            return 0
        follower_idx = 0
        max_profit = 0
        for leader_idx in range(1, len(prices)):
            max_profit = max(max_profit, prices[leader_idx] - prices[follower_idx])
            if prices[leader_idx] < prices[follower_idx]:
                follower_idx = leader_idx
        return max_profit
    

@dataclass
class TestCase:
    prices: List[int]
    golden_output: int

def main() -> None:
    testcases = [
        TestCase([1, 6], 5),
        TestCase([8, 2, 9, 6, 8], 7),
        TestCase([2, 2, 3, 2, 8, 1, 5], 6),
        TestCase([3, 2, 4, 1, 3, 1, 6], 5),
        TestCase([4, 1, 2, 3, 9, 1, 2, 3], 8),
        TestCase([7, 1, 5, 3, 6, 4], 5),
        TestCase([7, 6, 4, 3, 1], 0),
        TestCase([5, 5, 5, 5], 0)
    ]
    for testcase in testcases:
        result = Solution().maxProfit(testcase.prices)
        if result == testcase.golden_output:
            print(f'Pass, {testcase}')
        else:
            print(f'Fail, {testcase}')


if __name__ == '__main__':
    main()
