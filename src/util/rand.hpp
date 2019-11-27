#pragma once

#include <openssl/sha.h>
#include <random>
#include "bytestream.hpp"

namespace dla
{
    class rand : public bytestream
    {
    private:
        std::mt19937 source;
        std::uniform_int_distribution<uint8_t> range;
    public:
        rand();
        uint8_t next();
        uint8_t next(uint8_t lower, uint8_t upper);
    };
}