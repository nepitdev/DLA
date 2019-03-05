#pragma once

#include "../catch.hpp"

#include <cstdint>
#include <iostream>
#include "../../source/math/vector.hpp"
#include "../../source/math/group_a/item_a.hpp"

TEST_CASE("An empty vector should have no elements") 
{
    dla::vector<uint8_t> v;
    REQUIRE(v.size() == 0);
}

TEST_CASE("The elements of a vector should be zero if no value is specifyed") 
{
    dla::vector<uint8_t> v(5);
    for (int i = 0; i < 5; i++) {
        REQUIRE(v[i] == 0);
    }
}

TEST_CASE("A standard library vector should be convertable to a DLA vector") 
{
    std::vector<uint8_t> a = { 0, 1, 2, 3, 4 };
    dla::vector<uint8_t> v(a);
    for (int i = 0; i < 5; i++) {
        REQUIRE(v[i] == i);
    }
}