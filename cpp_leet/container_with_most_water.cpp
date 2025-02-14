/*
Got it! Here's another commonly asked coding interview question:

Question: Container With Most Water
You are given an integer array height where height[i] represents the height of a vertical line at index i. There are n such lines, and together they form vertical lines on a 2D plane.

Find the maximum amount of water a container can store by choosing two lines.

Example 1:
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49

Example 2:
Input: height = [1,1]
Output: 1

Constraints:
2 <= len(height) <= 10^5
0 <= height[i] <= 10^4
10'000'000'000
*/
#include <iostream>
#include <vector>
#include <ranges>
#include <forward_list>

struct TestCase {
    std::vector<int> heights;
    int golden_maximum_water;
};

template <std::ranges::bidirectional_range T>
void print_vector(const T& input) {
    std::cout << "[";
    for (auto it = input.begin(); it != input.end(); it++) {
        std::cout << *it;
        if (it != std::prev(input.end())) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

template<std::ranges::bidirectional_range T>
long int find_max_area(const T& heights) {
    if ( heights.size()==0 ) {
        return 0;
    }
    auto left = heights.begin();
    auto right = std::prev(heights.end());
    long int area {0};
    long int max_area_so_far {0};
    while( left != right ) {
        area = std::distance(left, right)*std::min(*left, *right);
        // std::cout << area << " " << *left << " " << *right << std::endl;
        max_area_so_far = std::max(max_area_so_far, area);
        if ( *left < *right ) {
            left++;
        } else {
            right--;
        }
    }
    return max_area_so_far;
}

int main() {
    std::vector<TestCase> testcases = {
        {{1, 8, 6, 2, 5, 4, 8, 3, 7}, 49},
        {{1, 1}, 1},
        {{}, 0},
        {{1, 2, 4, 4, 5}, 8}
    };
    for (const auto& testcase: testcases) {
        std::cout << "Input: ";
        print_vector(testcase.heights);
        auto max_area = find_max_area(testcase.heights);
        std::cout << " -> " << max_area << ": ";
        std::cout << (max_area == testcase.golden_maximum_water?"PASS":"FAIL") << std::endl;
    }
    return 0;
}