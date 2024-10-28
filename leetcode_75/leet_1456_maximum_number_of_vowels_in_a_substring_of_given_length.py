"""
Given a string s and an integer k, return the maximum number of
vowel letters in any substring of s with length k.

Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

# Examples

## Example 1:
Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.

## Example 2:
Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.

## Example 3:
Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.

# Constraints:

1 <= s.length <= 1e5
s consists of lowercase English letters.
1 <= k <= s.length
"""
from dataclasses import dataclass

VOWELS = "aeiou"

class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        num_vowels = sum([c in VOWELS for c in s[:k]])
        max_vowels = num_vowels
        for head_index in range(k, len(s)):
            if s[head_index-k] in VOWELS:
                num_vowels -= 1
            if s[head_index] in VOWELS:
                num_vowels += 1
            max_vowels = max(max_vowels, num_vowels)
        return max_vowels

@dataclass
class TestCase:
    s: str
    k: int
    golden: int

def main()->None:
    testcases = [
        TestCase(s = "abciiidef", k = 3, golden=3),
        TestCase(s = "aeiou", k = 2, golden=2),
        TestCase(s = "leetcode", k = 3, golden=2),
        # TestCase(s = "aaa", k = 5, golden=3),
        # TestCase(s = "a", k = 5, golden=1),
        TestCase(s = "a", k = 1, golden=1),
        TestCase(s = "rbrtkdjrhgp", k = 5, golden=0),
    ]
    for testcase in testcases:
        result = Solution().maxVowels(testcase.s, testcase.k)
        msg = 'pass' if result==testcase.golden else 'fail'
        msg += f': {result} {testcase}'
        print(msg)

if __name__ == '__main__':
    main()