// Demonstrate a std::optional

/*
Compile using:
g++ -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion \
    -Wnull-dereference -Wformat=2 -fsanitize=address,undefined \
    -fstack-protector-strong -std=c++20 -g -Werror optional.cpp -o opp

*/
#include <iostream>
#include <string>
#include <optional>

int main() {
    auto a = std::make_optional<int>(3);
    std::cout << *a << std::endl;
    
    auto b = std::optional<int>(std::nullopt);
    std::cout << b.value_or(21) << std::endl;

    //auto c = std::optional<int>(std::nullopt);
    //std::cout << c.value() << std::endl;

    auto d = std::optional<int>(std::nullopt);
    std::cout << *d << std::endl;
}