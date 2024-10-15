"""
leet_1071

This is my original implementation.  It passed and appears to be functioning properly, however,
ideally I should have used math.gcd(len(str1), len(str2)) since that is a lot cleaner and likely
faster.


For two strings s and t, we say "t divides s" if and only if s = t + t + t + ... + t + t
(i.e., t is concatenated with itself one or more times).

Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.

 
# Examples
## Example 1:
Input: str1 = "ABCABC", str2 = "ABC"
Output: "ABC"

## Example 2:
Input: str1 = "ABABAB", str2 = "ABAB"
Output: "AB"

## Example 3:
Input: str1 = "LEET", str2 = "CODE"
Output: ""
 
# Constraints:

1 <= str1.length, str2.length <= 1000
str1 and str2 consist of English uppercase letters.
"""
from dataclasses import dataclass

class Solution:
    def gcdOfStrings(self, str1: str, str2: str) -> str:
        l1 = len(str1)
        str1_even_multiples = set([x for x in range(1, l1+1) if l1/x==int(l1/x)])
        #print(f'{str1}, {str1_even_multiples}')
        l2 = len(str2)
        str2_even_multiples = set([x for x in range(1, l2+1) if l2/x==int(l2/x)])
        #print(f'{str2}, {str2_even_multiples}')
        divider_length = max(str1_even_multiples & str2_even_multiples)
        divider1 = str1[:divider_length]
        divider2 = str2[:divider_length]
        if divider1 != divider2:
            return '' # No common repeating substring found
        divider = divider1
        print()
        if str1 != ''.join([divider,] * (l1//divider_length)):
            return ''
        if str2 != ''.join([divider,] * (l2//divider_length)):
            return ''
        return divider

@dataclass
class TestCase:
    str1: str
    str2: str
    golden_output: str

def main() -> None:
    testcases = [
        TestCase('ABCABC', 'ABC', 'ABC'),
        TestCase('ABABAB', 'ABAB', 'AB'),
        TestCase('LEET', 'CODE', '')
    ]
    for testcase in testcases:
        result = Solution().gcdOfStrings(testcase.str1, testcase.str2)
        msg = 'pass' if result == testcase.golden_output else 'FAIL'
        msg += f' ({result}) {testcase}'
        print(msg)

if __name__ == '__main__':
    main()