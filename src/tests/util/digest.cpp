#include "../catch.hpp"

#include <cinttypes>
#include <sstream>
#include <vector>
#include "../../source/util/digest.hpp"

TEST_CASE("Digest should calculate SHA-256") 
{
    std::string text = "Hello World!";
    //SHA-256("Hello World!")
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

TEST_CASE("Digest should function as a bytestream") 
{
    std::string text = "Hello World!";
    //SHA-256("Hello World!") + SHA-256(SHA-256("Hello World!"))
    std::string hash = "7f83b1657ff1fc53b92dc18148a1d65dfc2d4b1fa3d677284addd200126d906961f417374f4400b47dcae1a8f402d4f4dacf455a0442a06aa455a447b0d4e170";

    std::vector<uint8_t> data(text.length());
    for (int i = 0; i < text.length(); i++)
    {
        data[i] = text.at(i);
    }
    dla::digest d(data);

    char hex[] = {
        '0','1','2','3',
        '4','5','6','7',
        '8','9','a','b',
        'c','d','e','f'
    };
    std::string result = "";
    int l = hash.length();
    while ( result.length() < l)
    {
        uint8_t val = d.next();
        result += hex[val >> 4];
        result += hex[val & 15];
        REQUIRE(result.find(result) == 0);
    }

    REQUIRE(hash == result);
}

TEST_CASE("Digest should be able to take the SHA-256 of a SHA-256") 
{
    std::string text = "Hello World!";
    //SHA-256(SHA-256("Hello World!"))
    std::string hash = "61f417374f4400b47dcae1a8f402d4f4dacf455a0442a06aa455a447b0d4e170";

    std::vector<uint8_t> data(text.length());
    for (int i = 0; i < text.length(); i++)
    {
        data[i] = text.at(i);
    }
    dla::digest d(data);
    d.execute();
    std::vector<uint8_t> dig = d.execute();

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