#pragma once

#include <cstdint>
#include <vector>
#include "../math/matrix.hpp"
#include "../util/rand.hpp"

namespace dla
{
    template < class T, class BUFFER >
    class set
    {
    protected:
        static const int BYTE_SIZE = 8;
        const int BLOCK_SIZE = 0;
        const int PAYLOAD_SIZE = 0;
        const int ITEM_SIZE = 0;
        std::vector<T> data;
    private:
        int pow(int a, int b);
    public:
        set (int BLOCK_SIZE, int PAYLOAD_SIZE, int ITEM_SIZE);

        void setRawData(std::vector<uint8_t> raw_data);
        void setMatrix(matrix<T> mat);
        void setFormatedData(std::vector<uint8_t> formated_data);

        std::vector<uint8_t> getRawData();
        matrix<T> getMatrix();
        std::vector<uint8_t> getFormatedData();

        T operator[] (int index);
        int size();
    };
}

#include "set.cpp"