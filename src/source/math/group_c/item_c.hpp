#pragma once

#include <cstdint>
#include <vector>
#include "../../util/bytestream.hpp"
#include "../../util/digest.hpp"

namespace dla
{
    class item_c
    {
    private:
        uint16_t val;
        uint32_t mathval() const;
    public:
        item_c ();
        item_c (uint16_t val);
        item_c (bytestream& stream);
        uint16_t getval () const;
        std::vector<uint8_t> getBytes() const;
        bool canBeSalted() const;
        bool isSalted() const;

        static const uint16_t R = 65521;
        static const item_c ZERO;
        static const item_c UNIT;
        static const item_c HIGH_ORDER_BIT;
        
        item_c operator+ (item_c const& x) const;
        item_c operator- (item_c const& x) const;
        item_c operator* (item_c const& x) const;
        item_c operator/ (item_c const& x) const;

        item_c operator+= (item_c const& x);
        item_c operator-= (item_c const& x);
        item_c operator*= (item_c const& x);
        item_c operator/= (item_c const& x);

        bool operator== (item_c const& x) const;
        bool operator!= (item_c const& x) const;

        item_c operator- () const;
        item_c operator! () const;
    };
}

dla::item_c operator"" _c (unsigned long long n);