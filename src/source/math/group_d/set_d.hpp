#pragma once

#include <string>
#include "item_d.hpp"
#include "../set.hpp"


namespace dla
{
    class set_d : public set<item_d, uint32_t> {
    private:
        static const int PAYLOAD_SIZE = 31;
        static const int ITEM_SIZE = 32;
    public:
        set_d (int BLOCK_SIZE);
    };
}