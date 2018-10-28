#pragma once

#include <vector>
#include "set_a.hpp"

namespace dla
{
    class set_a1 : public set_a
    {
    private:
        static const int BLOCK_SIZE = 5;
    public:
        set_a1 (): set_a(BLOCK_SIZE) { }
    };
}