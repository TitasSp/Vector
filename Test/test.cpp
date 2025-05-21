#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Vector.h"

TEST_CASE("Vector default constructor", "[Vector]") {
    Vector v;
    REQUIRE(v.size() == 0);
}

TEST_CASE("Vector size constructor", "[Vector]") {
    Vector v(5);
    REQUIRE(v.size() == 5);
}

TEST_CASE("Vector fill constructor", "[Vector]") {
    Vector v(3, 2.5);
    REQUIRE(v.size() == 3);
    for (int i = 0; i < 3; ++i) {
        REQUIRE(v[i] == Approx(2.5));
    }
}

TEST_CASE("Vector setElem and get", "[Vector]") {
    Vector v(2);
    v.setElem(0, 1.1);
    v.setElem(1, 2.2);
    REQUIRE(v[0] == Approx(1.1));
    REQUIRE(v[1] == Approx(2.2));
}

TEST_CASE("Vector operator[] bounds", "[Vector]") {
    Vector v(2);
    REQUIRE_THROWS_AS(v[-1], std::out_of_range);
    REQUIRE_THROWS_AS(v[2], std::out_of_range);
}

TEST_CASE("Vector add (push_back equivalent)", "[Vector]") {
    Vector v;
    v.add(1.1);
    v.add(2.2);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == Approx(1.1));
    REQUIRE(v[1] == Approx(2.2));
}

TEST_CASE("Vector pop", "[Vector]") {
    Vector v;
    v.add(1.0);
    v.add(2.0);
    v.pop();
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == Approx(1.0));
    v.pop();
    REQUIRE_THROWS_AS(v.pop(), std::out_of_range);
}


TEST_CASE("Vector insert", "[Vector]") {
    Vector v;
    v.add(1);
    v.add(3);
    v.insert(1, 2); // now should be 1, 2, 3
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == Approx(1));
    REQUIRE(v[1] == Approx(2));
    REQUIRE(v[2] == Approx(3));
    //REQUIRE_THROWS_AS(v.insert(-1, 0), std::out_of_range);
}

TEST_CASE("Vector swap", "[Vector]") {
    Vector v(2);
    v.setElem(0, 1.0);
    v.setElem(1, 2.0);
    v.swap(0, 1);
    REQUIRE(v[0] == Approx(2.0));
    REQUIRE(v[1] == Approx(1.0));
}

TEST_CASE("Vector clear (set elements to 0)", "[Vector]") {
    Vector v(2, 5.0);
    v.clear();
    REQUIRE(v[0] == 0.0);
    REQUIRE(v[1] == 0.0);
}

TEST_CASE("Vector erase (deletes whole vector)", "[Vector]") {
    Vector v(3, 3.0);
    v.erase();
    REQUIRE(v.size() == 0);
}

TEST_CASE("Vector resize (increase and shrink)", "[Vector]") {
    Vector v(2, 1.0);
    v.resize(4);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == Approx(1.0));
    REQUIRE(v[1] == Approx(1.0));
    v.resize(1);
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == Approx(1.0));
}

TEST_CASE("Vector shrink", "[Vector]") {
    Vector v(5, 1.0);
    v.shrink();
    REQUIRE(v.size() == 5);
    v.resize(3);
    v.shrink();
    REQUIRE(v.size() == 3);
}
