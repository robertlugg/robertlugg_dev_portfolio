"""
392. Is Subsequence

Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string
by deleting some (can be none) of the characters without disturbing the relative positions
of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

# Examples 

## Example 1:
Input: s = "abc", t = "ahbgdc"
Output: true

## Example 2:
Input: s = "axc", t = "ahbgdc"
Output: false
 

# Constraints:

0 <= s.length <= 100
0 <= t.length <= 104
s and t consist only of lowercase English letters.
 

Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 109,
and you want to check one by one to see if t has its subsequence. In this scenario,
how would you change your code?
"""
from dataclasses import dataclass

class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        t_idx = 0
        fully_found = False
        for s_char in s:
            while t_idx < len(t):
                if s_char==t[t_idx]:
                    t_idx += 1
                    break
                t_idx += 1
            else:
                break
        else:
            fully_found = True
        return fully_found
    

@dataclass
class TestCase:
    subsequence: str
    test_string: str
    golden: bool


def main()->None:
    testcases = [
        TestCase("abc", "ahbgdc", golden=True),
        TestCase("axc", "ahbgdc", golden=False),
        TestCase("abc", "a", golden=False),
        TestCase("abc", "", golden=False),
        TestCase("", "abc", golden=True),
        TestCase("aa", "abc", golden=False),
    ]
    for testcase in testcases:
        result = Solution().isSubsequence(testcase.subsequence, testcase.test_string)
        msg = 'pass' if result == testcase.golden else 'fail'
        msg += f': {result}, {testcase}'
        print(msg)

if __name__ == '__main__':
    main()
