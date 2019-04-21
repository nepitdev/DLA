#include "../../catch.hpp"

#include <cinttypes>
#include <sstream>
#include <vector>
#include "../../../src/util/bytestream.hpp"
#include "../../../src/math/group_d/item_d.hpp"

TEST_CASE("The default value of items in group D should be zero") 
{
    dla::item_d x;

    REQUIRE(x == dla::item_d::ZERO);
}

TEST_CASE("Items from group D should be constructable using an 32-bit integer") 
{
    uint32_t n = 65543;
    dla::item_d x(n);

    REQUIRE(x.getval() == n);
}

TEST_CASE("Items from group D should be constructable using an bytestream") 
{
    class teststream : public dla::bytestream { 
        uint8_t next() { return 42; }
    };
    teststream s;
    
    dla::item_d x(s);

    REQUIRE(x.getval() == 707406378);
}

TEST_CASE("An item from group D and its vector of bytes should have the same value") 
{
    dla::item_d x = 65543_d;
    std::vector<uint8_t> bytes = x.getBytes();
    REQUIRE(bytes.size() == 4);
    uint32_t val = 0;
    for (int i = 0; i < 4; i++)
        val += bytes[i] << ((3 - i) * 8);
        
    REQUIRE(val == x.getval());
}

TEST_CASE("Items in group D should only be saltable if setting the high order bit to one does not make the item smaller") 
{
    dla::item_d x = 42_d;
    dla::item_d y = 2147483647_d;
    REQUIRE(x.canBeSalted());
    REQUIRE(!y.canBeSalted());
    dla::item_d z = x + dla::item_d::HIGH_ORDER_BIT;
    dla::item_d w = y + dla::item_d::HIGH_ORDER_BIT;
    REQUIRE(z.getval() > x.getval());
    REQUIRE(w.getval() < y.getval());
}

TEST_CASE("Items in group D that share the same value should be equal") 
{
    dla::item_d x = 42_d;
    dla::item_d y = 42_d;

    REQUIRE(x == y);
}

TEST_CASE("Items in group D that do not share the same value should not be equal") 
{
    dla::item_d x = 42_d;
    dla::item_d y = 12_d;

    REQUIRE(x != y);
}

TEST_CASE("Items in group D should obay modular addition") 
{
    dla::item_d x = 4294967289_d;
    dla::item_d y = 3_d;
    dla::item_d z = 1_d;

    REQUIRE(x + y == z);
}

TEST_CASE("Items in group D should obay the commutative property of addition") 
{
    dla::item_d x = 4294967289_d;
    dla::item_d y = 42_d;

    REQUIRE(x + y == y + x);
}

TEST_CASE("Items in group D should obay the assosiative property of addition") 
{
    dla::item_d x = 3_d;
    dla::item_d y = 4294967289_d;
    dla::item_d z = 2_d;
    dla::item_d w = 3_d;

    REQUIRE((x + y) + z == w);
    REQUIRE(x + (y + z) == w);
}

TEST_CASE("Items in group D should obay the identity property of addition") 
{
    dla::item_d x = 54_d;
    dla::item_d y = dla::item_d::ZERO;

    REQUIRE(x + y == x);
    REQUIRE(y + x == x);
}

TEST_CASE("Items in group D should obay modular subtraction") 
{
    dla::item_d x = 4294967289_d;
    dla::item_d y = 3_d;
    dla::item_d z = 1_d;

    REQUIRE(z - y == x);
}

TEST_CASE("Items in group D should obay the identity property of subtraction") 
{
    dla::item_d x = 54_d;
    dla::item_d y = dla::item_d::ZERO;

    REQUIRE(x - y == x);
}

TEST_CASE("Items in group D should obay modular multiplication") 
{
    dla::item_d x = 612213_d;
    dla::item_d y = 212323_d;
    dla::item_d z = 1137882069_d;

    REQUIRE(x * y == z);
}

TEST_CASE("Items in group D should obay the commutative property of multiplication") 
{
    dla::item_d x = 16_d;
    dla::item_d y = 4_d;

    REQUIRE(x * y == y * x);
}

TEST_CASE("Items in group D should obay the assosiative property of multiplication") 
{
    dla::item_d x = 332_d;
    dla::item_d y = 65520_d;
    dla::item_d z = 212_d;
    dla::item_d w = 316592389_d;

    REQUIRE((x * y) * z == w);
    REQUIRE(x * (y * z) == w);
}

TEST_CASE("Items in group D should obay the identity property of multiplication") 
{
    dla::item_d x = 54_d;
    dla::item_d y = dla::item_d::UNIT;

    REQUIRE(x * y == x);
    REQUIRE(y * x == x);
}

TEST_CASE("Items in group D should obay modular division") 
{
    dla::item_d x = 612213_d;
    dla::item_d y = 212323_d;
    dla::item_d z = 1137882069_d;

    REQUIRE(z / y == x);
}

TEST_CASE("Items in group D should obay the identity property of division") 
{
    dla::item_d x = 54_d;
    dla::item_d y = dla::item_d::UNIT;

    REQUIRE(x / y == x);
}

TEST_CASE("An item in group D minus itself should equal zero") 
{
    dla::item_d x = 42_d;
    dla::item_d y = dla::item_d::ZERO;

    REQUIRE(x - x == y);
}

TEST_CASE("Adding a negative to an item in group D should be the same as subtracting") 
{
    dla::item_d x = 42_d;
    dla::item_d y = 12_d;

    REQUIRE(x + (-y) == x - y);
}

TEST_CASE("An item in group D divided by itself should equal one") 
{
    dla::item_d x = 42_d;
    dla::item_d y = dla::item_d::UNIT;

    REQUIRE(x / x == y);
}

TEST_CASE("Multiplying a riciprical by an item in group D should be the same as dividing") 
{
    dla::item_d x = 42_d;
    dla::item_d y = 12_d;

    REQUIRE(x * (!y) == x / y);
}

TEST_CASE("Incrementing an item from group D should function similarly to addition") 
{
    dla::item_d x = 54_d;
    dla::item_d y = 10_d;
    dla::item_d z = x;
    z += y;

    REQUIRE(x + y == z);
}

TEST_CASE("Decrementing an item from group D should function similarly to subtraction") 
{
    dla::item_d x = 3_d;
    dla::item_d y = 10_d;
    dla::item_d z = x;
    z -= y;

    REQUIRE(x - y == z);
}

TEST_CASE("Scaling an item from group D should function similarly to multiplication") 
{
    dla::item_d x = 23_d;
    dla::item_d y = 32_d;
    dla::item_d z = x;
    z *= y;

    REQUIRE(x * y == z);
}

TEST_CASE("Factoring an item from group D should function similarly to division") 
{
    dla::item_d x = 4_d;
    dla::item_d y = 32_d;
    dla::item_d z = x;
    z /= y;

    REQUIRE(x / y == z);
}