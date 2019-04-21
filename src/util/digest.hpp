#pragma once

#include <cinttypes>
#include <openssl/sha.h>
#include <vector>
#include "bytestream.hpp"

namespace dla
{
    class digest : public bytestream
    {
    private:
        std::vector<uint8_t> data;
        std::vector<uint8_t> buffer;
    public:
        digest(std::vector<uint8_t> data);
        std::vector<uint8_t> execute();
        uint8_t next();
        ~digest();
    };
}