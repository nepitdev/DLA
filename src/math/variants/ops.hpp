#include "types.hpp"

namespace dla
{
    template <class T>
    static vmatrix prod (vmatrix a, vmatrix b) {
        T x = boost::get<T>(a);
        T y = boost::get<T>(b);
        return x * y;
    }

    static vmatrix operator* (vmatrix x, vmatrix y) {
        if (x.which() != y.which())
            return matrix<item_a>(0, 0);
        switch(x.which()) {
            case 0:
                return prod<matrix<item_a>>(x, y);
            case 1:
                return prod<matrix<item_b>>(x, y);
            case 2:
                return prod<matrix<item_c>>(x, y);
            case 3:
                return prod<matrix<item_d>>(x, y);
            default:
                return matrix<item_a>(0, 0);
        }
    }

    template <class T>
    static vmatrix quot (vmatrix a, vmatrix b) {
        T x = boost::get<T>(a);
        T y = boost::get<T>(b);
        return x / y;
    }

    static vmatrix operator/ (vmatrix x, vmatrix y) {
        if (x.which() != y.which())
            return matrix<item_a>(0, 0);
        switch(x.which()) {
            case 0:
                return quot<matrix<item_a>>(x, y);
            case 1:
                return quot<matrix<item_b>>(x, y);
            case 2:
                return quot<matrix<item_c>>(x, y);
            case 3:
                return quot<matrix<item_d>>(x, y);
            default:
                return matrix<item_a>(0, 0);
        }
    }

    template <class T>
    static void _salt (vmatrix a) {
        T x = boost::get<T>(a);
        x.salt();
    }

    static void salt (vmatrix a) {
        switch(a.which()) {
            case 0:
                _salt<matrix<item_a>>(a);
                break;
            case 1:
                _salt<matrix<item_b>>(a);
                break;
            case 2:
                _salt<matrix<item_c>>(a);
                break;
            case 3:
                _salt<matrix<item_d>>(a);
                break;
        }
    }

    template <class T>
    static vmatrix _desalt (vmatrix a) {
        T x = boost::get<T>(a);
        x.desalt();
    }

    static void desalt (vmatrix a) {
        switch(a.which()) {
            case 0:
                _desalt<matrix<item_a>>(a);
                break;
            case 1:
                _desalt<matrix<item_b>>(a);
                break;
            case 2:
                _desalt<matrix<item_c>>(a);
                break;
            case 3:
                _desalt<matrix<item_d>>(a);
                break;
        }
    }

    template<class I, class S>
    static std::vector<uint8_t> _getdata (matrix<I> x)
    {
        S s;
        s.setMatrix(x);
        return s.getFormatedData();
    }

    template<class I, class S1, class S2, class S3, class S4>
    static std::vector<uint8_t> _getdata (vmatrix a) {
        matrix<I> x = boost::get<matrix<I>>(a);
        int size = x.numrows();
        if (size == 8)  return _getdata<I, S1>(x);
        if (size == 16) return _getdata<I, S2>(x);
        if (size == 24) return _getdata<I, S3>(x);
        if (size == 32) return _getdata<I, S4>(x);
        return std::vector<uint8_t>();
    }

    static std::vector<uint8_t> getdata (vmatrix x) {
        switch(x.which()) {
            case 0:
                return _getdata<item_a, set_a1, set_a2, set_a3, set_a4>(x);
            case 1:
                return _getdata<item_b, set_b1, set_b2, set_b3, set_b4>(x);
            case 2:
                return _getdata<item_c, set_c1, set_c2, set_c3, set_c4>(x);
            case 3:
                return _getdata<item_d, set_d1, set_d2, set_d3, set_d4>(x);
        }
    }
}
