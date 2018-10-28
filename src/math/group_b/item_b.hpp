#pragma once

#include <cstdint>

namespace dla
{
    class item_b
    {
    private:
        static const uint16_t R = 251;
        uint8_t val;
        uint16_t mathval() const;
    public:
        item_b ();
        item_b (uint8_t val);
        uint8_t getval () const;

        static const item_b ZERO;
        static const item_b UNIT;
        
        item_b operator+ (item_b const& x) const;
        item_b operator- (item_b const& x) const;
        item_b operator* (item_b const& x) const;
        item_b operator/ (item_b const& x) const;

        bool operator== (item_b const& x) const;
        bool operator!= (item_b const& x) const;

        item_b operator- () const;
        item_b operator! () const;
    };
}

dla::item_b operator"" _b (unsigned long long n);