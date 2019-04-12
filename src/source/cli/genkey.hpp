#pragma once

#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/beast/core/detail/base64.hpp>
#include "program.hpp"

#include "../util/rand.hpp"
#include "../math/matrix.hpp"

namespace dla
{
    class genkey : public program
    {
    public:
        virtual void verify(command* cmd);
        virtual void exec(command* cmd);
    private:
        template<class I, class S>
        std::vector<uint8_t> buildKey(int size)
        {
            rand r;
            matrix<I> m(size, size, r);
            
            S x;
            x.setMatrix(m);
            return x.getFormatedData();
        }

        template<class I, class S1, class S2, class S3, class S4>
        std::vector<uint8_t> buildKeyOfSize(int size)
        {
            if (size == 8)  return buildKey<I, S1>(8);
            if (size == 16) return buildKey<I, S2>(16);
            if (size == 24) return buildKey<I, S3>(24);
            if (size == 32) return buildKey<I, S4>(32);
            return std::vector<uint8_t>();
        }
    };
}