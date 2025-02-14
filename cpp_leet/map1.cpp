#include <iostream>
#include <string>
#include <map>

int main() {
    std::cout << "Welcome to my map program"  << std::endl;
    std::map<std::string, int> people = {
        {"Robert", 54},
        {"Jane", 52}
    };
    people["fred"] = 99;
    std::cout << people.at("Robert") << std::endl;
    for (auto [name, age]: people) {
        std::cout << name << " " << age << std::endl;
    }
}
