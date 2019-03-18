#include "item_d.hpp"

namespace dla
{
    uint64_t item_d::mathval() const
    {
        return val;
    }

    item_d::item_d():
        val(0) { }

    item_d::item_d(uint32_t val):
        val(val) { }

    item_d::item_d (bytestream& stream)
    {
        uint32_t mask = 4294967295;
        val = R;
        while (val == R)
        {
            uint32_t temp = 0;
            for (int i = 1; i >= 0; i--)
                temp += stream.next() << (8 * i);
            temp = temp & mask;
            if (temp < R) val = temp % R;
        }
    }

    uint32_t item_d::getval() const
    {
        return val;
    }

    std::vector<uint8_t> item_d::getBytes() const
    {
        uint32_t mask = 255;
        std::vector<uint8_t> bytes;
        for (int i = 3; i >= 0; i--)
            bytes.push_back(val & (mask << (8*i)));
        return bytes;
    }

    bool item_d::canBeSalted() const
    {
        return ((int) val < (int) (R - HIGH_ORDER_BIT.val));
    }

    bool item_d::isSalted() const
    {
        return ((int) val >= (int) (HIGH_ORDER_BIT.val));
    }

    const item_d item_d::ZERO = 0_d;
    const item_d item_d::UNIT = 1_d;
    const item_d item_d::HIGH_ORDER_BIT = 32768_d;

    item_d item_d::operator+(item_d const& x) const
    {
        return item_d((mathval() + x.mathval()) % R);
    }

    item_d item_d::operator-(item_d const& x) const
    {
        return (*this) + (-x);
    }

    item_d item_d::operator*(item_d const& x) const
    {
        return item_d((mathval() * x.mathval()) % R);
    }

    item_d item_d::operator/(item_d const& x) const
    {
        return (*this) * (!x);
    }

    item_d item_d::operator+=(item_d const& x)
    {
        val = (item_d(val) + x).getval();
        return *this;
    }

    item_d item_d::operator-=(item_d const& x)
    {
        val = (item_d(val) - x).getval();
        return *this;
    }

    item_d item_d::operator*=(item_d const& x)
    {
        val = (item_d(val) * x).getval();
        return *this;
    }

    item_d item_d::operator/=(item_d const& x)
    {
        val = (item_d(val) / x).getval();
        return *this;
    }

    bool item_d::operator==(item_d const& x) const
    {
        return this->getval() == x.getval();
    }

    bool item_d::operator!=(item_d const& x) const
    {
        return this->getval() != x.getval();
    }

    item_d item_d::operator-() const
    {
        return item_d(R - this->val);
    }

    item_d item_d::operator!() const
    {
        //TODO implement extended euclidian algorythum
    }
}

dla::item_d operator"" _d (unsigned long long n)
{
    return dla::item_d(n);
}