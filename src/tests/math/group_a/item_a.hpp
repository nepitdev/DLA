#pragma once

#include "../../catch.hpp"

#include <cinttypes>
#include <sstream>
#include <vector>
#include "../../../source/math/group_a/item_a.hpp"

TEST_CASE("Items in group A that share the same value should be equal") 
{
    dla::item_a x = 42_a;
    dla::item_a y = 42_a;

    REQUIRE(x == y);
}

TEST_CASE("Items in group A that do not share the same value should not be equal") 
{
    dla::item_a x = 42_a;
    dla::item_a y = 12_a;

    REQUIRE(x != y);
}

TEST_CASE("Items in group A should obay modular addition") 
{
    dla::item_a x = 54_a;
    dla::item_a y = 10_a;
    dla::item_a z = 3_a;

    REQUIRE(x + y == z);
}

TEST_CASE("Items in group A should obay the commutative property of addition") 
{
    dla::item_a x = 54_a;
    dla::item_a y = 10_a;

    REQUIRE(x + y == y + x);
}

TEST_CASE("Items in group A should obay the assosiative property of addition") 
{
    dla::item_a x = 23_a;
    dla::item_a y = 32_a;
    dla::item_a z = 11_a;
    dla::item_a w = 5_a;

    REQUIRE((x + y) + z == w);
    REQUIRE(x + (y + z) == w);
}

TEST_CASE("Items in group A should obay the identity property of addition") 
{
    dla::item_a x = 54_a;
    dla::item_a y = 0_a;

    REQUIRE(x + y == x);
    REQUIRE(y + x == x);
}

TEST_CASE("Items in group A should obay modular subtraction") 
{
    dla::item_a x = 54_a;
    dla::item_a y = 10_a;
    dla::item_a z = 3_a;

    REQUIRE(z - y == x);
}

TEST_CASE("Items in group A should obay the identity property of subtraction") 
{
    dla::item_a x = 54_a;
    dla::item_a y = 0_a;

    REQUIRE(x - y == x);
}

TEST_CASE("Items in group A should obay modular multiplication") 
{
    dla::item_a x = 16_a;
    dla::item_a y = 4_a;
    dla::item_a z = 3_a;

    REQUIRE(x * y == z);
}

TEST_CASE("Items in group A should obay the commutative property of multiplication") 
{
    dla::item_a x = 16_a;
    dla::item_a y = 4_a;

    REQUIRE(x * y == y * x);
}

TEST_CASE("Items in group A should obay the assosiative property of multiplication") 
{
    dla::item_a x = 23_a;
    dla::item_a y = 32_a;
    dla::item_a z = 11_a;
    dla::item_a w = 44_a;

    REQUIRE((x * y) * z == w);
    REQUIRE(x * (y * z) == w);
}

TEST_CASE("Items in group A should obay the identity property of multiplication") 
{
    dla::item_a x = 54_a;
    dla::item_a y = 1_a;

    REQUIRE(x * y == x);
    REQUIRE(y * x == x);
}

TEST_CASE("Items in group A should obay modular division") 
{
    dla::item_a x = 16_a;
    dla::item_a y = 4_a;
    dla::item_a z = 3_a;

    REQUIRE(z / y == x);
}

TEST_CASE("Items in group A should obay the identity property of division") 
{
    dla::item_a x = 54_a;
    dla::item_a y = 1_a;

    REQUIRE(x / y == x);
}

TEST_CASE("An item in group A minus itself should equal zero") 
{
    dla::item_a x = 42_a;
    dla::item_a y = 0_a;

    REQUIRE(x - x == y);
}

TEST_CASE("Adding a negative to an item in group A should be the same as subtracting") 
{
    dla::item_a x = 42_a;
    dla::item_a y = 12_a;

    REQUIRE(x + (-y) == x - y);
}

TEST_CASE("An item in group A divided by itself should equal one") 
{
    dla::item_a x = 42_a;
    dla::item_a y = 1_a;

    REQUIRE(x / x == y);
}

TEST_CASE("Multiplying a riciprical by an item in group A should be the same as dividing") 
{
    dla::item_a x = 42_a;
    dla::item_a y = 12_a;

    REQUIRE(x * (!y) == x / y);
}