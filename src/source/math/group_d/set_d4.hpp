#pragma once

#include <vector>
#include "set_d.hpp"

namespace dla
{
    class set_d4 : public set_d
    {
    private:
        static const int BLOCK_SIZE = 124;
    public:
        set_d4 (): set_d(BLOCK_SIZE) { }
    };
}