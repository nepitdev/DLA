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
            for (int i = 3; i >= 0; i--)
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
            bytes.push_back((val & (mask << (8*i))) >> (8*i));
        return bytes;
    }

    bool item_d::canBeSalted() const
    {
        return ((uint64_t) val < (uint64_t) (R - HIGH_ORDER_BIT.val));
    }

    bool item_d::isSalted() const
    {
        return ((uint64_t) val >= (uint64_t) (HIGH_ORDER_BIT.val));
    }

    const item_d item_d::ZERO = 0_d;
    const item_d item_d::UNIT = 1_d;
    const item_d item_d::HIGH_ORDER_BIT = 2147483648_d;

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
        if (val == 0) return ZERO;

        std::vector<int64_t> x;
        std::vector<int64_t> k;
        
        x.push_back(R);
        x.push_back(val);
        k.push_back(0);

        int n = 1;
        while (x[n] > 1)
        {
            k.push_back(x[n-1] / x[n]);
            x.push_back(x[n-1] % x[n]);
            n++;
        }

        std::vector<int64_t> q;
        q.push_back(1);
        q.push_back(-k[n-1]);
        
        for (int i = 2; i < n; i++)
        {
            q.push_back(q[i-2]-(q[i-1]*k[n-i]));
        }

        int32_t inv = q[n-1] < 0 ? q[n-1] + R : q[n-1];
        return item_d(inv);
    }
}

dla::item_d operator"" _d (unsigned long long n)
{
    return dla::item_d(n);
}