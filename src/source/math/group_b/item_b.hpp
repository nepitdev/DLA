#pragma once

#include <cstdint>
#include <vector>
#include "../../util/bytestream.hpp"
#include "../../util/digest.hpp"

namespace dla
{
    class item_b
    {
    private:
        uint8_t val;
        uint16_t mathval() const;
    public:
        item_b ();
        item_b (uint8_t val);
        item_b (bytestream& stream);
        uint8_t getval () const;
        std::vector<uint8_t> getBytes() const;
        bool canBeSalted() const;
        bool isSalted() const;

        static const uint16_t R = 251;
        static const item_b ZERO;
        static const item_b UNIT;
        static const item_b HIGH_ORDER_BIT;
        
        item_b operator+ (item_b const& x) const;
        item_b operator- (item_b const& x) const;
        item_b operator* (item_b const& x) const;
        item_b operator/ (item_b const& x) const;

        item_b operator+= (item_b const& x);
        item_b operator-= (item_b const& x);
        item_b operator*= (item_b const& x);
        item_b operator/= (item_b const& x);

        bool operator== (item_b const& x) const;
        bool operator!= (item_b const& x) const;

        item_b operator- () const;
        item_b operator! () const;
    };
}

dla::item_b operator"" _b (unsigned long long n);