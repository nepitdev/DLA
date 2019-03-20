#include "../../catch.hpp"

#include <cinttypes>
#include <sstream>
#include <vector>
#include "../../../source/util/bytestream.hpp"
#include "../../../source/math/group_c/item_c.hpp"

TEST_CASE("The default value of items in group C should be zero") 
{
    dla::item_c x;

    REQUIRE(x == dla::item_c::ZERO);
}

TEST_CASE("Items from group C should be constructable using an 16-bit integer") 
{
    uint16_t n = 263;
    dla::item_c x(n);

    REQUIRE(x.getval() == n);
}

TEST_CASE("Items from group C should be constructable using an bytestream") 
{
    class teststream : public dla::bytestream { 
        uint8_t next() { return 42; }
    };
    teststream s;
    
    dla::item_c x(s);

    REQUIRE(x.getval() == 10794);
}

TEST_CASE("An item from group C and its vector of bytes should have the same value") 
{
    dla::item_c x = 543_c;
    std::vector<uint8_t> bytes = x.getBytes();
    REQUIRE(bytes.size() == 2);
    uint16_t val = 0;
    for (int i = 0; i < 2; i++)
        val += bytes[i] << ((1 - i) * 8);
    REQUIRE(val == x.getval());
}

TEST_CASE("Items in group C should only be saltable if setting the high order bit to one does not make the item smaller") 
{
    dla::item_c x = 42_c;
    dla::item_c y = 32767_c;
    REQUIRE(x.canBeSalted());
    REQUIRE(!y.canBeSalted());
    dla::item_c z = x + dla::item_c::HIGH_ORDER_BIT;
    dla::item_c w = y + dla::item_c::HIGH_ORDER_BIT;
    REQUIRE(z.getval() > x.getval());
    REQUIRE(w.getval() < y.getval());
}

TEST_CASE("Items in group C that share the same value should be equal") 
{
    dla::item_c x = 42_c;
    dla::item_c y = 42_c;

    REQUIRE(x == y);
}

TEST_CASE("Items in group C that do not share the same value should not be equal") 
{
    dla::item_c x = 42_c;
    dla::item_c y = 12_c;

    REQUIRE(x != y);
}

TEST_CASE("Items in group C should obay modular addition") 
{
    dla::item_c x = 65520_c;
    dla::item_c y = 2_c;
    dla::item_c z = 1_c;

    REQUIRE(x + y == z);
}

TEST_CASE("Items in group C should obay the commutative property of addition") 
{
    dla::item_c x = 54_c;
    dla::item_c y = 65520_c;

    REQUIRE(x + y == y + x);
}

TEST_CASE("Items in group C should obay the assosiative property of addition") 
{
    dla::item_c x = 3_c;
    dla::item_c y = 65520_c;
    dla::item_c z = 2_c;
    dla::item_c w = 4_c;

    REQUIRE((x + y) + z == w);
    REQUIRE(x + (y + z) == w);
}

TEST_CASE("Items in group C should obay the identity property of addition") 
{
    dla::item_c x = 54_c;
    dla::item_c y = dla::item_c::ZERO;

    REQUIRE(x + y == x);
    REQUIRE(y + x == x);
}

TEST_CASE("Items in group C should obay modular subtraction") 
{
    dla::item_c x = 65520_c;
    dla::item_c y = 2_c;
    dla::item_c z = 1_c;

    REQUIRE(z - y == x);
}

TEST_CASE("Items in group C should obay the identity property of subtraction") 
{
    dla::item_c x = 54_c;
    dla::item_c y = dla::item_c::ZERO;

    REQUIRE(x - y == x);
}

TEST_CASE("Items in group C should obay modular multiplication") 
{
    dla::item_c x = 6123_c;
    dla::item_c y = 2123_c;
    dla::item_c z = 25971_c;

    REQUIRE(x * y == z);
}

TEST_CASE("Items in group C should obay the commutative property of multiplication") 
{
    dla::item_c x = 16_c;
    dla::item_c y = 4_c;

    REQUIRE(x * y == y * x);
}

TEST_CASE("Items in group C should obay the assosiative property of multiplication") 
{
    dla::item_c x = 3_c;
    dla::item_c y = 65520_c;
    dla::item_c z = 2_c;
    dla::item_c w = 65515_c;

    REQUIRE((x * y) * z == w);
    REQUIRE(x * (y * z) == w);
}

TEST_CASE("Items in group C should obay the identity property of multiplication") 
{
    dla::item_c x = 54_c;
    dla::item_c y = dla::item_c::UNIT;

    REQUIRE(x * y == x);
    REQUIRE(y * x == x);
}

TEST_CASE("Items in group C should obay modular division") 
{
    dla::item_c x = 6123_c;
    dla::item_c y = 2123_c;
    dla::item_c z = 25971_c;

    REQUIRE(z / y == x);
}

TEST_CASE("Items in group C should obay the identity property of division") 
{
    dla::item_c x = 54_c;
    dla::item_c y = dla::item_c::UNIT;

    REQUIRE(x / y == x);
}

TEST_CASE("An item in group C minus itself should equal zero") 
{
    dla::item_c x = 42_c;
    dla::item_c y = dla::item_c::ZERO;

    REQUIRE(x - x == y);
}

TEST_CASE("Adding a negative to an item in group C should be the same as subtracting") 
{
    dla::item_c x = 42_c;
    dla::item_c y = 12_c;

    REQUIRE(x + (-y) == x - y);
}

TEST_CASE("An item in group C divided by itself should equal one") 
{
    dla::item_c x = 42_c;
    dla::item_c y = dla::item_c::UNIT;

    REQUIRE(x / x == y);
}

TEST_CASE("Multiplying a riciprical by an item in group C should be the same as dividing") 
{
    dla::item_c x = 42_c;
    dla::item_c y = 12_c;

    REQUIRE(x * (!y) == x / y);
}

TEST_CASE("Incrementing an item from group C should function similarly to addition") 
{
    dla::item_c x = 54_c;
    dla::item_c y = 10_c;
    dla::item_c z = x;
    z += y;

    REQUIRE(x + y == z);
}

TEST_CASE("Decrementing an item from group C should function similarly to subtraction") 
{
    dla::item_c x = 3_c;
    dla::item_c y = 10_c;
    dla::item_c z = x;
    z -= y;

    REQUIRE(x - y == z);
}

TEST_CASE("Scaling an item from group C should function similarly to multiplication") 
{
    dla::item_c x = 23_c;
    dla::item_c y = 32_c;
    dla::item_c z = x;
    z *= y;

    REQUIRE(x * y == z);
}

TEST_CASE("Factoring an item from group C should function similarly to division") 
{
    dla::item_c x = 4_c;
    dla::item_c y = 32_c;
    dla::item_c z = x;
    z /= y;

    REQUIRE(x / y == z);
}