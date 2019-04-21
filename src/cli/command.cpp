#include "command.hpp"

#include <iostream>
#include "programs/genkey.hpp"
#include "programs/enciph.hpp"

namespace dla
{
    std::map<std::string, std::shared_ptr<dla::program>> command::programs =
    {
        { "genkey", std::make_shared<genkey>() },
        { "enciph", std::make_shared<enciph>() }
    };

    bool command::delegate(int mode)
    {
        if (invalid) return false;
        auto it = programs.find(cmd);
        if (it != programs.end())
        {
            switch (mode)
            {
                case VERIFY: it->second->verify(this); break;
                case EXEC: it->second->exec(this); break;
            }
        }
        else
        {
            fail("Command '" + cmd + "' is unknown.");
        }
        if (invalid) return false;
        return true;
    }

    command::command(int argc, char** argv):
        invalid(false)
    {
        if (argc == 1)
        {
            fail("No command specifyed!");
            return;
        }

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
        
        // if (!invalid) 
        // {
        //     std::cout << cmd << std::endl;
        //     for (auto const& pair : flags)
        //     {
        //         std::cout << pair.first << " " << pair.second << std::endl;
        //     }
        // } else {
        //     std::cout << msg << std::endl;
        // }
    }

    void command::fail(std::string _msg)
    {
        invalid = true;
        msg = _msg;
    }

    bool command::isInvalid()
    {
        return invalid;
    }

    std::string command::getMsg()
    {
        return msg;
    }

    bool command::hasFlag(std::string flag)
    {
        auto it = flags.find(flag);
        return it != flags.end();
    }

    std::string command::getFlag(std::string flag)
    {
        auto it = flags.find(flag);
        if (it != flags.end()) return it->second;
        else return "";
    }
}