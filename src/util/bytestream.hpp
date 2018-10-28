#pragma once

#include <vector>
#include <cinttypes>

namespace dla
{
    class bytestream
    {
    public:
        virtual uint8_t next() = 0;
    };
}