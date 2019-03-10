#pragma once

#include <vector>
#include "set_c.hpp"

namespace dla
{
    class set_c3 : public set_c
    {
    private:
        static const int BLOCK_SIZE = 45;
    public:
        set_c3 (): set_c(BLOCK_SIZE) { }
    };
}