#pragma once

#include "matrix.hpp"

namespace dla
{
    template < class T >
    matrix<T>::matrix(int rows, int cols):
        data(std::vector<dla::vector<T>>()),
        rows(rows), cols(cols)
    {
        for (int c = 0; c < cols; c++)
        {
            data.push_back(dla::vector<T>(rows));
        }
    }

    template < class T >
    matrix<T>::matrix(int rows, int cols, bytestream& stream):
        data(std::vector<dla::vector<T>>()),
        rows(rows), cols(cols)
    {
        for (int c = 0; c < cols; c++)
        {
            dla::vector<T> col(rows);
            for (int r = 0; r < rows; r++)
            {
                col[r] = T(stream);
            }
            data.push_back(col);
        }
    }

    template < class T >
    matrix<T>::matrix(std::vector<dla::vector<T>> mat):
        data(mat), rows(mat[0].size()), cols(mat.size()) { }

    template < class T >
    int matrix<T>::numrows() const
    {
        return rows;
    }
    
    template < class T >
    int matrix<T>::numcols() const
    {
        return cols;
    }
    
    template < class T >
    dla::vector<T> matrix<T>::getrow (int row) const
    {
        dla::vector<T> v(cols);
        for (int c = 0; c < cols;c ++)
        {
            v[c] = getitm(row,c);
        }
        return v;
    }

    template < class T >
    dla::vector<T> matrix<T>::getcol (int col) const
    {
        return data.at(col);
    }

    template < class T >
    T matrix<T>::getitm (int row, int col) const
    {
        dla::vector<T> vec = getcol(col);
        return vec[row];
    }

    template < class T >
    void matrix<T>::setitm (int row, int col, T val)
    {
        dla::vector<T> vec = data.at(col);
        vec[row] = val;
        data.at(col) = vec;
    }

    template < class T >
    void matrix<T>::salt ()
    {
        rand rng;
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (data[c][r].canBeSalted())
                    if (rng.next(0, 1) == 1)
                        data[c][r] += T::HIGH_ORDER_BIT;

        vector<T> iv(rows);
        for (int i = 0; i < rows; i++)
            iv[i] = T(rng);
        data.insert(data.begin(), iv);
        cols++;

        for (int i = 1; i < cols; i++)
        {
            digest hash = data[i-1].getDigest();
            vector<T> mask(rows);
            for (int j = 0; j < rows; j++)
                mask[j] = T(hash);
            data[i] = data[i] + mask;
        }
    }

    template < class T >
    void matrix<T>::desalt ()
    {
        for (int i = cols - 1; i > 0; i--)
        {
            digest hash = data[i-1].getDigest();
            vector<T> mask(rows);
            for (int j = 0; j < rows; j++)
                mask[j] = T(hash);
            data[i] = data[i] - mask;
        }

        data.erase(data.begin());
        cols--;

        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (data[c][r].isSalted())
                    data[c][r] -= T::HIGH_ORDER_BIT;            
    }

    template < class T >
    matrix<T> matrix<T>::operator* (matrix<T> const& x) const
    {
        matrix m(x.rows, cols);
        for (int r = 0; r < m.rows; r++)
        {
            dla::vector<T> v = x.getrow(r);
            for (int c = 0; c < m.cols; c++)
            {
                dla::vector<T> u = getcol(c);
                m.setitm(r, c, v * u);
            }
        }
        return m;
    }

    template < class T >
    matrix<T> matrix<T>::operator/ (matrix<T> const& x) const
    {
        return (*this) * (!x);
    }

    template < class T >
    matrix<T> matrix<T>::operator% (matrix<T> const& x) const
    {
        return (!(*this)) * x;
    }

    template < class T >
    matrix<T> matrix<T>::operator! () const
    {
        matrix d(rows, cols);
        matrix m(rows, cols);

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (r == c) m.setitm(r, c, T::UNIT);
                else m.setitm(r, c, T::ZERO);
                d.setitm(r, c, getitm(r, c));
            }
        }

        for (int c = 0; c < cols; c++)
        {
            if (d.getitm(c,c) == T::ZERO)
            {
                for (int n = c + 1; n < rows; n++)
                {
                    if (d.getitm(c,n) != T::ZERO)
                    {
                        for (int x = 0; x < cols; x++)
                        {
                            T dn = d.getitm(n, x);
                            T mn = m.getitm(n, x);
                            d.setitm(n, x, d.getitm(c, x));
                            m.setitm(n, x, m.getitm(c, x));
                            d.setitm(c, x, dn);
                            m.setitm(c, x, mn);
                        }
                        break;
                    }
                }
            }
            for (int r = c; r < rows; r++)
            {
                if (d.getitm(r,c) != T::ZERO)
                {
                    T inv = !d.getitm(r,c);
                    for (int x = 0; x < cols; x++)
                    {
                        d.setitm(r, x, d.getitm(r, x) * inv);
                        m.setitm(r, x, m.getitm(r, x) * inv);
                    }
                }
            }
            for (int r = c + 1; r < rows; r++)
            {
                if (d.getitm(r,c) != T::ZERO)
                {
                    for (int x = 0; x < cols; x++)
                    {
                        d.setitm(r, x, d.getitm(c, x) - d.getitm(r, x));
                        m.setitm(r, x, m.getitm(c, x) - m.getitm(r, x));
                    }
                }
            }
        }

        for (int c = cols - 1; c >= 0; c--)
        {
            for (int r = c - 1; r >= 0; r--)
            {
                T coef = d.getitm(r,c);
                for (int x = 0; x < cols; x++)
                {
                    d.setitm(r, x, d.getitm(r, x) - (d.getitm(c, x) * coef));
                    m.setitm(r, x, m.getitm(r, x) - (m.getitm(c, x) * coef));
                }
            }
        }
        return m;
    }

    template < class T >
    matrix<T> matrix<T>::operator~ () const
    {
        matrix m(rows, cols);
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                m.setitm(r,c,getitm(c,r));
            }
        }
        return m;
    }
}