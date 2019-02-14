#pragma once

#include "../catch.hpp"

#include "../../source/math/matrix.hpp"
#include "../../source/math/vector.hpp"
#include "../../source/math/group_a/item_a.hpp"
#include "../../source/util/bytestream.hpp"
#include "../../source/util/rand.hpp"

TEST_CASE("A matrix should be constructable with a set number of rows and cols") 
{
    int r = 6;
    int c = 4;
    dla::matrix<int> m(r, c);

    REQUIRE(m.numrows() == r);
    REQUIRE(m.numcols() == c);
}

TEST_CASE("A matrix should be constructable with a byte stream")
{
    class teststream : public dla::bytestream {
        uint8_t x = 0;
        uint8_t next() { x++; return x; }
    };
    teststream s;

    int n = 4;
    uint8_t i = 1;
    dla::matrix<dla::item_a> m(n, n, s);
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            REQUIRE(m.getitm(r,c).getval() == i);
            i++;
        }
    }
}

TEST_CASE("A matrix should be constructable with a set of dla vectors")
{
    std::vector<dla::vector<int>> v {
        dla::vector<int>(2),
        dla::vector<int>(2),
        dla::vector<int>(2),
    };

    dla::matrix<int> m(v);
    REQUIRE(m.numrows() == 2);
    REQUIRE(m.numcols() == 3);
}

TEST_CASE("getrow and getcol should return an apropriate dla vector")
{
    dla::matrix<int> m(2, 2);
    m.setitm(0, 0, 1);
    m.setitm(0, 1, 2);
    m.setitm(1, 0, 3);
    m.setitm(1, 1, 4);
    
    REQUIRE(m.getrow(0)[1] == 2);
    REQUIRE(m.getcol(0)[1] == 3);
}

TEST_CASE("desalt should revurse salt")
{
    dla::rand rng;
    dla::matrix<dla::item_a> m(4, 4, rng);
    dla::matrix<dla::item_a> w(4, 4);
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            if (m.getitm(r, c).getval() > 32)
                m.setitm(r, c, dla::item_a(m.getitm(r, c).getval() - 32));
            w.setitm(r, c, dla::item_a(m.getitm(r, c).getval()));
        }
    }
    w.salt();
    w.desalt();
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            REQUIRE(m.getitm(r, c).getval() == w.getitm(r, c).getval());
        }
    }
}

TEST_CASE("salt should not revurse desalt")
{
    dla::rand rng;
    dla::matrix<dla::item_a> m(4, 4, rng);
    dla::matrix<dla::item_a> w(4, 4);
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            if (m.getitm(r, c).getval() > 32)
                m.setitm(r, c, dla::item_a(m.getitm(r, c).getval() - 32));
            w.setitm(r, c, dla::item_a(m.getitm(r, c).getval()));
        }
    }
    w.desalt();
    w.salt();
    bool allElementsMatch = true;
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            if (m.getitm(r, c).getval() != w.getitm(r, c).getval()) {
                allElementsMatch = false;
                break;
            }
        }
        if (!allElementsMatch) break;
    }
    REQUIRE(!allElementsMatch);
}