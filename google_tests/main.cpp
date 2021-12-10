#include <gtest/gtest.h>

#include <stdlib.h>

extern "C" {
#include "../works/pipex.h"
}

TEST(pipex, noramal)
{
    int argc = 5;
    char *argv[] = {"./main", "infile", "pwd", "pwd", "actual", NULL};
    char *env[] = {NULL};

    ASSERT_EQ(pipex(argc, argv, env), 0);
    system("< infile pwd | pwd > expected");
    ASSERT_EQ(system("diff actual expected"), 0);
}
