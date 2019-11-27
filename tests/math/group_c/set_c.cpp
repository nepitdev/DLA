#include "../../catch.hpp"

#include "../../../src/math/group_c/set_c.hpp"
#include "../../../src/math/group_c/set_c1.hpp"

TEST_CASE("A group C set should be able to be filled with raw data") 
{
    dla::set_c1 s;
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

TEST_CASE("Convernting to a matrix should not alter the raw data of a group C set") 
{
    dla::set_c1 s;
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

TEST_CASE("Formating should not alter the raw data of a group C set") 
{
    dla::set_c1 s;
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

TEST_CASE("The size of a group C set should be a correct") 
{
    dla::set_c1 s;
    std::vector<uint8_t> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);
    v.push_back(10);
    v.push_back(11);
    v.push_back(12);
    v.push_back(13);
    v.push_back(14);
    s.setRawData(v);
    REQUIRE(s.size() == 8);
    v.push_back(15);
    s.setRawData(v);
    REQUIRE(s.size() == 16);
}