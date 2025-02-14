#include <iostream>
#include <vector>

int main() {
    auto v1 = std::vector(2, 2.6);
    auto v2 = std::vector{2, 2.6};
    std::cout << std::boolalpha << (v1[0] == v2[0]) << std::endl;
    std::cout << v1[0] << "   " << v1[1] << std::endl;
    std::cout << v2[0] << "   " << v2[1] << std::endl;
    std::cout << typeid(v1).name() << std::endl;
}