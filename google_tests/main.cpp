#include <gtest/gtest.h>

#include <stdlib.h>

extern "C" {
#include "../works/pipex.h"
}

TEST(pipex, pwd_pwd)
{
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
    int argc = 5;
    char *argv[] = {"./main", "infile", "/usr/bin/uname", "/usr/bin/rev", "actual", NULL};
    char *env[] = {NULL};

    unlink("actual");
    unlink("expected");
    ASSERT_EQ(pipex(argc, argv, env), 0);
    system("< infile uname | rev > expected");
    ASSERT_EQ(system("diff actual expected"), 0);
}
