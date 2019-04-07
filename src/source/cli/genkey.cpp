#include "genkey.hpp"
#include "command.hpp"

namespace dla
{
    void genkey::verify(command* cmd)
    {
        if (!cmd->hasFlag("-o"))
        {
            cmd->fail("Command 'genkey' requires the flag '-o'");
            return;
        }
        std::string path = cmd->getFlag("-o");
        if (path == "")
        {
            cmd->fail("Flag '-o' must be followed by a file name");
            return;
        }
    }

    void genkey::exec(command* cmd)
    {
        std::cout << "I dont do anything yet!" << std::endl;
        return;
    }
}