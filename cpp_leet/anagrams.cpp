/*
🔥 Next Question (Easy-Medium)
📌 Problem: Find All Anagrams in a String

🔹 Description:
Given two strings, s and p, return all starting indices of p's anagrams in s.
You can return the result in any order.

🔹 Examples:
Input: s = "cbaebabacd", p = "abc"
Output: [0, 6]
Explanation: 
- The substring starting at index 0 ("cba") is an anagram of "abc".
- The substring starting at index 6 ("bac") is an anagram of "abc".

Input: s = "abab", p = "ab"
Output: [0, 1, 2]
Explanation:
- The substring starting at index 0 ("ab") is an anagram of "ab".
- The substring starting at index 1 ("ba") is an anagram of "ab".
- The substring starting at index 2 ("ab") is an anagram of "ab".
🔹 Constraints:

1 <= s.length, p.length <= 3 * 10⁴
s and p consist of lowercase English letters only.

*/
#include <iostream>
#include <string>
#include <vector>
#include <array>


std::vector<int> find_anagrams(const std::string& s, const std::string& p) {
    if (s.size()<p.size()) { return {}; }
    std::array<int, 26> s_freq{0};
    std::array<int, 26> p_freq{0};
    std::vector<int> found;
    int match_count = 26; // Initially the counts match.
    // Compute p letter frequency once
    for(auto ch: p) {
        auto idx = ch-'a';
        if (p_freq[idx]==0) {
            match_count--;
        }
        p_freq[idx]++;
    }
    std::cout << "p:";
    for(auto pf:p_freq) {
        std::cout << pf << " ";
    };
    std::cout << std::endl;

    for(int i=0; i<s.size(); ++i) {
        auto idx = s[i]-'a';
        // Update the front
        if (s_freq[idx]==p_freq[idx]) match_count--;
        s_freq[idx]++;
        if (s_freq[idx]==p_freq[idx]) match_count++;

        // Update the back once we get past the first few characters
        if (i>=p.size()) {
            auto bidx = s[i-p.size()]-'a';
            if (s_freq[bidx]==p_freq[bidx]) match_count--;
            s_freq[bidx]--;
            if (s_freq[bidx]==p_freq[bidx]) match_count++;
        }

        if (match_count==26) {
            found.push_back(i-p.size()+1);
        }

        
    }

    std::cout << "s:";
    for(auto sf:s_freq) {
        std::cout << sf << " ";
    };
    std::cout << std::endl;

    return found;
}

int main() {
    //auto result = find_anagrams("cbaebabacd","abc");
    auto result = find_anagrams("abab","ab");

    std::cout << "Result: ";
    for(auto r:result) {
        std::cout << r << " ";
    }
    std::cout << std::endl;
}