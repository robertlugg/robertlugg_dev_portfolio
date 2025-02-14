/* 
🔥 Next Question (Easy - Sorting Pattern)
📌 Problem: Merge Two Sorted Lists
🔹 Description:
You are given the heads of two sorted linked lists, list1 and list2.

Merge the two lists into one sorted linked list and return the head of the new merged list.

🔹 Examples:

Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Input: list1 = [], list2 = []
Output: []

Input: list1 = [], list2 = [0]
Output: [0]
🔹 Constraints:

The two linked lists are already sorted in non-decreasing order.
The final merged list should also be sorted.


*/
#include <iostream>
#include <list>

std::list<int> merge_sorted_lists(std::list<int> list1, std::list<int> list2) {
    // Early exit if one or both lists are empty.
    // Copies of input lists are copied because I destroy the lists.
    if (list1.empty()) return list2;
    if (list2.empty()) return list1;

    std::list<int> return_list;
    while (!list1.empty() && !list2.empty()) {
        auto val1 = list1.front();
        auto val2 = list2.front();
        if (val1<val2) {
            return_list.push_back(val1);
            list1.pop_front();
            continue;
        }
        return_list.push_back(val2);
        list2.pop_front();
    }
    //At this point either one or both input lists are empty.
    while (!list1.empty()) {
        return_list.push_back(list1.front());
        list1.pop_front();
    }
    while (!list2.empty()) {
        return_list.push_back(list2.front());
        list2.pop_front();
    }

    // if (!list1.empty()) {
    //     std::copy(list1.begin(), list1.end(), return_list.end() );
    // }
    // if (!list2.empty()) {
    //     std::copy(list2.begin(), list2.end(), return_list.end() );
    // }
    return return_list;
}

int main() {
    // std::list<int> list1{1, 2, 4};
    // std::list<int> list2{1, 3, 4};

    //auto result = merge_sorted_lists({1, 2, 4}, {1, 3, 4});
    auto result = merge_sorted_lists({6 }, {1, 2, 3});
    for(auto value: result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}