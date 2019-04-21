#pragma once

#include <bitset>
#include "set.hpp"
#include "../util/rand.hpp"
#include <iostream>

namespace dla
{
    template < class T, class BUFFER >
    int set<T, BUFFER>::pow(int a, int b)
    {
        int result = 1;
        for (int i = 0; i < b; i++)
        {
            result *= a;
        }
        return result;
    }

    template < class T, class BUFFER >
    set<T, BUFFER>::set (int BLOCK_SIZE, int PAYLOAD_SIZE, int ITEM_SIZE):
        BLOCK_SIZE(BLOCK_SIZE), PAYLOAD_SIZE(PAYLOAD_SIZE), ITEM_SIZE(ITEM_SIZE) { }

    template < class T, class BUFFER >
    void set<T, BUFFER>::setRawData(std::vector<uint8_t> raw_data)
    {
        data.clear();
        data.shrink_to_fit();

        BUFFER reg = 0;
        BUFFER mask = pow(2, PAYLOAD_SIZE) - 1;

        int pos = -1;

        int P = BLOCK_SIZE - (raw_data.size() % BLOCK_SIZE);
        P = (P == 0) ? BLOCK_SIZE : P;
        rand rng;
        for (int i = 1; i < P; i++)
        {
            raw_data.push_back(rng.next());
        }
        int H = P % BLOCK_SIZE;
        int U = (255 - H) / BLOCK_SIZE;
        int Q = H + (BLOCK_SIZE * rng.next(0, U));
        raw_data.push_back(uint8_t(Q));

        int count = raw_data.size();
        for (int i = 0; i < count; i++)
        {
            reg = reg << BYTE_SIZE;
            reg += raw_data[i];
            pos += BYTE_SIZE;
            while (pos >= PAYLOAD_SIZE - 1)
            {
                int offset = pos - PAYLOAD_SIZE + 1;
                BUFFER m = mask << offset;
                BUFFER v = (reg & m) >> offset;
                data.push_back(T(v));
                pos -= PAYLOAD_SIZE;
            }
        }
    }

    template < class T, class BUFFER >
    void set<T, BUFFER>::setMatrix (matrix<T> matrix) 
    {
        data.clear();
        data.shrink_to_fit();

        int cols = matrix.numcols();
        int rows = matrix.numrows();
        for (int c = 0; c < cols; c++)
            for (int r = 0; r < rows; r++)
                data.push_back(matrix.getitm(r, c));
    }
    
    template < class T, class BUFFER >
    void set<T, BUFFER>::setFormatedData(std::vector<uint8_t> formated_data)
    {
        data.clear();
        data.shrink_to_fit();

        BUFFER reg = formated_data[0];
        BUFFER mask = pow(2, ITEM_SIZE) - 1;
        int pos = BYTE_SIZE - 1;

        while ((reg & (1 << pos)) == 0) pos--;
        pos--;

        int count = formated_data.size();
        for (int i = 1; i < count; i++)
        {
            reg = reg << BYTE_SIZE;
            reg += formated_data[i];
            pos += BYTE_SIZE;
            while (pos >= ITEM_SIZE - 1)
            {
                int offset = pos - ITEM_SIZE + 1;
                BUFFER m = mask << offset;
                BUFFER v = (reg & m) >> offset;
                data.push_back(T(v));
                pos -= ITEM_SIZE;
            }
        }
    }

    template < class T, class BUFFER >
    std::vector<uint8_t> set<T, BUFFER>::getRawData()
    {
        std::vector<uint8_t> raw_data(0);
        BUFFER reg = 0;
        BUFFER mask = pow(2, BYTE_SIZE) - 1;
        int pos = -1;
        
        int count = data.size();
        for (int i = 0; i < count; i++)
        {
            reg = reg << PAYLOAD_SIZE;
            reg += data[i].getval();
            pos += PAYLOAD_SIZE;
            
            while (pos >= BYTE_SIZE - 1)
            {
                int offset = pos - BYTE_SIZE + 1;
                BUFFER m = mask << offset;
                BUFFER v = (reg & m) >> offset;
                raw_data.push_back(uint8_t(v));
                pos -= BYTE_SIZE;
            }
        }
        int P = raw_data[raw_data.size()-1] % BLOCK_SIZE;
        P = (P == 0) ? 5 : P;
        for (int i = 0; i < P; i++)
        {
            raw_data.pop_back();
        }
        raw_data.shrink_to_fit();

        return raw_data;
    }

    template < class T, class BUFFER >
    matrix<T> set<T,BUFFER>::getMatrix()
    {
        int rows = BLOCK_SIZE / PAYLOAD_SIZE * BYTE_SIZE;
        int cols = data.size() / rows;
        matrix<T> m(rows, cols);
        for (int c = 0; c < cols; c++)
            for (int r = 0; r < rows; r++)
                m.setitm(r, c, data[(c * rows) + r]);
        return m;
    }

    template < class T, class BUFFER >
    std::vector<uint8_t> set<T, BUFFER>::getFormatedData()
    {
        std::vector<uint8_t> formated_data(0);
        BUFFER reg = 1;
        BUFFER mask = pow(2, BYTE_SIZE) - 1;
        int pos = -1;

        int padding = BYTE_SIZE - ((data.size() * ITEM_SIZE) % BYTE_SIZE);
        pos += padding;
        
        int count = data.size();
        for (int i = 0; i < count; i++)
        {
            reg = reg << ITEM_SIZE;
            reg += data[i].getval();
            pos += ITEM_SIZE;
            
            while (pos >= BYTE_SIZE - 1)
            {
                int offset = pos - BYTE_SIZE + 1;
                BUFFER m = mask << offset;
                BUFFER v = (reg & m) >> offset;
                formated_data.push_back(uint8_t(v));
                pos -= BYTE_SIZE;
            }
        }
        return formated_data;
    }

    template < class T, class BUFFER >
    T set<T, BUFFER>::operator[] (int index)
    {
        return data[index];
    }

    template < class T, class BUFFER >
    int set<T, BUFFER>::size()
    {
        return data.size();
    }
}