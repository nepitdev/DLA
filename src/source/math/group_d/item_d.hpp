#pragma once

#include <cstdint>
#include <vector>
#include "../../util/bytestream.hpp"
#include "../../util/digest.hpp"

namespace dla
{
    class item_d
    {
    private:
        uint32_t val;
        uint64_t mathval() const;
    public:
        item_d ();
        item_d (uint32_t val);
        item_d (bytestream& stream);
        uint32_t getval () const;
        std::vector<uint8_t> getBytes() const;
        bool canBeSalted() const;
        bool isSalted() const;

        static const uint64_t R = 4294967291;
        static const item_d ZERO;
        static const item_d UNIT;
        static const item_d HIGH_ORDER_BIT;
        
        item_d operator+ (item_d const& x) const;
        item_d operator- (item_d const& x) const;
        item_d operator* (item_d const& x) const;
        item_d operator/ (item_d const& x) const;

        item_d operator+= (item_d const& x);
        item_d operator-= (item_d const& x);
        item_d operator*= (item_d const& x);
        item_d operator/= (item_d const& x);

        bool operator== (item_d const& x) const;
        bool operator!= (item_d const& x) const;

        item_d operator- () const;
        item_d operator! () const;
    };
}

dla::item_d operator"" _d (unsigned long long n);