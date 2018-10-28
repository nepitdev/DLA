#pragma once

#include "set_a.hpp"

namespace dla
{
    set_a::set_a(int BLOCK_SIZE):
        set(BLOCK_SIZE, PAYLOAD_SIZE, ITEM_SIZE) { }
    
    void set_a::setBase64(std::string str)
    {
        data.clear();
        data.shrink_to_fit();

        int count = str.length();
        for (int i = 0; i < count; i++)
        {
            char x = str.at(i);
            if (x >= 97) data.push_back(item_a(x-71));
            else if (x >= 65) data.push_back(item_a(x-65));
            else if (x >= 48) data.push_back(item_a(x+4));
            else if (x == 43) data.push_back(62_a);
            else if (x == 47) data.push_back(63_a);
        }
    }

    std::string set_a::getBase64() const
    {
        static const char lookup[]
        {
            'A','B','C','D','E','F','G','H',
            'I','J','K','L','M','N','O','P',
            'Q','R','S','T','U','V','W','X',
            'Y','Z','a','b','c','d','e','f',
            'g','h','i','j','k','l','m','n',
            'o','p','q','r','s','t','u','v',
            'w','x','y','z','0','1','2','3',
            '4','5','6','7','8','9','+','/',
        };
        std::string str = "";
        int count = data.size();
        for (int i = 0; i < count; i++)
        {
            str += lookup[data[i].getval()];
        }
        return str;
    }
}