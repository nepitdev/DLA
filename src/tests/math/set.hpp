#pragma once

#include "../catch.hpp"

#include <cstdint>
#include <vector>
#include "../../source/math/set.hpp"

TEST_CASE("A set should be able to hold arbitrary payloads") 
{
    class testset : public dla::set<uint8_t, uint8_t> 
    {
    public:
        testset(): set(8, 8, 8) { }
    };

    REQUIRE_NOTHROW([&](){
        testset t;
    }());
}