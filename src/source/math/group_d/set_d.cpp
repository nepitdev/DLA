#include "set_d.hpp"

namespace dla
{
    set_d::set_d(int BLOCK_SIZE):
        set(BLOCK_SIZE, PAYLOAD_SIZE, ITEM_SIZE) { }
}