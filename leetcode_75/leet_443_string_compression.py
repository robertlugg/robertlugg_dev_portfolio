"""
Given an array of characters chars, compress it using the following algorithm:

Begin with an empty string s. For each group of consecutive repeating characters in chars:

If the group's length is 1, append the character to s.
Otherwise, append the character followed by the group's length.
The compressed string s should not be returned separately, but instead, be stored
in the input character array chars. Note that group lengths that are 10 or longer
will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the array.

You must write an algorithm that uses only constant extra space.

# Examples

## Example 1:
Input: chars = ["a","a","b","b","c","c","c"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".

## Example 2:
Input: chars = ["a"]
Output: Return 1, and the first character of the input array should be: ["a"]
Explanation: The only group is "a", which remains uncompressed since it's a single character.

## Example 3:
Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".
 
# Constraints:
1 <= chars.length <= 2000
chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.

"""
from typing import List
from dataclasses import dataclass

class Solution:
    def compress(self, chars: List[str]) -> int:
        current_char = chars[0]
        num_consecutive = 0
        insertion_index = 0 # Where to put the results within the chars list
        for char in chars:
            print(f'{chars}\n{char}: {current_char} {num_consecutive} {insertion_index}')
            if char == current_char:
                num_consecutive += 1
                continue
            # char has changed
            chars[insertion_index] = current_char
            insertion_index += 1
            if num_consecutive > 1:
                num_consecutive_as_string = f'{num_consecutive}'
                for digit in num_consecutive_as_string:
                    chars[insertion_index] = digit
                    insertion_index += 1
            current_char = char
            num_consecutive = 1
        if num_consecutive:
            chars[insertion_index] = current_char
            insertion_index += 1
            if num_consecutive > 1:
                num_consecutive_as_string = f'{num_consecutive}'
                for digit in num_consecutive_as_string:
                    chars[insertion_index] = digit
                    insertion_index += 1
        print(chars)
        return insertion_index

    
@dataclass
class TestCase:
    chars: List[str]
    golden_output: int

def main() -> None:
    testcases = [
        TestCase(["a","a","b","b","c","c","c"], 6),
        TestCase(["a"], 1),
        TestCase(["a","b","b","b","b","b","b","b","b","b","b","b","b"], 4)
    ]
    for testcase in testcases:
        result = Solution().compress(testcase.chars)
        msg = 'pass' if result==testcase.golden_output else 'fail'
        msg += f': {result}, {testcase}'
        print(msg)

if __name__ == '__main__':
    main()

