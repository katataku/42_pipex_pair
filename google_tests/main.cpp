#include <gtest/gtest.h>

#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <assert.h> 

extern "C" {
#include "../works/pipex.h"
}

TEST(pipex, noramal)
{
    ASSERT_EQ(pipex(), 0);
}
