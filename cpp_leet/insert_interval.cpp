/*
Problem: Insert Interval
Difficulty: Medium

Problem Statement
You are given a set of non-overlapping intervals sorted by their start time,
and a new interval that you need to insert into the list while maintaining order.

If necessary, merge overlapping intervals after the insertion.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
✅ The new interval [2,5] overlaps with [1,3], so we merge them into [1,5].

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
✅ The new interval [4,8] overlaps with [3,5], [6,7], and [8,10], so we merge them into [3,10].

Constraints:
0 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti <= endi <= 10^4
intervals is sorted by starti.

Follow-Up Questions
    * What is the time complexity of your solution?
    * Can you solve it in-place?
    * What if intervals is empty?
    * What if newInterval does not overlap with any existing intervals?

*/
#include <iostream>
#include <vector>
using Interval = std::pair<int, int>;

int main() {
    const std::vector<Interval> input{
        {1, 3}, {6,9}
    };
    Interval current_interval{2, 5};
    std::vector<Interval> outputs{};
    for(auto index=0; index<input.size(); index++) {
        if (current_interval.second < input[index].first) {
            outputs.push_back(current_interval);
            current_interval = input[index];
            std::cout << "A" << std::endl;
            continue;
        }
        if (current_interval.first > input[index].second) {
            outputs.push_back(input[index]);
            std::cout << "B" << std::endl;
            continue;
        }
        // If logic gets to this point, ranges overlap
        current_interval.first = std::min(current_interval.first, input[index].first);
        current_interval.second = std::max(current_interval.second, input[index].second);
        std::cout << "C" << std::endl;
        std::cout << current_interval.first << ":" << current_interval.second << std::endl;
        continue;
    }
    outputs.push_back(current_interval);
    std::cout << "[";
    for(auto& interval: outputs) {
        std::cout << interval.first << ":" << interval.second << ", ";
    }
    std::cout << "]" << std::endl;
}