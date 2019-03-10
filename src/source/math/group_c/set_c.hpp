#pragma once

#include <string>
#include "item_c.hpp"
#include "../set.hpp"


namespace dla
{
    class set_c : public set<item_c, uint32_t> {
    private:
        static const int PAYLOAD_SIZE = 15;
        static const int ITEM_SIZE = 16;
    public:
        set_c (int BLOCK_SIZE);
    };
}