#pragma once

#include <map>
#include <memory>
#include <string>

#include "programs/program.hpp"

namespace dla
{
    class command
    {
    private:
        static std::map<std::string, std::shared_ptr<dla::program>> programs;

        bool invalid;
        std::string msg;
        std::string cmd;
        std::map<std::string, std::string> flags;

        static const int VERIFY = 1;
        static const int EXEC = 2;

        bool delegate(int mode);

    public:
        command(int argc, char** argv);

        void fail(std::string msg);
        bool verify() { return delegate(VERIFY); }
        bool exec() { return delegate(EXEC); }
        bool isInvalid();
        std::string getMsg();

        bool hasFlag(std::string flag);
        std::string getFlag(std::string flag);
    };
}