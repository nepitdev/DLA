#pragma once

#include <vector>
#include <openssl/sha.h>
#include "../util/digest.hpp"

namespace dla
{
    template < class T >
    class vector
    {
    private:
        std::vector<T> data;
    public:
        vector();
        vector(int n);
        vector(std::vector<T> vec);

        int size() const;

        digest getDigest() const;

        T& operator[] (int index);

        vector<T> operator+ (vector<T> const& x) const;
        vector<T> operator- (vector<T> const& x) const;
        T operator* (vector<T> const& x) const;
        vector<T> operator* (T const& x) const;

        vector<T> operator- () const;
    };

    template <class T>
    static vector<T> operator * (T const& scaler, vector<T> const& vector);
}

#include "vector.cpp"