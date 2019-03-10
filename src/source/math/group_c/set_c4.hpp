#pragma once

#include <vector>
#include "set_c.hpp"

namespace dla
{
    class set_c4 : public set_c
    {
    private:
        static const int BLOCK_SIZE = 60;
    public:
        set_c4 (): set_c(BLOCK_SIZE) { }
    };
}