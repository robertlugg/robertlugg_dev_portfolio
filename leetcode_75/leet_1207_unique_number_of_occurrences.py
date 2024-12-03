"""
Given an array of integers arr, return true if the number of occurrences of each value in the array
is unique or false otherwise.

# Examples

## Example 1:
Input: arr = [1,2,2,1,1,3]
Output: true
Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.

## Example 2:
Input: arr = [1,2]
Output: false

## Example 3:
Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
Output: true
 
# Constraints:
    1 <= arr.length <= 1000
    -1000 <= arr[i] <= 1000
"""
from dataclasses import dataclass

class Solution():
    def uniqueOccurrences(self, arr: list[int])->bool:
        as_dict: dict[int, int] = dict()
        for e in arr:
            as_dict.setdefault(e, 1)
            as_dict[e] += 1
        return len(set(as_dict.values())) == len(as_dict.values())
    
@dataclass()
class TestCase:
    arr: list[int]
    golden: bool

def main()->None:
    testcases = [
        TestCase(arr = [1,2,2,1,1,3], golden=True),
        TestCase(arr = [1,2], golden=False),
        TestCase(arr = [-3,0,1,-3,1,1,1,-3,10,0], golden=True),
    ]
    for testcase in testcases:
        result = Solution().uniqueOccurrences(testcase.arr)
        msg = 'pass' if result == testcase.golden else 'fail'
        msg += f'. {result} {testcase}'
        print(msg)

if __name__ == '__main__':
    main()