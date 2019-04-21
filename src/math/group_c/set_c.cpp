#include "set_c.hpp"

namespace dla
{
    set_c::set_c(int BLOCK_SIZE):
        set(BLOCK_SIZE, PAYLOAD_SIZE, ITEM_SIZE) { }
}