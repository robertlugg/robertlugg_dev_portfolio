/*
Compile using:
g++ -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion \
    -Wnull-dereference -Wformat=2 -fsanitize=address,undefined \
    -fstack-protector-strong -std=c++20 -g -Werror \
    -DBOOST_ALLOW_DEPRECATED_HEADERS rectangle.cpp -o rectangle

g++ -Wall -Wextra -std=c++20 -g -Werror \
    -DBOOST_ALLOW_DEPRECATED_HEADERS rectangle.cpp -o rectangle


*/
#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/box.hpp>

namespace bg = boost::geometry;
namespace bgm = boost::geometry::model;
using Point2D = bgm::point<int64_t, 2, bg::cs::cartesian>;

int main() {
    const auto pt1 = Point2D(10, 10);
    const auto pt2 = Point2D(30, 50);
    // Partial covered which means covered_by is false;
        // const auto pt3 = Point2D(11, 11);
        // const auto pt4 = Point2D(35, 55);
    // totally covered
        // const auto pt3 = Point2D(9, 9);
        // const auto pt4 = Point2D(31, 51);
    // Not interacting
    const auto pt3 = Point2D(40, 60);
    const auto pt4 = Point2D(42, 62);
    
    auto r1 = bgm::box<Point2D>(pt1, pt2);
    auto r2 = bgm::box<Point2D>(pt3, pt4);

    const auto x = bg::covered_by(r1, r2);
    std::cout << bg::wkt(r1) << std::endl;
    std::cout << bg::wkt(r2) << std::endl;
    std::cout << "r1 is completely covered by r2: " << std::boolalpha << x << std::endl;

    auto rout = bgm::box<Point2D>{};
    const auto y = bg::intersection(r1, r2, rout);
    std::cout << bg::wkt(rout) << std::endl;
    std::cout << std::boolalpha << "Has intersection: " << y << std::endl;

}