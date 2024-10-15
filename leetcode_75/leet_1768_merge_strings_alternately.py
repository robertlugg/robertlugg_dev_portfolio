"""
leetcode 1768
You are given two strings word1 and word2. Merge the strings by adding letters in alternating order,
starting with word1. If a string is longer than the other, append the additional letters onto the
end of the merged string.

Return the merged string.

 
# Examples 
## Example 1:

Input: word1 = "abc", word2 = "pqr"
Output: "apbqcr"
Explanation: The merged string will be merged as so:
word1:  a   b   c
word2:    p   q   r
merged: a p b q c r

## Example 2:

Input: word1 = "ab", word2 = "pqrs"
Output: "apbqrs"
Explanation: Notice that as word2 is longer, "rs" is appended to the end.
word1:  a   b 
word2:    p   q   r   s
merged: a p b q   r   s

## Example 3:

Input: word1 = "abcd", word2 = "pq"
Output: "apbqcd"
Explanation: Notice that as word1 is longer, "cd" is appended to the end.
word1:  a   b   c   d
word2:    p   q 
merged: a p b q c   d
 

# Constraints:

1 <= word1.length, word2.length <= 100
word1 and word2 consist of lowercase English letters.
"""
from dataclasses import dataclass

@dataclass
class TestCase:
    word1: str
    word2: str
    golden_output: str


class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        merged = [f'{a}{b}' for a,b in zip(word1, word2)]
        min_word_len = min(len(word1), len(word2))
        if len(word1)>min_word_len:
            merged.extend(word1[min_word_len:])
        if len(word2)>min_word_len:
            merged.extend(word2[min_word_len:])
        return ''.join(merged)

def main()->None:
    testcases = [
        TestCase('abc', 'pqr', 'apbqcr'),
        TestCase('ab', 'pqrs', 'apbqrs'),
        TestCase('abcd', 'pq', 'apbqcd')
    ]
    for testcase in testcases:
        result = Solution().mergeAlternately(testcase.word1, testcase.word2)
        msg = 'pass' if result==testcase.golden_output else 'FAIL'
        msg += f': ({result}) {testcase}'
        print(msg)

if __name__ == '__main__':
    main()
