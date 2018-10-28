#pragma once

#include <cstdint>
#include <vector>
#include "../../util/bytestream.hpp"
#include "../../util/digest.hpp"

namespace dla
{
    class item_a
    {
    private:
        static const uint16_t R = 61;
        uint8_t val;
        uint16_t mathval() const;
    public:
        item_a ();
        item_a (uint8_t val);
        item_a (bytestream& stream);
        uint8_t getval () const;
        std::vector<uint8_t> getBytes() const;
        bool canBeSalted() const;
        bool isSalted() const;

        static const item_a ZERO;
        static const item_a UNIT;
        static const item_a HIGH_ORDER_BIT;
        
        item_a operator+ (item_a const& x) const;
        item_a operator- (item_a const& x) const;
        item_a operator* (item_a const& x) const;
        item_a operator/ (item_a const& x) const;

        item_a operator+= (item_a const& x);
        item_a operator-= (item_a const& x);
        item_a operator*= (item_a const& x);
        item_a operator/= (item_a const& x);

        bool operator== (item_a const& x) const;
        bool operator!= (item_a const& x) const;

        item_a operator- () const;
        item_a operator! () const;
    };
}

dla::item_a operator"" _a (unsigned long long n);