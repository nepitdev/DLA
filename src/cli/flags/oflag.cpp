#include "oflag.hpp"
#include "../command.hpp"

namespace dla
{
    bool oflag::doesFail(command* cmd)
    {
        if (!cmd->hasFlag("-o"))
        {
            cmd->fail("This command requires the flag '-o'");
            return true;
        }
        if (cmd->getFlag("-o") == "")
        {
            cmd->fail("Flag '-o' must be followed by a file name");
            return true;
        }
        boost::filesystem::path ofile(cmd->getFlag("-o"));
        if (boost::filesystem::is_regular_file(ofile))
        {
            cmd->fail("File '" + boost::filesystem::absolute(ofile).string() + "' already exist");
            return true;
        }
        auto odir = boost::filesystem::absolute(ofile).parent_path();
        if (!boost::filesystem::exists(odir))
        {
            cmd->fail("Directory '" + odir.string() + "' does not exist");
            return true;
        }
        return false;
    }
}