#include "../../catch.hpp"

#include <cinttypes>
#include <sstream>
#include <vector>
#include "../../../src/util/bytestream.hpp"
#include "../../../src/math/group_b/item_b.hpp"

TEST_CASE("The default value of items in group B should be zero") 
{
    dla::item_b x;

    REQUIRE(x == dla::item_b::ZERO);
}

TEST_CASE("Items from group B should be constructable using an 32-bit integer") 
{
    uint8_t n = 200;
    dla::item_b x(n);

    REQUIRE(x.getval() == n);
}

TEST_CASE("Items from group B should be constructable using an bytestream") 
{
    class teststream : public dla::bytestream { 
        uint8_t next() { return 42; }
    };
    teststream s;
    
    dla::item_b x(s);

    REQUIRE(x.getval() == 42);
}

TEST_CASE("An item from group B and its vector of bytes should have the same value") 
{
    dla::item_b x = 200_b;
    std::vector<uint8_t> bytes = x.getBytes();
    REQUIRE(bytes.size() == 1);
    uint8_t val = bytes[0];

    REQUIRE(val == x.getval());
}

TEST_CASE("Items in group B should only be saltable if setting the high order bit to one does not make the item smaller") 
{
    dla::item_b x = 42_b;
    dla::item_b y = 200_b;
    REQUIRE(x.canBeSalted());
    REQUIRE(!y.canBeSalted());
    dla::item_b z = x + dla::item_b::HIGH_ORDER_BIT;
    dla::item_b w = y + dla::item_b::HIGH_ORDER_BIT;
    REQUIRE(z.getval() > x.getval());
    REQUIRE(w.getval() < y.getval());
}

TEST_CASE("Items in group B that share the same value should be equal") 
{
    dla::item_b x = 42_b;
    dla::item_b y = 42_b;

    REQUIRE(x == y);
}

TEST_CASE("Items in group B that do not share the same value should not be equal") 
{
    dla::item_b x = 42_b;
    dla::item_b y = 12_b;

    REQUIRE(x != y);
}

TEST_CASE("Items in group B should obay modular addition") 
{
    dla::item_b x = 200_b;
    dla::item_b y = 52_b;
    dla::item_b z = 1_b;

    REQUIRE(x + y == z);
}

TEST_CASE("Items in group B should obay the commutative property of addition") 
{
    dla::item_b x = 200_b;
    dla::item_b y = 100_b;

    REQUIRE(x + y == y + x);
}

TEST_CASE("Items in group B should obay the assosiative property of addition") 
{
    dla::item_b x = 200_b;
    dla::item_b y = 50_b;
    dla::item_b z = 2_b;
    dla::item_b w = 1_b;

    REQUIRE((x + y) + z == w);
    REQUIRE(x + (y + z) == w);
}

TEST_CASE("Items in group B should obay the identity property of addition") 
{
    dla::item_b x = 54_b;
    dla::item_b y = dla::item_b::ZERO;

    REQUIRE(x + y == x);
    REQUIRE(y + x == x);
}

TEST_CASE("Items in group B should obay modular subtraction") 
{
    dla::item_b x = 200_b;
    dla::item_b y = 52_b;
    dla::item_b z = 1_b;

    REQUIRE(z - y == x);
}

TEST_CASE("Items in group B should obay the identity property of subtraction") 
{
    dla::item_b x = 54_b;
    dla::item_b y = dla::item_b::ZERO;

    REQUIRE(x - y == x);
}

TEST_CASE("Items in group B should obay modular multiplication") 
{
    dla::item_b x = 200_b;
    dla::item_b y = 100_b;
    dla::item_b z = 171_b;

    REQUIRE(x * y == z);
}

TEST_CASE("Items in group B should obay the commutative property of multiplication") 
{
    dla::item_b x = 200_b;
    dla::item_b y = 4_b;

    REQUIRE(x * y == y * x);
}

TEST_CASE("Items in group B should obay the assosiative property of multiplication") 
{
    dla::item_b x = 50_b;
    dla::item_b y = 75_b;
    dla::item_b z = 100_b;
    dla::item_b w = 6_b;

    REQUIRE((x * y) * z == w);
    REQUIRE(x * (y * z) == w);
}

TEST_CASE("Items in group B should obay the identity property of multiplication") 
{
    dla::item_b x = 54_b;
    dla::item_b y = dla::item_b::UNIT;

    REQUIRE(x * y == x);
    REQUIRE(y * x == x);
}

TEST_CASE("Items in group B should obay modular division") 
{
    dla::item_b x = 200_b;
    dla::item_b y = 100_b;
    dla::item_b z = 171_b;

    REQUIRE(z / y == x);
}

TEST_CASE("Items in group B should obay the identity property of division") 
{
    dla::item_b x = 54_b;
    dla::item_b y = dla::item_b::UNIT;

    REQUIRE(x / y == x);
}

TEST_CASE("An item in group B minus itself should equal zero") 
{
    dla::item_b x = 42_b;
    dla::item_b y = dla::item_b::ZERO;

    REQUIRE(x - x == y);
}

TEST_CASE("Adding a negative to an item in group B should be the same as subtracting") 
{
    dla::item_b x = 42_b;
    dla::item_b y = 12_b;

    REQUIRE(x + (-y) == x - y);
}

TEST_CASE("An item in group B divided by itself should equal one") 
{
    dla::item_b x = 42_b;
    dla::item_b y = dla::item_b::UNIT;

    REQUIRE(x / x == y);
}

TEST_CASE("Multiplying a riciprical by an item in group B should be the same as dividing") 
{
    dla::item_b x = 42_b;
    dla::item_b y = 12_b;

    REQUIRE(x * (!y) == x / y);
}

TEST_CASE("Incrementing an item from group B should function similarly to addition") 
{
    dla::item_b x = 200_b;
    dla::item_b y = 100_b;
    dla::item_b z = x;
    z += y;

    REQUIRE(x + y == z);
}

TEST_CASE("Decrementing an item from group B should function similarly to subtraction") 
{
    dla::item_b x = 100_b;
    dla::item_b y = 200_b;
    dla::item_b z = x;
    z -= y;

    REQUIRE(x - y == z);
}

TEST_CASE("Scaling an item from group B should function similarly to multiplication") 
{
    dla::item_b x = 203_b;
    dla::item_b y = 32_b;
    dla::item_b z = x;
    z *= y;

    REQUIRE(x * y == z);
}

TEST_CASE("Factoring an item from group B should function similarly to division") 
{
    dla::item_b x = 4_b;
    dla::item_b y = 200_b;
    dla::item_b z = x;
    z /= y;

    REQUIRE(x / y == z);
}