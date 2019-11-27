#pragma once

namespace dla
{
    class command;
    class flag
    {
    public:
        virtual bool doesFail(command* cmd) = 0;
    };
}