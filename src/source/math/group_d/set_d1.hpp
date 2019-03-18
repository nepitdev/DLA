#pragma once

#include <vector>
#include "set_d.hpp"

namespace dla
{
    class set_d1 : public set_d
    {
    private:
        static const int BLOCK_SIZE = 31;
    public:
        set_d1 (): set_d(BLOCK_SIZE) { }
    };
}