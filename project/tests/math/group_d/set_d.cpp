#include "../../catch.hpp"

#include "../../../src/math/group_d/set_d.hpp"
#include "../../../src/math/group_d/set_d1.hpp"

TEST_CASE("A group D set should be able to be filled with raw data") 
{
    dla::set_d1 s;
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

TEST_CASE("Convernting to a matrix should not alter the raw data of a group D set") 
{
    dla::set_d1 s;
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

TEST_CASE("Formating should not alter the raw data of a group D set") 
{
    dla::set_d1 s;
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

TEST_CASE("The size of a group D set should be a correct") 
{
    dla::set_d1 s;
    std::vector<uint8_t> v;
    for (int i = 1; i <= 30; i++)
        v.push_back(i);
    s.setRawData(v);
    REQUIRE(s.size() == 8);
    v.push_back(15);
    s.setRawData(v);
    REQUIRE(s.size() == 16);
}