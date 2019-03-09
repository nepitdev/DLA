#include "item_c.hpp"

#include "invurse_table_c.hpp"

namespace dla
{
    uint32_t item_c::mathval() const
    {
        return val;
    }

    item_c::item_c():
        val(0) { }

    item_c::item_c(uint16_t val):
        val(val) { }

    item_c::item_c (bytestream& stream)
    {
        uint16_t mask = 65535;
        val = R;
        while (val == R)
        {
            uint16_t temp = 0;
            for (int i = 1; i >= 0; i--)
                temp += stream.next() << (8 * i);
            temp = temp & mask;
            if (temp < R) val = temp % R;
        }
    }

    uint16_t item_c::getval() const
    {
        return val;
    }

    std::vector<uint8_t> item_c::getBytes() const
    {
        uint16_t mask = 255;
        std::vector<uint8_t> bytes;
        for (int i = 1; i >= 0; i--)
            bytes.push_back(val & (mask << (8*i)));
        return bytes;
    }

    bool item_c::canBeSalted() const
    {
        return ((int) val < (int) (R - HIGH_ORDER_BIT.val));
    }

    bool item_c::isSalted() const
    {
        return ((int) val >= (int) (HIGH_ORDER_BIT.val));
    }

    const item_c item_c::ZERO = 0_c;
    const item_c item_c::UNIT = 1_c;
    const item_c item_c::HIGH_ORDER_BIT = 32768_c;

    item_c item_c::operator+(item_c const& x) const
    {
        return item_c((mathval() + x.mathval()) % R);
    }

    item_c item_c::operator-(item_c const& x) const
    {
        return (*this) + (-x);
    }

    item_c item_c::operator*(item_c const& x) const
    {
        return item_c((mathval() * x.mathval()) % R);
    }

    item_c item_c::operator/(item_c const& x) const
    {
        return (*this) * (!x);
    }

    item_c item_c::operator+=(item_c const& x)
    {
        val = (item_c(val) + x).getval();
        return *this;
    }

    item_c item_c::operator-=(item_c const& x)
    {
        val = (item_c(val) - x).getval();
        return *this;
    }

    item_c item_c::operator*=(item_c const& x)
    {
        val = (item_c(val) * x).getval();
        return *this;
    }

    item_c item_c::operator/=(item_c const& x)
    {
        val = (item_c(val) / x).getval();
        return *this;
    }

    bool item_c::operator==(item_c const& x) const
    {
        return this->getval() == x.getval();
    }

    bool item_c::operator!=(item_c const& x) const
    {
        return this->getval() != x.getval();
    }

    item_c item_c::operator-() const
    {
        return item_c(R - this->val);
    }

    item_c item_c::operator!() const
    {
        return item_c(invurse_table_c::L[this->val]);
    }
}

dla::item_c operator"" _c (unsigned long long n)
{
    return dla::item_c(n);
}