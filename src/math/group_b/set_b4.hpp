#pragma once

#include <vector>
#include "set_b.hpp"

namespace dla
{
    class set_b4 : public set_b
    {
    private:
        static const int BLOCK_SIZE = 28;
    public:
        set_b4 (): set_b(BLOCK_SIZE) { }
    };
}