/*
# Problem: Merge Intervals
Difficulty: Medium

## Problem Statement
Given an array of intervals where intervals[i] = [starti, endi],
merge all overlapping intervals and return an array of the non-overlapping intervals
that cover all the intervals in the input.

## Examples
### Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Intervals [1,3] and [2,6] overlap, so they are merged into [1,6].

### Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

## Constraints:
1 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti <= endi <= 10^4

## Follow-Up Questions:
What is the time complexity of your solution?
Can you solve it in-place to reduce space complexity?
*/
#include <iostream>
#include <vector>

using Interval = std::pair<int, int>;

void print_intervals(std::vector<Interval>& intervals) {
    std::cout << "[";
    for(const auto& interval: intervals) {
        std::cout << " [" << interval.first << ", " << interval.second << "],";
    }
    std::cout << "]" << std::endl;
}

/* Assumptions:
        - Each pair is ordered by first element
*/
void merge_intervals(std::vector<Interval>& io_intervals) {
    if (!io_intervals.size()) {
        return;
    }

    int output_interval_index = 0;
    Interval& output_interval = io_intervals[output_interval_index];
    for(int i=1; i<io_intervals.size(); i++) {
        auto& this_interval = io_intervals[i];
        //std::cout << "\n" <<output_interval_index << "  output_interval " << output_interval.first << ":" << output_interval.second;
        //std::cout << " " << i << "  this_interval " << this_interval.first << ":" << this_interval.second;
        if (this_interval.first<=output_interval.second) {
            output_interval.second = this_interval.second;
            continue;
        }
        //output_interval is a reference to the io_intervals elements
        output_interval_index++;
        Interval& output_interval = io_intervals[output_interval_index];
        output_interval = io_intervals[i];
    }
    io_intervals.resize(output_interval_index+1);
    return;
};

struct TestCase {
    std::vector<Interval> input;
    std::vector<Interval> golden_output;
};

std::vector<TestCase> testcases {
    { {{1,3}, {2,6}, {8,10}, {15,18}}, {{1,6}, {8,10}, {15,18}} },
    { {{1,4}, {4,5}}, {{1,5}} },
    { {{1,4}, {4,5}, {5,6}}, {{1,6}} },
    { {}, {} },
};

int main() {
    std::cout << "Merge Intervals" << std::endl;
    std::cout << "---------------" << std::endl;

    for (auto& testcase: testcases) {
        std::cout << "Input:  ";
        print_intervals(testcase.input);
        merge_intervals(testcase.input);
        std::cout << "Output: ";
        print_intervals(testcase.input);
        std::cout << "Golden: ";
        print_intervals(testcase.golden_output);
    }
}