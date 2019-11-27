#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/beast/core/detail/base64.hpp>
#include <boost/variant.hpp>

#include "program.hpp"
#include "../../util/rand.hpp"
#include "../../math/matrix.hpp"
#include "../flags/iflag.hpp"
#include "../flags/kflag.hpp"
#include "../flags/oflag.hpp"
#include "../flags/mflag.hpp"
#include "../../math/variants/types.hpp"
#include "../../math/variants/ops.hpp"

namespace dla
{
    class deciph : public program
    {
    public:
        virtual void verify(command* cmd);
        virtual void exec(command* cmd);
    private:
        template<class I, class S>
        matrix<I> importMatrix(std::vector<uint8_t> data)
        {
            S x;
            x.setFormatedData(data);
            return x.getMatrix();
        }

        template<class I, class S1, class S2, class S3, class S4>
        matrix<I> importMatrixOfSize(int size, std::vector<uint8_t> data)
        {
            if (size == 8)  return importMatrix<I, S1>(data);
            if (size == 16) return importMatrix<I, S2>(data);
            if (size == 24) return importMatrix<I, S3>(data);
            if (size == 32) return importMatrix<I, S4>(data);
            return matrix<I>(0, 0);
        }
    };
}