#pragma once

#include "../catch.hpp"

#include <cstdint>
#include <vector>
#include "../../source/math/matrix.hpp"
#include "../../source/math/vector.hpp"
#include "../../source/math/group_a/item_a.hpp"
#include "../../source/util/bytestream.hpp"
#include "../../source/util/rand.hpp"

TEST_CASE("A matrix should be constructable with a set number of rows and cols") 
{
    int r = 6;
    int c = 4;
    dla::matrix<dla::item_a> m(r, c);

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
    std::vector<dla::vector<dla::item_a>> v {
        dla::vector<dla::item_a>(2),
        dla::vector<dla::item_a>(2),
        dla::vector<dla::item_a>(2),
    };

    dla::matrix<dla::item_a> m(v);
    REQUIRE(m.numrows() == 2);
    REQUIRE(m.numcols() == 3);
}

TEST_CASE("getrow and getcol should return an apropriate dla vector")
{
    dla::matrix<dla::item_a> m(2, 2);
    m.setitm(0, 0, 1_a);
    m.setitm(0, 1, 2_a);
    m.setitm(1, 0, 3_a);
    m.setitm(1, 1, 4_a);
    
    REQUIRE(m.getrow(0)[1] == 2_a);
    REQUIRE(m.getcol(0)[1] == 3_a);
}

TEST_CASE("getitm, getrow, and getcol should throw an exception for indecies that are out of bounds")
{
    dla::matrix<dla::item_a> m(2, 2);
    m.setitm(0, 0, 1_a);
    m.setitm(0, 1, 2_a);
    m.setitm(1, 0, 3_a);
    m.setitm(1, 1, 4_a);
    
    REQUIRE_THROWS(m.getitm(2,1));
    REQUIRE_THROWS(m.getitm(1,2));
    REQUIRE_THROWS(m.getitm(-1,1));
    REQUIRE_THROWS(m.getitm(1,-1));
    REQUIRE_THROWS(m.getrow(-1));
    REQUIRE_THROWS(m.getrow(2));
    REQUIRE_THROWS(m.getcol(-1));
    REQUIRE_THROWS(m.getcol(2));
}

TEST_CASE("setitm should throw an exception for indecies that are out of bounds")
{
    dla::matrix<dla::item_a> m(2, 2);
    m.setitm(0, 0, 1_a);
    m.setitm(0, 1, 2_a);
    m.setitm(1, 0, 3_a);
    m.setitm(1, 1, 4_a);
    
    REQUIRE_THROWS(m.setitm(2,1, 0_a));
    REQUIRE_THROWS(m.setitm(1,2, 0_a));
    REQUIRE_THROWS(m.setitm(-1,1, 0_a));
    REQUIRE_THROWS(m.setitm(1,-1, 0_a));
}

TEST_CASE("desalt should revurse salt")
{
    dla::matrix<dla::item_a> m(4, 4);
    dla::matrix<dla::item_a> w(4, 4);
    uint8_t data[16] = 
    { 7, 12, 28, 15, 7, 21, 6, 19, 10, 3, 16, 1, 9, 23, 25, 4 };
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            m.setitm(r, c, dla::item_a(data[4*c+r]));
            w.setitm(r, c, dla::item_a(data[4*c+r]));
        }
    }
    w.salt();
    w.desalt();
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            REQUIRE(+m.getitm(r, c).getval() == +w.getitm(r, c).getval());
        }
    }
}

TEST_CASE("salt should not revurse desalt")
{
    dla::matrix<dla::item_a> m(4, 4);
    dla::matrix<dla::item_a> w(4, 4);
    uint8_t data[16] = 
    { 7, 12, 28, 15, 7, 21, 6, 19, 10, 3, 16, 1, 9, 23, 25, 4 };
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            m.setitm(r, c, dla::item_a(data[4*c+r]));
            w.setitm(r, c, dla::item_a(data[4*c+r]));
        }
    }
    w.desalt();
    w.salt();
    bool allElementsMatch = true;
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            if (+m.getitm(r, c).getval() != +w.getitm(r, c).getval()) {
                allElementsMatch = false;
                break;
            }
        }
        if (!allElementsMatch) break;
    }
    REQUIRE(!allElementsMatch);
}

