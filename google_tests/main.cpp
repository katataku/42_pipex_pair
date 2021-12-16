#include <gtest/gtest.h>

#include <stdlib.h>

extern "C" {
#include "../works/pipex.h"
}

TEST(pipex, pwd_pwd)
{
    system("echo bc > infile");

    int argc = 5;
    char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", "actual", NULL};
    char *env[] = {NULL};

    unlink("actual");
    unlink("expected");
    ASSERT_EQ(pipex(argc, argv, env), 0);
    system("< infile pwd | pwd > expected");
    ASSERT_EQ(system("diff actual expected"), 0);
}

TEST(pipex, uname_rev)
{
    system("echo bc > infile");

    int argc = 5;
    char *argv[] = {"./main", "infile", "/usr/bin/uname", "/usr/bin/rev", "actual", NULL};
    char *env[] = {NULL};

    unlink("actual");
    unlink("expected");
    ASSERT_EQ(pipex(argc, argv, env), 0);
    system("< infile uname | rev > expected");
    ASSERT_EQ(system("diff actual expected"), 0);
}

TEST(pipex, sort_rev)
{
    system("echo bc > infile");
    system("echo ab >> infile");

    int argc = 5;
    char *argv[] = {"./main", "infile", "/usr/bin/sort", "/usr/bin/rev", "actual", NULL};
    char *env[] = {NULL};

    unlink("actual");
    unlink("expected");
    ASSERT_EQ(pipex(argc, argv, env), 0);
    system("< infile sort | rev > expected");
    ASSERT_EQ(system("diff actual expected"), 0);
}

TEST(pipex, with_option)
{
    system("echo bc > infile");
    system("echo ab >> infile");

    int argc = 5;
    char *argv[] = {"./main", "infile", "/usr/bin/grep ab", "/usr/bin/wc -l -c", "actual", NULL};
    char *env[] = {NULL};

    unlink("actual");
    unlink("expected");
    ASSERT_EQ(pipex(argc, argv, env), 0);
    system("< infile grep ab | wc -l -c > expected");
    ASSERT_EQ(system("diff actual expected"), 0);
}
