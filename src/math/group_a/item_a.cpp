#pragma once

#include "item_a.hpp"

namespace dla
{
    uint16_t item_a::mathval() const
    {
        return val;
    }

    item_a::item_a():
        val(0) { }

    item_a::item_a(uint8_t val):
        val(val) { }

    item_a::item_a (bytestream& stream)
    {
        uint8_t mask = 63;
        val = 61;
        while (val == 61)
        {
            uint8_t temp = stream.next();
            temp = temp & mask;
            if (temp < R) val = temp % R;
        }
    }

    uint8_t item_a::getval() const
    {
        return val;
    }

    std::vector<uint8_t> item_a::getBytes() const
    {
        return std::vector<uint8_t>(val);
    }

    bool item_a::canBeSalted() const
    {
        return ((int) val < (int) (R - HIGH_ORDER_BIT.val));
    }

    bool item_a::isSalted() const
    {
        return ((int) val >= (int) (HIGH_ORDER_BIT.val));
    }

    const item_a item_a::ZERO = 0_a;
    const item_a item_a::UNIT = 1_a;
    const item_a item_a::HIGH_ORDER_BIT = 32;

    item_a item_a::operator+(item_a const& x) const
    {
        return item_a((mathval() + x.mathval()) % R);
    }

    item_a item_a::operator-(item_a const& x) const
    {
        return (*this) + (-x);
    }

    item_a item_a::operator*(item_a const& x) const
    {
        return item_a((mathval() * x.mathval()) % R);
    }

    item_a item_a::operator/(item_a const& x) const
    {
        return (*this) * (!x);
    }

    item_a item_a::operator+=(item_a const& x)
    {
        val = (item_a(val) + x).getval();
        return *this;
    }

    item_a item_a::operator-=(item_a const& x)
    {
        val = (item_a(val) - x).getval();
        return *this;
    }

    item_a item_a::operator*=(item_a const& x)
    {
        val = (item_a(val) * x).getval();
        return *this;
    }

    item_a item_a::operator/=(item_a const& x)
    {
        val = (item_a(val) / x).getval();
        return *this;
    }

    bool item_a::operator==(item_a const& x) const
    {
        return this->getval() == x.getval();
    }

    bool item_a::operator!=(item_a const& x) const
    {
        return this->getval() != x.getval();
    }

    item_a item_a::operator-() const
    {
        return item_a(R - this->val);
    }

    item_a item_a::operator!() const
    {
        static const uint8_t lookup[] =
        {
            0x00, 0x01, 0x1F, 0x29, 0x2E, 0x31, 0x33, 0x23,
            0x17, 0x22, 0x37, 0x32, 0x38, 0x2F, 0x30, 0x39,
            0x2A, 0x12, 0x11, 0x2D, 0x3A, 0x20, 0x19, 0x08,
            0x1C, 0x16, 0x36, 0x34, 0x18, 0x28, 0x3B, 0x02,
            0x15, 0x25, 0x09, 0x07, 0x27, 0x21, 0x35, 0x24,
            0x1D, 0x03, 0x10, 0x2C, 0x2B, 0x13, 0x04, 0x0D,
            0x0E, 0x05, 0x0B, 0x06, 0x1B, 0x26, 0x1A, 0x0A,
            0x0C, 0x0F, 0x14, 0x1E, 0x3C
        };
        return item_a(lookup[this->val]);
    }
}

dla::item_a operator"" _a (unsigned long long n)
{
    return dla::item_a(n);
}