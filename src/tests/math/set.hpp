#pragma once

#include "../catch.hpp"

#include <cstdint>
#include <vector>
#include "../../source/math/set.hpp"
#include "../../source/math/group_a/item_a.hpp"
#include "../../source/math/group_a/set_a1.hpp"

TEST_CASE("A set should be able to hold arbitrary payloads") 
{
    class testset : public dla::set<uint8_t, uint8_t> 
    {
    public:
        testset(): set(8, 8, 8) { }
    };

    REQUIRE_NOTHROW([&](){
        testset t;
    }());
}

TEST_CASE("A set should be able to be filled with raw data") 
{
    dla::set_a1 s;
    std::vector<uint8_t> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    s.setRawData(v);
    std::vector<uint8_t> w = s.getRawData();
    REQUIRE(v.size() == w.size());
    for (int i = 0; i < v.size(); i++) {
        REQUIRE(v[i] == w[i]);
    }
}

TEST_CASE("Convernting to formated data should not alter the raw data of a set") 
{
    dla::set_a1 s;
    std::vector<uint8_t> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    s.setRawData(v);

    s.setFormatedData(s.getFormatedData());
    std::vector<uint8_t> w = s.getRawData();

    REQUIRE(v.size() == w.size());
    for (int i = 0; i < v.size(); i++) {
        REQUIRE(v[i] == w[i]);
    }
}

TEST_CASE("Convernting to a matrix should not alter the raw data of a set") 
{
    dla::set_a1 s;
    std::vector<uint8_t> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    s.setRawData(v);
    s.setMatrix(s.getMatrix());
    std::vector<uint8_t> w = s.getRawData();

    REQUIRE(v.size() == w.size());
    for (int i = 0; i < v.size(); i++) {
        REQUIRE(v[i] == w[i]);
    }
}

TEST_CASE("Specifice items should be addressable") 
{
    dla::set_a1 s;
    std::vector<uint8_t> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    s.setRawData(v);
    for (int i = 0; i < 8; i++) {
        REQUIRE(s[i] * 0_a == 0_a);
    }
}

TEST_CASE("The size of a set should be a correct") 
{
    dla::set_a1 s;
    std::vector<uint8_t> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    s.setRawData(v);
    REQUIRE(s.size() == 8);
    v.push_back(5);
    s.setRawData(v);
    REQUIRE(s.size() == 16);
}
