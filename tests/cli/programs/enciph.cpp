#include "../../catch.hpp"

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include "../../../src/cli/command.hpp"

TEST_CASE("enciph should fail without any flags") 
{
    char arg1[] = "dla";
    char arg2[] = "enciph";
    char* args[2] = {
        arg1, arg2
    };
    dla::command cmd(2, args);
    REQUIRE_FALSE(cmd.verify());
    REQUIRE(cmd.getMsg() == "This command requires the flag '-i'");
}

TEST_CASE("enciph should fail without 'i' flag") 
{
    char arg1[] = "dla";
    char arg2[] = "enciph";
    char arg3[] = "-o";
    char arg4[] = "ofile";
    char arg5[] = "-k";
    char arg6[] = "kfile";
    char arg7[] = "-m";
    char arg8[] = "A8";
    char* args[8] = {
        arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8
    };
    dla::command cmd(8, args);

    boost::filesystem::ofstream("ofile").close();
    boost::filesystem::ofstream("kfile").close();

    REQUIRE_FALSE(cmd.verify());
    REQUIRE(cmd.getMsg() == "This command requires the flag '-i'");

    boost::filesystem::remove("ofile");
    boost::filesystem::remove("kfile");
}

TEST_CASE("enciph should fail without 'o' flag") 
{
    char arg1[] = "dla";
    char arg2[] = "enciph";
    char arg3[] = "-i";
    char arg4[] = "ifile";
    char arg5[] = "-k";
    char arg6[] = "kfile";
    char arg7[] = "-m";
    char arg8[] = "A8";
    char* args[8] = {
        arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8
    };
    dla::command cmd(8, args);

    boost::filesystem::ofstream("ifile").close();
    boost::filesystem::ofstream("kfile").close();

    REQUIRE_FALSE(cmd.verify());
    REQUIRE(cmd.getMsg() == "This command requires the flag '-o'");

    boost::filesystem::remove("ifile");
    boost::filesystem::remove("kfile");
}

TEST_CASE("enciph should fail without 'k' flag") 
{
    char arg1[] = "dla";
    char arg2[] = "enciph";
    char arg3[] = "-i";
    char arg4[] = "ifile";
    char arg5[] = "-o";
    char arg6[] = "ofile";
    char arg7[] = "-m";
    char arg8[] = "A8";
    char* args[8] = {
        arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8
    };
    dla::command cmd(8, args);

    boost::filesystem::ofstream("ifile").close();

    REQUIRE_FALSE(cmd.verify());
    REQUIRE(cmd.getMsg() == "This command requires the flag '-k'");

    boost::filesystem::remove("ifile");
}

TEST_CASE("enciph should fail without 'm' flag") 
{
    char arg1[] = "dla";
    char arg2[] = "enciph";
    char arg3[] = "-i";
    char arg4[] = "ifile";
    char arg5[] = "-o";
    char arg6[] = "ofile";
    char arg7[] = "-k";
    char arg8[] = "kfile";
    char* args[8] = {
        arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8
    };
    dla::command cmd(8, args);

    boost::filesystem::ofstream("ifile").close();
    boost::filesystem::ofstream("kfile").close();

    REQUIRE_FALSE(cmd.verify());
    REQUIRE(cmd.getMsg() == "This command requires the flag '-m'");

    boost::filesystem::remove("ifile");
    boost::filesystem::remove("kfile");
}

void create_key_file() 
{
    char arg1[] = "dla";
    char arg2[] = "genkey";
    char arg3[] = "-o";
    char arg4[] = "kfile";
    char arg5[] = "-m";
    char arg6[] = "A8";
    char* args[6] = {
        arg1, arg2, arg3, arg4, arg5, arg6
    };
    dla::command cmd(6, args);
    cmd.exec();
}

TEST_CASE("genkey should encrypt a file") 
{
    create_key_file();

    char arg1[] = "dla";
    char arg2[] = "enciph";
    char arg3[] = "-i";
    char arg4[] = "ifile";
    char arg5[] = "-o";
    char arg6[] = "ofile";
    char arg7[] = "-k";
    char arg8[] = "kfile";
    char arg9[] = "-m";
    char arg10[] = "P1";
    char* args[10] = {
        arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10
    };
    dla::command cmd(10, args);

    boost::filesystem::ofstream istream("ifile");
    istream << "hello world!";
    istream.close();

    REQUIRE(cmd.verify());
    cmd.exec();
    
    boost::filesystem::path file("ofile");
    REQUIRE(boost::filesystem::is_regular_file(file));
    boost::filesystem::remove(file);

    boost::filesystem::remove("ifile");
    boost::filesystem::remove("kfile");
}