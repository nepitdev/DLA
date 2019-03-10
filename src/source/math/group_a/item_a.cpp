#include "item_a.hpp"

#include "inverse_table_a.hpp"

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
        val = R;
        while (val == R)
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
        std::vector<uint8_t> vec = {val};
        return vec;
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
        return item_a(inverse_table_a::L[this->val]);
    }
}

dla::item_a operator"" _a (unsigned long long n)
{
    return dla::item_a(n);
}