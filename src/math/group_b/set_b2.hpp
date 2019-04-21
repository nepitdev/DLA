#pragma once

#include <vector>
#include "set_b.hpp"

namespace dla
{
    class set_b2 : public set_b
    {
    private:
        static const int BLOCK_SIZE = 14;
    public:
        set_b2 (): set_b(BLOCK_SIZE) { }
    };
}