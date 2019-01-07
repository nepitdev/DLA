#pragma once

#include <vector>
#include "set_b.hpp"

namespace dla
{
    class set_b1 : public set_b
    {
    private:
        static const int BLOCK_SIZE = 7;
    public:
        set_b1 (): set_b(BLOCK_SIZE) { }
    };
}