#include <iostream>
#include "cli/command.hpp"

int main(int argc, char** argv)
{
    dla::command cmd(argc, argv);
    if (cmd.verify()) cmd.exec();
    if (cmd.isInvalid()) std::cout << cmd.getMsg() << std::endl;
}