#pragma once

#include "flag.hpp"

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>

namespace dla
{
    class mflag : public flag
    {
    public:
        virtual bool doesFail(command* cmd);
    };
}