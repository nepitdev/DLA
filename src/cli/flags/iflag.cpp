#include "iflag.hpp"
#include "../command.hpp"

namespace dla
{
    bool iflag::doesFail(command* cmd)
    {
        if (!cmd->hasFlag("-i"))
        {
            cmd->fail("This command requires the flag '-i'");
            return true;
        }
        if (cmd->getFlag("-i") == "")
        {
            cmd->fail("Flag '-i' must be followed by a file name");
            return true;
        }
        boost::filesystem::path ifile(cmd->getFlag("-i"));
        if (!boost::filesystem::is_regular_file(ifile))
        {
            cmd->fail("File '" + boost::filesystem::absolute(ifile).string() + "' does not exist");
            return true;
        }
        return false;
    }
}