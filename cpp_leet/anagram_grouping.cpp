/* 
New Problem: Anagram Grouping with STL
This problem will push your STL and functional programming skills.

Problem: Group Anagrams

Write a C++ program that:

    Reads words from a file (input.txt), one word per line.
    Groups anagrams together (words that contain the same letters in any order).
    Prints groups of anagrams, sorted by group size (largest first).
    Uses STL containers (std::unordered_map, std::vector).
    Uses STL algorithms (std::sort, std::transform, std::stable_sort).
    Uses RAII principles to handle file input safely.

Example Input (input.txt)
listen
silent
enlist
rat
tar
art
god
dog
evil
vile
live

Expected Output
listen silent enlist
evil vile live
rat tar art
god dog

(Groups sorted by size, words in each group can be in any order)

*/
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream fp("ag_input1.txt");
    if (!fp) {
        std::cerr << "Unable to open input file.\n";
        return 1;
    }

    // Create an unordered_map of each input word after sorting its letters
    // each key will have a list of one or more input words.
    std::unordered_map<std::string, std::vector<std::string>> tokens;
    std::string token;
    while (fp >> token) {
        //std::cout << token;
        std::string sorted_token(token);
        std::stable_sort(sorted_token.begin(), sorted_token.end());
        tokens[sorted_token].push_back(token);
    }
    std::vector<std::pair<std::string, std::vector<std::string>>> vec(tokens.begin(), tokens.end());
    std::stable_sort(vec.begin(), vec.end(), [](const auto&a, const auto&b){
        return a.second.size() > b.second.size();
    });
    for(const auto& item: vec) {
        std::cout << item.first << ":";
        for(const auto& word: item.second) {
            std::cout << " " << word;
        }
        std::cout << std::endl;
    }

}