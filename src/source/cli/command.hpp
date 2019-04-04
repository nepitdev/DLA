#pragma once

#include <map>

namespace dla
{
    class command
    {
    private:
        bool invalid;
        std::string msg;
        std::string cmd;
        std::map<std::string, std::string> flags;

        void fail(std::string msg);

    public:
        command(int argc, char** argv);
    };
}