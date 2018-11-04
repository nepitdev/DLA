#pragma once

#include <vector>
#include "set_a.hpp"

namespace dla
{
    class set_a2 : public set_a
    {
    private:
        static const int BLOCK_SIZE = 10;
    public:
        set_a2 (): set_a(BLOCK_SIZE) { }
    };
}