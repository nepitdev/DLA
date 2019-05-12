#include "../../catch.hpp"

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include "../../../src/cli/command.hpp"

TEST_CASE("genkey should fail without any flags") 
{
    char arg1[] = "dla";
    char arg2[] = "genkey";
    char* args[2] = {
        arg1, arg2
    };
    dla::command cmd(2, args);
    REQUIRE_FALSE(cmd.verify());
    REQUIRE(cmd.getMsg() == "This command requires the flag '-o'");
}

TEST_CASE("genkey should fail without 'm' flag") 
{
    char arg1[] = "dla";
    char arg2[] = "genkey";
    char arg3[] = "-o";
    char arg4[] = "key";
    char* args[4] = {
        arg1, arg2, arg3, arg4
    };
    dla::command cmd(4, args);
    REQUIRE_FALSE(cmd.verify());
    REQUIRE(cmd.getMsg() == "This command requires the flag '-m'");
}

TEST_CASE("genkey should fail without 'o' flag") 
{
    char arg1[] = "dla";
    char arg2[] = "genkey";
    char arg3[] = "-m";
    char arg4[] = "A8";
    char* args[4] = {
        arg1, arg2, arg3, arg4
    };
    dla::command cmd(4, args);
    REQUIRE_FALSE(cmd.verify());
    REQUIRE(cmd.getMsg() == "This command requires the flag '-o'");
}

TEST_CASE("genkey should generate a keyfile") 
{
    char arg1[] = "dla";
    char arg2[] = "genkey";
    char arg3[] = "-o";
    char arg4[] = "testkey";
    char arg5[] = "-m";
    char arg6[] = "A8";
    char* args[6] = {
        arg1, arg2, arg3, arg4, arg5, arg6
    };
    dla::command cmd(6, args);
    REQUIRE(cmd.verify());
    cmd.exec();
    boost::filesystem::path file("testkey");
    REQUIRE(boost::filesystem::is_regular_file(file));
    boost::filesystem::remove(file);
}