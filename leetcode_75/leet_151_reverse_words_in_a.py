"""
151. Reverse Words in a String
Medium
Topics
Companies
Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be
separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

 

Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
 

Constraints:

1 <= s.length <= 104
s contains English letters (upper-case and lower-case), digits, and spaces ' '.
There is at least one word in s.
 

Follow-up: If the string data type is mutable in your language,
can you solve it in-place with O(1) extra space?
"""
from dataclasses import dataclass
from typing import List

class Solution:
    def reverseWords(self, s: str) -> str:
        by_word_split = s.split()
        by_word_split.reverse()
        
        # for char in s:
        #     print(f'{s}: {char.isspace()}')
        return " ".join(by_word_split)
    

@dataclass
class TestCase:
    input_string: str
    golden: str

def main() -> None:
    testcases = [
        TestCase("one", "one"),
        TestCase("", ""),
        TestCase("the sky is blue", "blue is sky the"),
        TestCase("  hello world  ", "world hello"),
        TestCase("a good   example", "example good a"),
        TestCase("  a \tgood \n  example     ", "example good a"),
    ]
    for testcase in testcases:
        result = Solution().reverseWords(testcase.input_string)
        msg = 'pass' if result==testcase.golden else 'fail'
        msg += f':\n    returned value: {result}'
        msg += f'\n    {testcase}'
        print(msg)

if __name__ == '__main__':
    main()