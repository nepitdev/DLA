#pragma once

#include <vector>
#include "set_c.hpp"

namespace dla
{
    class set_c2 : public set_c
    {
    private:
        static const int BLOCK_SIZE = 30;
    public:
        set_c2 (): set_c(BLOCK_SIZE) { }
    };
}