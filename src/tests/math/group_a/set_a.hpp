#pragma once

#include "../../catch.hpp"

#include "../../../source/math/group_a/set_a.hpp"

TEST_CASE("A set of Group A should buildable using base64") 
{
    dla::set_a s(5);
    std::string b64 = "0123456789abcde";
    s.setBase64(b64);
    REQUIRE(b64 == s.getBase64());
}