/*

STL + RAII Interview Challenge (Moderate Difficulty)

This problem is something you might see in a C++ interview to test your knowledge of RAII,
STL algorithms, and smart pointers.

Problem: Word Frequency Counter

Write a C++ program that:

    Reads a text file (given as input.txt).
    Counts the frequency of each word (case-insensitive).
    Prints the words in descending order of frequency.
    Uses RAII principles (i.e., smart pointers) to manage resources.
    Uses STL containers (std::map or std::unordered_map).
    Uses STL algorithms (std::transform, std::sort).

Example Input (input.txt)
Hello world hello C++ programming. Programming is fun!
Expected Output
hello: 2
programming: 2
is: 1
fun: 1
c++: 1
world: 1
(The words are sorted by frequency, highest first.)
*/
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>

void clean_word(std::string& input) {
    std::erase_if(input, [](char ch) {
        return !std::isalnum(ch);
    });
    std::transform(input.begin(), input.end(), input.begin(), [](char ch) {
        return std::tolower(ch);
    });
}

int main() {
    std::unordered_map<std::string, int> words;
    std::ifstream inputFile("wfc_input1.txt");
    if (!inputFile) {
        std::cerr << "Unable to open input file.";
        return 1;
    }
    std::string token;
    while (inputFile >> token) {
        clean_word(token);
        words[token]++;
    };
    std::vector<std::pair<std::string, int>> vec(words.begin(), words.end());
    //std::transform(words.begin(), words.end(), std::back_inserter(vec), [](auto a) {return std::pair(a.first, a.second);});
    std::stable_sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    for (const auto& [word, count] : vec) {
        std::cout << word << ": " << count << std::endl;
    }
}

