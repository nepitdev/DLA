#pragma once

#include <iostream>
#include "program.hpp"

namespace dla
{
    class genkey : public program
    {
    public:
        virtual void verify(command* cmd);
        virtual void exec(command* cmd);
    };
}