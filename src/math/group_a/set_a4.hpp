#pragma once

#include <vector>
#include "set_a.hpp"

namespace dla
{
    class set_a4 : public set_a
    {
    private:
        static const int BLOCK_SIZE = 20;
    public:
        set_a4 (): set_a(BLOCK_SIZE) { }
    };
}