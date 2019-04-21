#pragma once

#include <vector>
#include "set_b.hpp"

namespace dla
{
    class set_b3 : public set_b
    {
    private:
        static const int BLOCK_SIZE = 21;
    public:
        set_b3 (): set_b(BLOCK_SIZE) { }
    };
}