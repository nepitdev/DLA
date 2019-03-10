#include "item_b.hpp"

#include "inverse_table_b.hpp"

namespace dla
{
    uint16_t item_b::mathval() const
    {
        return val;
    }

    item_b::item_b():
        val(0) { }

    item_b::item_b(uint8_t val):
        val(val) { }

    item_b::item_b (bytestream& stream)
    {
        uint8_t mask = 255;
        val = R;
        while (val == R)
        {
            uint8_t temp = stream.next();
            temp = temp & mask;
            if (temp < R) val = temp % R;
        }
    }

    uint8_t item_b::getval() const
    {
        return val;
    }

    std::vector<uint8_t> item_b::getBytes() const
    {
        return std::vector<uint8_t>(val);
    }

    bool item_b::canBeSalted() const
    {
        return ((int) val < (int) (R - HIGH_ORDER_BIT.val));
    }

    bool item_b::isSalted() const
    {
        return ((int) val >= (int) (HIGH_ORDER_BIT.val));
    }

    const item_b item_b::ZERO = 0_b;
    const item_b item_b::UNIT = 1_b;
    const item_b item_b::HIGH_ORDER_BIT = 128;

    item_b item_b::operator+(item_b const& x) const
    {
        return item_b((mathval() + x.mathval()) % R);
    }

    item_b item_b::operator-(item_b const& x) const
    {
        return (*this) + (-x);
    }

    item_b item_b::operator*(item_b const& x) const
    {
        return item_b((mathval() * x.mathval()) % R);
    }

    item_b item_b::operator/(item_b const& x) const
    {
        return (*this) * (!x);
    }

    item_b item_b::operator+=(item_b const& x)
    {
        val = (item_b(val) + x).getval();
        return *this;
    }

    item_b item_b::operator-=(item_b const& x)
    {
        val = (item_b(val) - x).getval();
        return *this;
    }

    item_b item_b::operator*=(item_b const& x)
    {
        val = (item_b(val) * x).getval();
        return *this;
    }

    item_b item_b::operator/=(item_b const& x)
    {
        val = (item_b(val) / x).getval();
        return *this;
    }

    bool item_b::operator==(item_b const& x) const
    {
        return this->getval() == x.getval();
    }

    bool item_b::operator!=(item_b const& x) const
    {
        return this->getval() != x.getval();
    }

    item_b item_b::operator-() const
    {
        return item_b(R - this->val);
    }

    item_b item_b::operator!() const
    {
        return item_b(inverse_table_b::L[this->val]);
    }
}

dla::item_b operator"" _b (unsigned long long n)
{
    return dla::item_b(n);
}