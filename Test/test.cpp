#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Vector.h"

TEST_CASE("Vector default constructor", "[Vector]") {
    Vector<int> vec;
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 0);
}
TEST_CASE("Vector constructor with size", "[Vector]") {
    Vector<int> vec(5);
    REQUIRE(vec.size() == 5);
    REQUIRE(vec.capacity() == 5);
}
TEST_CASE("Vector constructor with size and value", "[Vector]") {
    Vector<int> vec(5, 10);
    REQUIRE(vec.size() == 5);
    REQUIRE(vec.capacity() == 5);
    for (size_t i = 0; i < vec.size(); ++i) {
        REQUIRE(vec[i] == 10);
    }
}
TEST_CASE("Vector constructor with initializer list", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4, 5};
    REQUIRE(vec.size() == 5);
    REQUIRE(vec.capacity() == 5);
    for (size_t i = 0; i < vec.size(); ++i) {
        REQUIRE(vec[i] == i + 1);
    }
}
TEST_CASE("Vector copy constructor", "[Vector]") {
    Vector<int> vec1 = {1, 2, 3, 4, 5};
    Vector<int> vec2(vec1);
    REQUIRE(vec2.size() == vec1.size());
    REQUIRE(vec2.capacity() == vec1.capacity());
    for (size_t i = 0; i < vec2.size(); ++i) {
        REQUIRE(vec2[i] == vec1[i]);
    }
}
TEST_CASE("Vector move constructor", "[Vector]") {
    Vector<int> vec1 = {1, 2, 3, 4, 5};
    Vector<int> vec2(std::move(vec1));
    REQUIRE(vec2.size() == 5);
    REQUIRE(vec2.capacity() == 5);
    for (size_t i = 0; i < vec2.size(); ++i) {
        REQUIRE(vec2[i] == i + 1);
    }
    REQUIRE(vec1.size() == 0);
}
TEST_CASE("Vector copy assignment operator", "[Vector]") {
    Vector<int> vec1 = {1, 2, 3, 4, 5};
    Vector<int> vec2;
    vec2 = vec1;
    REQUIRE(vec2.size() == vec1.size());
    REQUIRE(vec2.capacity() == vec1.capacity());
    for (size_t i = 0; i < vec2.size(); ++i) {
        REQUIRE(vec2[i] == vec1[i]);
    }
}
TEST_CASE("Vector move assignment operator", "[Vector]") {
    Vector<int> vec1 = {1, 2, 3, 4, 5};
    Vector<int> vec2;
    vec2 = std::move(vec1);
    REQUIRE(vec2.size() == 5);
    REQUIRE(vec2.capacity() == 5);
    for (size_t i = 0; i < vec2.size(); ++i) {
        REQUIRE(vec2[i] == i + 1);
    }
    REQUIRE(vec1.size() == 0);
}
TEST_CASE("Vector push_back", "[Vector]") {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    REQUIRE(vec.size() == 3);
    REQUIRE(vec.capacity() >= 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
}
TEST_CASE("Vector pop_back", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4, 5};
    vec.pop_back();
    REQUIRE(vec.size() == 4);
    REQUIRE(vec[3] == 4);
}
TEST_CASE("Vector resize", "[Vector]") {
    Vector<int> vec = {1, 2, 3};
    vec.resize(5, 10);
    REQUIRE(vec.size() == 5);
    REQUIRE(vec[3] == 10);
    REQUIRE(vec[4] == 10);
}
TEST_CASE("Vector clear", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4, 5};
    vec.clear();
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 5); // Capacity should remain the same
}
TEST_CASE("Vector reserve", "[Vector]") {
    Vector<int> vec;
    vec.reserve(10);
    REQUIRE(vec.capacity() == 10);
    vec.push_back(1);
    REQUIRE(vec.size() == 1);
}
TEST_CASE("Vector shrink_to_fit", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4, 5};
    vec.reserve(10);
    vec.shrink_to_fit();
    REQUIRE(vec.capacity() == 5);
}
TEST_CASE("Vector insert", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4, 5};
    vec.insert(vec.begin() + 2, 10);
    REQUIRE(vec.size() == 6);
    REQUIRE(vec[2] == 10);
}
TEST_CASE("Vector erase", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4, 5};
    vec.erase(vec.begin() + 2);
    REQUIRE(vec.size() == 4);
    REQUIRE(vec[2] == 4);
}
TEST_CASE("Vector front and back", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4, 5};
    REQUIRE(vec.front() == 1);
    REQUIRE(vec.back() == 5);
}
TEST_CASE("Vector begin and end", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4, 5};
    REQUIRE(*vec.begin() == 1);
    REQUIRE(*(vec.end() - 1) == 5);
}
TEST_CASE("Vector swap", "[Vector]") {
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2 = {4, 5, 6};
    vec1.swap(vec2);
    REQUIRE(vec1.size() == 3);
    REQUIRE(vec2.size() == 3);
    REQUIRE(vec1[0] == 4);
    REQUIRE(vec2[0] == 1);
}
TEST_CASE("Vector at", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4, 5};
    REQUIRE(vec.at(0) == 1);
    REQUIRE(vec.at(4) == 5);
    REQUIRE_THROWS_AS(vec.at(5), std::out_of_range);
}
TEST_CASE("Vector empty", "[Vector]") {
    Vector<int> vec;
    REQUIRE(vec.empty() == true);
    vec.push_back(1);
    REQUIRE(vec.empty() == false);
}
TEST_CASE("Vector assignment operator", "[Vector]") {
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2;
    vec2 = vec1;
    REQUIRE(vec2.size() == 3);
    REQUIRE(vec2[0] == 1);
    REQUIRE(vec2[1] == 2);
    REQUIRE(vec2[2] == 3);
}
TEST_CASE("Vector equality operator", "[Vector]") {
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2 = {1, 2, 3};
    Vector<int> vec3 = {4, 5, 6};
    REQUIRE(vec1 == vec2);
    REQUIRE(vec1 != vec3);
}


