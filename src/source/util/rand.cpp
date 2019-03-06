#include "rand.hpp"

namespace dla
{
    rand::rand()
    {
        std::random_device rd;
        source = std::mt19937(rd());
        range = std::uniform_int_distribution<uint8_t>(0, 255);
    }

    uint8_t rand::next()
    {
        return range(source);
    }

    uint8_t rand::next(uint8_t lower, uint8_t upper)
    {
        std::uniform_int_distribution<uint8_t> srange(lower, upper);
        return srange(source);
    }
}