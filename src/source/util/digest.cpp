#pragma once

#include "digest.hpp"
#include <iostream>

namespace dla
{
    digest::digest(std::vector<uint8_t> data):
        data(data) { }
    
    std::vector<uint8_t> digest::execute()
    {
        uint8_t digest[SHA256_DIGEST_LENGTH];
        for (int i = 0; i < data.size(); i++)
        {
            std::cout << (int) data[i] << std::endl;
        }
        SHA256(&data[0], data.size(), (uint8_t*) &digest);    
        data = std::vector<uint8_t>(std::begin(digest), std::end(digest));
        return data;
    }

    uint8_t digest::next()
    {
        if (buffer.empty()) buffer = execute();
        uint8_t val = buffer[0];
        buffer.erase(buffer.begin());
        return val;
    }

    digest::~digest() { }
}