/*
Problem: Minimum Number of Arrows to Burst Balloons 🎯
Difficulty: Medium

g++ burst_ballons.cpp -std=c++20 -Wall -Wextra -Werror


Problem Statement
There are n balloons, and each balloon is represented as an interval [x_start, x_end],
where x_start is the balloon's left edge and x_end is its right edge.

An arrow can be shot vertically at any x coordinate. When an arrow is shot,
it bursts all balloons that intersect with that x-coordinate.

Return the minimum number of arrows needed to burst all balloons.

Example 1
    Input: points = [[10,16],[2,8],[1,6],[7,12]]
    Output: 2
    Explanation:  
    - One arrow can burst balloons at `[1,6]` and `[2,8]`  
    - Another arrow can burst `[7,12]` and `[10,16]`.

Example 2
    Input: points = [[1,2],[3,4],[5,6],[7,8]]
    Output: 4
    Explanation: Each balloon is separate, so **4 arrows** are needed.

Example 3
    Input: points = [[1,2],[2,3],[3,4],[4,5]]
    Output: 2
    Explanation:  
    - One arrow bursts `[1,2]` and `[2,3]`.  
    - Another arrow bursts `[3,4]` and `[4,5]`.

Constraints
    1 <= points.length <= 10^4
    points[i].length == 2
    -2^31 <= x_start < x_end <= 2^31 - 1

*/
#include <vector>
#include <iostream>

struct Balloon {
    int x_start;
    int x_end;
};

int main() {
    //std::vector<Balloon> input = {  {10,16},{2,8},{1,6},{7,12}  }; // 2
    //std::vector<Balloon> input = {  {1,2},{3,4},{5,6},{7,8}  }; // 4
    std::vector<Balloon> input = {  {1,2},{2,3},{3,4},{4,5}  }; // 2
    if (input.size()==0) {return 0;}
    if (input.size()==1) {return 1;}
    std::sort(input.begin(), input.end(), [] (auto& a, auto& b) { return a.x_start < b.x_start; });

    std::pair<int, int> shot_range;

    int arrow_count = 0;
    shot_range = {input[0].x_start, input[0].x_end};
    for(size_t index=1; index<input.size(); index++) {
        if (input[index].x_start > shot_range.second) {
            arrow_count++;
            shot_range = {input[index].x_start, input[index].x_end};
            continue;
        }
        shot_range.first = input[index].x_start;
        shot_range.second = std::min(shot_range.second, input[index].x_end);
    }
    arrow_count++;

    std::cout << "[ ";
    for (auto& i: input) {
        std::cout << "[" << i.x_start << ", " << i.x_end << "], ";
    }
    std::cout << "]" << std::endl;
    std::cout << "Arrows Needed:" << arrow_count << std::endl;
    return 0;
}
