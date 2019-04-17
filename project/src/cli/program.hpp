#pragma once

namespace dla
{
    class command;
    class program
    {
    public:
        virtual void verify(command* cmd) = 0;
        virtual void exec(command* cmd) = 0;
    };
}