"""
345. Reverse Vowels of a String

Given a string s, reverse only all the vowels in the string and return it.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and
upper cases, more than once.

 

Example 1:

Input: s = "IceCreAm"

Output: "AceCreIm"

Explanation:

The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".

Example 2:

Input: s = "leetcode"

Output: "leotcede"

 

Constraints:

1 <= s.length <= 3 * 105
s consist of printable ASCII characters.
"""
from typing import List
from dataclasses import dataclass


class Solution:
    def reverseVowels(self, s: str) -> str:
        """
        Algorithm:
        for each vowel, add an item to a list of what it is and its index.
        Sort the list of vowels (but not the index list)
        for each in index list, put the corresponding vowel in the original string.
        """
        text_chars = [char for char in s]
        the_vowels = "AaEeIiOoUu"
        vowels: List[str] = list()
        vowels_indexes: List[int] = list()
        for input_index, char in enumerate(text_chars):
            if char in the_vowels:
                vowels.append(char)
                vowels_indexes.append(input_index)
        #print(f'{vowels}: {vowels_indexes}')
        vowels.reverse()
        for idx, input_index in enumerate(vowels_indexes):
            text_chars[input_index] = vowels[idx]
        #print(f'{text_chars}')
        return ''.join(text_chars)
    

@dataclass
class TestCase:
    input: str
    golden: str


def main() -> None:
    testcases = [
        TestCase('IceCreAm', 'AceCreIm'),
        TestCase('leetcode', 'leotcede'),
    ]
    for testcase in testcases:
        result = Solution().reverseVowels(testcase.input)
        msg = 'pass' if result == testcase.golden else 'fail'
        msg += f':  result={result}, golden={testcase.golden}'
        print(msg)

if __name__ == '__main__':
    main()