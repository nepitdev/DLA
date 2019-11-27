#pragma once

#include <vector>
#include "set_d.hpp"

namespace dla
{
    class set_d3 : public set_d
    {
    private:
        static const int BLOCK_SIZE = 93;
    public:
        set_d3 (): set_d(BLOCK_SIZE) { }
    };
}