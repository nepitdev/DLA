#include "../../catch.hpp"

#include "../../../source/math/group_a/set_a1.hpp"

TEST_CASE("A set of Group A should buildable using base64") 
{
    dla::set_a1 s;
    std::string b64 = "0123456789abcde";
    s.setBase64(b64);
    REQUIRE(b64 == s.getBase64());
}

TEST_CASE("A group A set should be able to be filled with raw data") 
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

TEST_CASE("Convernting to a matrix should not alter the raw data of a group A set") 
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

TEST_CASE("Formating should not alter the raw data of a group A set") 
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

TEST_CASE("The size of a group A set should be a correct") 
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