"""
1732. Find the Highest Altitude

There is a biker going on a road trip. The road trip consists of n + 1 points
at different altitudes. The biker starts his trip on point 0 with altitude equal 0.

You are given an integer array gain of length n where gain[i] is the net gain in altitude
between points i​​​​​​ and i + 1 for all (0 <= i < n). Return the highest altitude of a point.

 
# Examples

## Example 1:
Input: gain = [-5,1,5,0,-7]
Output: 1
Explanation: The altitudes are [0,-5,-4,1,1,-6]. The highest is 1.

## Example 2:
Input: gain = [-4,-3,-2,-1,4,3,2]
Output: 0
Explanation: The altitudes are [0,-4,-7,-9,-10,-6,-3,-1]. The highest is 0.
 

Constraints:

n == gain.length
1 <= n <= 100
-100 <= gain[i] <= 100
"""
from dataclasses import dataclass
from typing import List

@dataclass
class TestCase():
    gain: List[int]
    golden: int

class Solution:
    def largestAltitude(self, gain: List[int]) -> int:
        altitude = 0
        max_altitude = altitude
        # print(f'{altitude}', end=',')
        for n in gain:
            altitude += n
            # print(f'{altitude}', end=',')
            max_altitude = max(max_altitude, altitude)
        return max_altitude
    

def main()->None:
    testcases = [
        TestCase(gain = [-5,1,5,0,-7], golden=1),
        TestCase(gain = [-4,-3,-2,-1,4,3,2], golden=0),
    ]
    for testcase in testcases:
        result = Solution().largestAltitude(testcase.gain)
        msg = 'pass' if result==testcase.golden else 'fail'
        msg += f': {result}  {testcase}'
        print(msg)

if __name__ == '__main__':
    main()

