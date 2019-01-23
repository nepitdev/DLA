#pragma once

#include "../../catch.hpp"

#include <cinttypes>
#include <sstream>
#include <vector>
#include "../../../source/util/bytestream.hpp"
#include "../../../source/math/group_a/item_a.hpp"

TEST_CASE("The default value of items in group A should be zero") 
{
    dla::item_a x;

    REQUIRE(x == dla::item_a::ZERO);
}

TEST_CASE("Items from group A should be constructable using an 8-bit integer") 
{
    uint8_t n = 7;
    dla::item_a x(n);

    REQUIRE(x.getval() == n);
}

TEST_CASE("Items from group A should be constructable using an bytestream") 
{
    class teststream : public dla::bytestream { 
        uint8_t next() { return 42; }
    };
    teststream s;
    
    dla::item_a x(s);

    REQUIRE(x.getval() == 42);
}

TEST_CASE("The byte array of an item from group A should match its value") 
{
    dla::item_a x = 42_a;
    std::vector<uint8_t> bytes = x.getBytes();
    REQUIRE(bytes.size() == 1);
    REQUIRE(x.getval() == bytes[0]);
}

TEST_CASE("Items in group A should only be saltable if setting the high order bit to one does not make the item smaller") 
{
    dla::item_a x = 12_a;
    dla::item_a y = 42_a;
    REQUIRE(x.canBeSalted());
    REQUIRE(!y.canBeSalted());
    dla::item_a z = x + dla::item_a::HIGH_ORDER_BIT;
    dla::item_a w = y + dla::item_a::HIGH_ORDER_BIT;
    REQUIRE(z.getval() > x.getval());
    REQUIRE(w.getval() < y.getval());
}

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
    dla::item_a y = dla::item_a::ZERO;

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
    dla::item_a y = dla::item_a::ZERO;

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
    dla::item_a y = dla::item_a::UNIT;

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
    dla::item_a y = dla::item_a::UNIT;

    REQUIRE(x / y == x);
}

TEST_CASE("An item in group A minus itself should equal zero") 
{
    dla::item_a x = 42_a;
    dla::item_a y = dla::item_a::ZERO;

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
    dla::item_a y = dla::item_a::UNIT;

    REQUIRE(x / x == y);
}

TEST_CASE("Multiplying a riciprical by an item in group A should be the same as dividing") 
{
    dla::item_a x = 42_a;
    dla::item_a y = 12_a;

    REQUIRE(x * (!y) == x / y);
}

TEST_CASE("Incrementing an item from group A should function similarly to addition") 
{
    dla::item_a x = 54_a;
    dla::item_a y = 10_a;
    dla::item_a z = x;
    z += y;

    REQUIRE(x + y == z);
}

TEST_CASE("Decrementing an item from group A should function similarly to subtraction") 
{
    dla::item_a x = 3_a;
    dla::item_a y = 10_a;
    dla::item_a z = x;
    z -= y;

    REQUIRE(x - y == z);
}

TEST_CASE("Scaling an item from group A should function similarly to multiplication") 
{
    dla::item_a x = 23_a;
    dla::item_a y = 32_a;
    dla::item_a z = x;
    z *= y;

    REQUIRE(x * y == z);
}

TEST_CASE("Factoring an item from group A should function similarly to division") 
{
    dla::item_a x = 4_a;
    dla::item_a y = 32_a;
    dla::item_a z = x;
    z /= y;

    REQUIRE(x / y == z);
}