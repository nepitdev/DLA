#pragma once

#include "vector.hpp"
#include <cmath>
#include <memory>
#include <vector>
#include "vector.hpp"
#include "../util/bytestream.hpp"
#include "../util/rand.hpp"

namespace dla
{
    template < class T >
    class matrix
    {
    private:
        std::vector<dla::vector<T>> data;
        int cols;
        int rows;
    public:
        matrix(int rows, int cols);
        matrix(int rows, int cols, bytestream& stream);
        matrix(std::vector<dla::vector<T>> mat);

        int numcols() const;
        int numrows() const;

        dla::vector<T> getrow (int row) const;
        dla::vector<T> getcol (int col) const;

        T getitm (int row, int col) const;
        void setitm (int row, int col, T val);

        void salt();
        void desalt();

        matrix<T> operator* (matrix<T> const& x) const;
        matrix<T> operator/ (matrix<T> const& x) const;
        matrix<T> operator% (matrix<T> const& x) const;
        matrix<T> operator~ () const;
        matrix<T> operator! () const;
    };

    template <class T>
    static vector<T> operator * (T const& scaler, vector<T> const& vector);
}

#include "matrix.cpp"