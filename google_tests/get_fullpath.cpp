#include <gtest/gtest.h>

extern "C" {
#include "shared.h"
}

char *envp2[] = {
        "LANG=ja_JP.UTF-8",
        "HOME=/Users/hayashi-ay",
        "SHELL=/bin/bash",
        "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
        "COLORTERM=truecolor",
        NULL
    };

TEST(GetFullpathTest, normal_case)
{
    int argc = 5;


    ASSERT_STREQ(get_fullpath("ls", envp2), "/bin/ls");
}

TEST(GetFullpathTest, has_slash)
{
    ASSERT_STREQ(get_fullpath("/bin/ls", envp2), "/bin/ls");
}

TEST(DISABLED_GetFullpathTest, has_slash2)
{
    char *env[] = {
        "LANG=ja_JP.UTF-8",
        "HOME=/Users/hayashi-ay",
        "SHELL=/bin/bash",
        "PS1=\h\[\033[00m\]:\W\[\033[31m\]$(__git_ps1 [%s])\[\033[00m\]\$",
        "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
        "COLORTERM=truecolor",
        NULL
    };

    ASSERT_STREQ(get_fullpath("./ls", envp2), "./ls");
}
