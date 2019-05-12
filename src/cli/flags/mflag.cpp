#include "mflag.hpp"
#include "../command.hpp"

namespace dla
{
    bool mflag::doesFail(command* cmd)
    {
        if (!cmd->hasFlag("-m"))
        {
            cmd->fail("This command requires the flag '-m'");
            return true;
        }
        if (cmd->getFlag("-m") == "")
        {
            cmd->fail("Flag '-m' must be followed by a string");
            return true;
        }
        std::string mode = cmd->getFlag("-m");
        if (!isalpha(mode.at(0)))
        {
            cmd->fail("Mode '" + mode + "' is invalid, the mode must begin with a letter");
            return true;
        }
        try
        {
            int size = boost::lexical_cast<int>(mode.substr(1, mode.size()-1));
            if (size < 0)
            {
                cmd->fail("Mode '" + mode + "' is invalid, the mode must end with a whole number");
                return true;
            }
        }
        catch (boost::bad_lexical_cast &)
        {
            cmd->fail("Mode '" + mode + "' is invalid, the mode must end with a whole number");
            return true;
        }
        return false;
    }
}