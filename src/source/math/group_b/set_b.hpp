#pragma once

#include <string>
#include "item_b.hpp"
#include "../set.hpp"


namespace dla
{
    class set_b : public set<item_b, uint16_t> {
    private:
        static const int PAYLOAD_SIZE = 7;
        static const int ITEM_SIZE = 8;
    public:
        set_b (int BLOCK_SIZE);
    };
}