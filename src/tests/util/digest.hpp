#pragma once

#include "../catch.hpp"

#include <cinttypes>
#include <sstream>
#include <vector>
#include "../../source/util/digest.hpp"

TEST_CASE("Digest should calculate SHA-256") 
{
    std::string text = "Hello World!";
    std::string hash = "7f83b1657ff1fc53b92dc18148a1d65dfc2d4b1fa3d677284addd200126d9069";

    std::vector<uint8_t> data(text.length());
    for (int i = 0; i < text.length(); i++)
    {
        data[i] = text.at(i);
    }
    std::vector<uint8_t> dig = dla::digest(data).execute();

    char hex[] = {
        '0','1','2','3',
        '4','5','6','7',
        '8','9','a','b',
        'c','d','e','f'
    };
    std::string result = "";
    int l = dig.size();
    for (int i = 0; i < l; i++)
    {
        result += hex[dig[i] >> 4];
        result += hex[dig[i] & 15];
    }

    REQUIRE(hash == result);
}