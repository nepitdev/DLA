#pragma once

#include <string>
#include "item_a.hpp"
#include "../set.hpp"


namespace dla
{
    class set_a : public set<item_a, uint16_t> {
    private:
        static const int PAYLOAD_SIZE = 5;
        static const int ITEM_SIZE = 6;
    public:
        set_a (int BLOCK_SIZE);
        void setBase64(std::string);
        std::string getBase64() const;
    };
}