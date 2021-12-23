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

TEST(get_command, normal_case)
{
    int argc = 5;
    char *env[] = {
        "LANG=ja_JP.UTF-8",
        "HOME=/Users/hayashi-ay",
        "SHELL=/bin/bash",
        "PS1=\h\[\033[00m\]:\W\[\033[31m\]$(__git_ps1 [%s])\[\033[00m\]\$",
        "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
        "COLORTERM=truecolor",
        NULL
    };

    ASSERT_STREQ(get_command("ls", env), "/bin/ls");
}

TEST(get_command, has_slash)
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

    ASSERT_STREQ(get_command("/bin/ls", env), "/bin/ls");
}

TEST(get_command, has_slash2)
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

    ASSERT_STREQ(get_command("./ls", env), "./ls");
}

TEST(pipex, abnormal_infile)
{
   unlink("infile");

    std::string expect_stderr = "infile: No such file or directory\n";
    std::string actual_stderr;
   int argc = 5;
   char *argv[] = {"./main", "infile", "/bin/ls", "/bin/cat", "actual", NULL};
   char *env[] = {NULL};

   unlink("actual");
   unlink("expected");
   testing::internal::CaptureStderr();
   ASSERT_EQ(pipex(argc, argv, env), 0);
   actual_stderr = testing::internal::GetCapturedStderr();

   testing::internal::CaptureStderr();
   system("< infile ls | cat > expected");
   testing::internal::GetCapturedStderr();
   ASSERT_EQ(system("diff actual expected"), 0);
   ASSERT_EQ(expect_stderr, actual_stderr);
}


TEST(pipex, abnormal_outfile)
{
    system("echo bc > infile");
    system("echo ab >> infile");
    unlink("vacant/outfile");

	std::string expect_stderr = "vacant/outfile: No such file or directory\n";
	std::string actual_stderr;
    int argc = 5;
    char *argv[] = {"./main", "infile", "/bin/ls", "/bin/cat", "vacant/outfile", NULL};
    char *env[] = {NULL};

    unlink("actual");
    unlink("expected");
    testing::internal::CaptureStderr();
    ASSERT_EQ(pipex(argc, argv, env), 0);
	actual_stderr = testing::internal::GetCapturedStderr();

    testing::internal::CaptureStderr();
    system("< infile ls | cat > vacant/outfile");
    testing::internal::GetCapturedStderr();
    ASSERT_EQ(expect_stderr, actual_stderr);
}

//TEST(pipex, resolve_path)
//{
//    system("echo bc > infile");
//    system("echo ab >> infile");

//    int argc = 5;
//    char *argv[] = {"./main", "infile", "grep ab", "wc -l -c", "actual", NULL};
//    char *env[] = {NULL};

//    unlink("actual");
//    unlink("expected");
//    ASSERT_EQ(pipex(argc, argv, env), 0);
//    system("< infile grep ab | wc -l -c > expected");
//    ASSERT_EQ(system("diff actual expected"), 0);
//}
