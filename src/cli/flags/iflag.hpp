#pragma once

#include "flag.hpp"

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

namespace dla
{
    class iflag : public flag
    {
    public:
        virtual bool doesFail(command* cmd);
    };
}