TEST_CASE("Matrix multiplication and division should be inverses")
{
    dla::matrix<dla::item_a> m(4, 4);
    dla::matrix<dla::item_a> w(4, 4);
    uint8_t data1[16] = 
    { 7, 12, 28, 15, 7, 21, 6, 19, 10, 3, 16, 1, 9, 23, 25, 4 };
    uint8_t data2[16] = 
    { 14, 31, 12, 2, 0, 3, 31, 10, 26, 7, 24, 26, 13, 5, 9, 20 };
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            m.setitm(r, c, dla::item_a(data1[4*c+r]));
            w.setitm(r, c, dla::item_a(data2[4*c+r]));
        }
    }

    dla::matrix<dla::item_a> a(0, 0), b(0, 0);
    a = m * w;
    a = a / w;

    b = m / w;
    b = b * w;

    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            REQUIRE(+m.getitm(r, c).getval() == +a.getitm(r, c).getval());
            REQUIRE(+m.getitm(r, c).getval() == +b.getitm(r, c).getval());
        }
    }
}

TEST_CASE("Matrix definition should create the correct matrix")
{
    dla::matrix<dla::item_a> m(4, 4);
    dla::matrix<dla::item_a> k(4, 4);
    uint8_t data1[16] = 
    { 7, 12, 28, 15, 7, 21, 6, 19, 10, 3, 16, 1, 9, 23, 25, 4 };
    uint8_t data2[16] = 
    { 14, 31, 12, 2, 0, 3, 31, 10, 26, 7, 24, 26, 13, 5, 9, 20 };
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            m.setitm(r, c, dla::item_a(data1[4*c+r]));
            k.setitm(r, c, dla::item_a(data2[4*c+r]));
        }
    }

    auto w = m * k;
    auto z = m % w;

    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            REQUIRE(+z.getitm(r, c).getval() == +k.getitm(r, c).getval());
        }
    }
}

TEST_CASE("Transpose of a transpose of a matrix should be the original matrix")
{
    dla::matrix<dla::item_a> m(4, 4);
    uint8_t data1[16] = 
    { 7, 12, 28, 15, 7, 21, 6, 19, 10, 3, 16, 1, 9, 23, 25, 4 };
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            m.setitm(r, c, dla::item_a(data1[4*c+r]));
        }
    }

    auto w = ~(~m);

    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            REQUIRE(+m.getitm(r, c).getval() == +w.getitm(r, c).getval());
        }
    }
}

TEST_CASE("Invurse of the invurse of a matrix should be the original matrix")
{
    dla::matrix<dla::item_a> m(4, 4);
    uint8_t data1[16] = 
    { 7, 12, 28, 15, 7, 21, 6, 19, 10, 3, 16, 1, 9, 23, 25, 4 };
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            m.setitm(r, c, dla::item_a(data1[4*c+r]));
        }
    }

    auto w = !(!m);

    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            REQUIRE(+m.getitm(r, c).getval() == +w.getitm(r, c).getval());
        }
    }
}

TEST_CASE("Multiplying by the invurse should be the same as division")
{
    dla::matrix<dla::item_a> m(4, 4);
    dla::matrix<dla::item_a> w(4, 4);
    uint8_t data1[16] = 
    { 7, 12, 28, 15, 7, 21, 6, 19, 10, 3, 16, 1, 9, 23, 25, 4 };
    uint8_t data2[16] = 
    { 14, 31, 12, 2, 0, 3, 31, 10, 26, 7, 24, 26, 13, 5, 9, 20 };
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            m.setitm(r, c, dla::item_a(data1[4*c+r]));
            w.setitm(r, c, dla::item_a(data2[4*c+r]));
        }
    }

    auto z = m / w;
    auto s = m * (!w);

    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            REQUIRE(+z.getitm(r, c).getval() == +s.getitm(r, c).getval());
        }
    }
}
