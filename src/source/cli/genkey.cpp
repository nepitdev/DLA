#include "genkey.hpp"
#include "command.hpp"

#include "../math/group_a/item_a.hpp"
#include "../math/group_a/set_a1.hpp"
#include "../math/group_a/set_a2.hpp"
#include "../math/group_a/set_a3.hpp"
#include "../math/group_a/set_a4.hpp"

#include "../math/group_b/item_b.hpp"
#include "../math/group_b/set_b1.hpp"
#include "../math/group_b/set_b2.hpp"
#include "../math/group_b/set_b3.hpp"
#include "../math/group_b/set_b4.hpp"

#include "../math/group_c/item_c.hpp"
#include "../math/group_c/set_c1.hpp"
#include "../math/group_c/set_c2.hpp"
#include "../math/group_c/set_c3.hpp"
#include "../math/group_c/set_c4.hpp"

#include "../math/group_d/item_d.hpp"
#include "../math/group_d/set_d1.hpp"
#include "../math/group_d/set_d2.hpp"
#include "../math/group_d/set_d3.hpp"
#include "../math/group_d/set_d4.hpp"

namespace dla
{
    void genkey::verify(command* cmd)
    {
        if (!cmd->hasFlag("-o"))
        {
            cmd->fail("Command 'genkey' requires the flag '-o'");
            return;
        }
        std::string p = cmd->getFlag("-o");
        if (p == "")
        {
            cmd->fail("Flag '-o' must be followed by a file name");
            return;
        }
    }

    void genkey::exec(command* cmd)
    {
        rand r;
        char group = cmd->getFlag("-g").at(0);
        int size = std::stoi(cmd->getFlag("-s"));
        std::vector<uint8_t> data;

        switch (group)
        {
            case 'a':
            case 'A':
                data = buildKeyOfSize<item_a, set_a1, set_a2, set_a3, set_a4>(size);
                break;
            case 'b':
            case 'B':
                data = buildKeyOfSize<item_b, set_b1, set_b2, set_b3, set_b4>(size);
                break;
            case 'c':
            case 'C':
                data = buildKeyOfSize<item_c, set_c1, set_c2, set_c3, set_c4>(size);
                break;
            case 'd':
            case 'D':
                data = buildKeyOfSize<item_d, set_d1, set_d2, set_d3, set_d4>(size);
                break;
            default:
                cmd->fail("Group '" + cmd->getFlag("-g") + "' is not a valid group");
        }
        

        std::cout << "I dont do anything yet!" << std::endl;
        return;
    }
}