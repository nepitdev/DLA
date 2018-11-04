#pragma once

#include "../catch.hpp"

#include <cinttypes>
#include <sstream>
#include <vector>
#include "../../source/util/rand.hpp"

TEST_CASE("Two different rands should have different outputs") 
{
    dla::rand ra, rb;
    std::stringstream sa, sb;
    bool match = true;
    for (int i = 0; i < 32; i++)
    {
        uint8_t va = ra.next();
        uint8_t vb = rb.next();
        sa << std::setfill('0') << std::setw(2) << std::hex << (int) va;
        sb << std::setfill('0') << std::setw(2) << std::hex << (int) vb;
    }
    REQUIRE(sa.str() != sb.str());
}