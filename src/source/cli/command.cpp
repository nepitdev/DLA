#include "command.hpp"

#include <iostream>

namespace dla
{
    void command::fail(std::string _msg)
    {
        invalid = true;
        msg = _msg;
    }

    command::command(int argc, char** argv):
        invalid(false)
    {
        cmd = argv[1];
        for (int i = 2; i < argc; i++)
        {
            std::string flag = argv[i];
            if (flag.at(0) != '-')
            {
                fail("Invalid syntax: flag '" + flag + "' is not allowed.");
            }
            std::string val = "";
            if (i < argc - 1)
            {
                val = argv[i+1];
                if (val.at(0) == '-')
                {
                    val = "";
                } else {
                    i++;
                }
            }
            flags[flag] = val;
        }
        
        if (!invalid) 
        {
            std::cout << cmd << std::endl;
            for (auto const& pair : flags)
            {
                std::cout << pair.first << " " << pair.second << std::endl;
            }
        } else {
            std::cout << msg << std::endl;
        }
    }
}