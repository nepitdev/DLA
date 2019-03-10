#pragma once

#include <vector>
#include "set_c.hpp"

namespace dla
{
    class set_c1 : public set_c
    {
    private:
        static const int BLOCK_SIZE = 15;
    public:
        set_c1 (): set_c(BLOCK_SIZE) { }
    };
}