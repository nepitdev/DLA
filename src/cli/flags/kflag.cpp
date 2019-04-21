#include "kflag.hpp"
#include "../command.hpp"

namespace dla
{
    bool kflag::doesFail(command* cmd)
    {
        if (!cmd->hasFlag("-k"))
        {
            cmd->fail("This command requires the flag '-k'");
            return true;
        }
        if (cmd->getFlag("-k") == "")
        {
            cmd->fail("Flag '-k' must be followed by a file name");
            return true;
        }
        boost::filesystem::path kfile(cmd->getFlag("-k"));
        if (!boost::filesystem::is_regular_file(kfile))
        {
            cmd->fail("File '" + boost::filesystem::absolute(kfile).string() + "' does not exist");
            return true;
        }
        return false;
    }
}