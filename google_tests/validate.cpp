#include <gtest/gtest.h>

extern "C" {
#include "pipex.h"
#include "pipex_bonus.h"
}

TEST(Validate, valid)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", "actual", NULL};

	ASSERT_EQ(is_valid_args(argc, argv), 1);
}

TEST(Validate, args_short)
{
    int argc = 4;
    char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", NULL};

    ASSERT_EQ(is_valid_args(argc,argv), 0);
}

TEST(Validate, args_long)
{
    int argc = 6;
    char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", "actual", "actual2", NULL};

    ASSERT_EQ(is_valid_args(argc,argv), 0);
}

TEST(Validate_Bonus, valid_mandatory)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", "actual", NULL};

	ASSERT_EQ(is_valid_args_bonus(argc, argv), 1);
}

TEST(Validate_Bonus, valid_long)
{
    int argc = 7;
    char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", "/bin/pwd", "/bin/pwd", "actual", NULL};

    ASSERT_EQ(is_valid_args_bonus(argc,argv), 1);
}

TEST(Validate_Bonus, args_short)
{
    int argc = 4;
    char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", NULL};

    ASSERT_EQ(is_valid_args_bonus(argc,argv), 0);
}

TEST(Validate_Bonus, valid_heredoc)
{
    int argc = 6;
    char *argv[] = {"./main", "here_doc", "LIMITER", "/bin/pwd", "/bin/pwd", "actual", NULL};

    ASSERT_EQ(is_valid_args_bonus(argc,argv), 1);
}

TEST(Validate_Bonus, args_short_heredoc)
{
    int argc = 5;
    char *argv[] = {"./main", "here_doc", "/bin/pwd", "/bin/pwd", "actual", NULL};

    ASSERT_EQ(is_valid_args_bonus(argc,argv), 0);
}

TEST(Validate_Bonus, valid_long_heredoc)
{
    int argc = 8;
    char *argv[] = {"./main", "here_doc", "LIMITER", "/bin/pwd", "/bin/pwd", "/bin/pwd", "/bin/pwd", "actual", NULL};

    ASSERT_EQ(is_valid_args_bonus(argc,argv), 1);
}
