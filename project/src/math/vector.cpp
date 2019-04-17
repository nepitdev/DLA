#pragma once

#include "vector.hpp"

namespace dla
{
    template < class T >
    vector<T>::vector():
        data(std::vector<T>(0)) { }
    
    template < class T >
    vector<T>::vector(int n):
        data(std::vector<T>(n)) { }

    template < class T >
    vector<T>::vector(std::vector<T> vec):
        data(vec) { }

    template < class T >
    int vector<T>::size() const
    {
        return data.size();
    }

    template < class T >
    digest vector<T>::getDigest() const
    {
        std::vector<uint8_t> text;
        for (int i = 0; i < data.size(); i++)
        {
            std::vector<uint8_t> bytes = data[i].getBytes();
            text.insert(text.end(), bytes.begin(), bytes.end());
        }
        return digest(text);
    }

    template < class T >
    T& vector<T>::operator[] (int index)
    {
        return data.at(index);
    }

    template < class T >
    vector<T> vector<T>::operator+ (vector<T> const& x) const
    {
        int l = data.size();
        if (x.data.size() != l)
            return vector<T>(0);
        vector<T> sum(l);
        for (int i = 0; i < l; i++)
        {
            sum[i] = (data[i] + x.data[i]);
        }
        return sum;
    }

    template < class T >
    vector<T> vector<T>::operator- (vector<T> const& x) const
    {
        return (*this) + (-x);
    }

    template < class T >
    T vector<T>::operator* (vector<T> const& x) const
    {
        int l = data.size();
        if (x.data.size() != l)
            return T::ZERO;
        T dot = T::ZERO;
        for (int i = 0; i < l; i++)
        {
            dot = dot + (data[i] * x.data[i]);
        }
        return dot;
    }
    
    template <class T>
    vector<T> vector<T>::operator* (T const& x) const
    {
        int l = data.size();
        vector<T> prod(l);
        for (int i = 0; i < l; i++)
        {
            prod[i] = x * data[i]; 
        }
        return prod;
    }

    template < class T >
    vector<T> vector<T>::operator- () const
    {
        int l = data.size();
        vector<T> neg(l);
        for (int i = 0; i < l; i++)
        {
            neg[i] = -data[i];
        }
        return neg;
    }

    template <class T>
    static vector<T> operator* (T const& scaler, vector<T> const& vector)
    {
        return vector * scaler;
    }
}