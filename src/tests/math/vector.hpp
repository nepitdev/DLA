#pragma once

#include "../catch.hpp"

#include <cstdint>
#include <iostream>
#include "../../source/math/vector.hpp"
#include "../../source/math/group_a/item_a.hpp"
#include "../../source/util/digest.hpp"

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

TEST_CASE("The digests of identical vectors should be the same") 
{
    std::vector<dla::item_a> a = { 0_a, 1_a, 2_a, 3_a, 4_a };
    std::vector<dla::item_a> b = { 0_a, 1_a, 2_a, 3_a, 4_a };
    dla::vector<dla::item_a> v(a);
    dla::vector<dla::item_a> w(b);

    dla::digest x = v.getDigest();
    dla::digest y = w.getDigest();

    for (int i = 0; i < 16; i++) {
        REQUIRE(x.next() == y.next());
    }
}

TEST_CASE("Accessing an index greater than or equal to the sive of a vector should throw an exception") 
{
    std::vector<dla::item_a> a = { 0_a, 1_a, 2_a, 3_a, 4_a };
    dla::vector<dla::item_a> v(a);

    REQUIRE_THROWS(v[5]);
}

TEST_CASE("Adding vectors should be commutative")
{
    std::vector<dla::item_a> a = { 0_a, 1_a, 2_a, 3_a, 4_a };
    std::vector<dla::item_a> b = { 4_a, 3_a, 2_a, 1_a, 0_a };
    dla::vector<dla::item_a> v(a);
    dla::vector<dla::item_a> w(b);
    dla::vector<dla::item_a> x = v + w;
    dla::vector<dla::item_a> y = w + v;

    for (int i = 0; i < 5; i++) {
        REQUIRE(x[i].getval() == y[i].getval());
    }
}

TEST_CASE("Adding vectors should be associative")
{
    std::vector<dla::item_a> a = { 0_a, 1_a, 2_a, 3_a, 4_a };
    std::vector<dla::item_a> b = { 4_a, 3_a, 2_a, 1_a, 0_a };
    std::vector<dla::item_a> c = { 1, 1, 1, 1, 1 };
    dla::vector<dla::item_a> v(a);
    dla::vector<dla::item_a> u(b);
    dla::vector<dla::item_a> w(c);
    dla::vector<dla::item_a> x = (v + u) + w;
    dla::vector<dla::item_a> y = v + (u + w);

    for (int i = 0; i < 5; i++) {
        REQUIRE(x[i].getval() == y[i].getval());
    }
}

TEST_CASE("Subtracting vectors should be the same as adding a negative vector")
{
    std::vector<dla::item_a> a = { 4_a, 4_a, 4_a, 4_a, 4_a };
    std::vector<dla::item_a> b = { 4_a, 3_a, 2_a, 1_a, 0_a };
    dla::vector<dla::item_a> v(a);
    dla::vector<dla::item_a> w(b);
    dla::vector<dla::item_a> x = v + (-w);
    dla::vector<dla::item_a> y = v - w;

    for (int i = 0; i < 5; i++) {
        REQUIRE(x[i].getval() == y[i].getval());
    }
}

TEST_CASE("Multiplying vectors should give a single value")
{
    std::vector<dla::item_a> a = { 0_a, 1_a, 2_a, 3_a, 4_a };
    std::vector<dla::item_a> b = { 4_a, 3_a, 2_a, 1_a, 0_a };
    dla::vector<dla::item_a> v(a);
    dla::vector<dla::item_a> w(b);
    dla::item_a x = v * w;
    dla::item_a y = w * v;

    REQUIRE(x.getval() == y.getval());
}

TEST_CASE("Scaling a vector should be commutative")
{
    std::vector<dla::item_a> a = { 0_a, 1_a, 2_a, 3_a, 4_a };
    dla::vector<dla::item_a> v(a);
    dla::item_a k = 2_a;
    dla::vector<dla::item_a> x = k * v;
    dla::vector<dla::item_a> y = v * k;

    for (int i = 0; i < 5; i++) {
        REQUIRE(x[i].getval() == 2 * a[i].getval());
        REQUIRE(y[i].getval() == 2 * a[i].getval());
    }
}