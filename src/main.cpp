/*
#include <iostream>
#include <string>
#include <vector>
#include "math/group_a/set_a1.hpp"
#include "math/matrix.hpp"
#include "math/set.hpp"
#include "util/digest.hpp"
#include "util/rand.hpp"

int main()
{
    std::vector<uint8_t> x(64);
    dla::rand rng;

    for (int i = 0; i < x.size(); i++)
    {
        x[i] = rng.next();
    }

    dla::matrix<dla::item_a> key(8, 8, rng);

    dla::set_a1 s;
    s.setRawData(x);
    dla::matrix<dla::item_a> m = s.getMatrix();
    
    m.salt();
    m = m * key;

    std::cout << s.getBase64() << std::endl;
    s.setMatrix(m);
    std::cout << s.getBase64() << std::endl;
    s.setBase64(s.getBase64());
    m = s.getMatrix();

    m = m / key;

    m.desalt();

    s.setMatrix(m);
    std::vector<uint8_t> y = s.getRawData();

    bool sucess = true;
    if (x.size() == y.size())
    {
        for (int i = 0; i < x.size(); i++)
        {
            if (x[i] != y[i]) sucess = false;
        }
    }
    else
    {
        sucess = false;
    }
    
    if (sucess)
    {
        std::cout << "CORRECT!" << std::endl;
    }
    else
    {
        std::cout << "WRONG!" << std::endl;
    }
    
    return 0;
}
*/