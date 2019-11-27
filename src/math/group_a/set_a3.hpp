#pragma once

#include <vector>
#include "set_a.hpp"

namespace dla
{
    class set_a3 : public set_a
    {
    private:
        static const int BLOCK_SIZE = 15;
    public:
        set_a3 (): set_a(BLOCK_SIZE) { }
    };
}