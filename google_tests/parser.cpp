#include <gtest/gtest.h>

extern "C" {
#include "pipex.h"
#include "pipex_bonus.h"
}

class ParserBonusTest : public ::testing::Test {
protected:
	static void SetUpTestCase() {}
	static void TearDownTestCase() {}
	t_pipex *pipex;

	virtual void SetUp() {}
	virtual void TearDown() {
		free(pipex);
	}
};

TEST(ParserTest, normal)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", "actual", NULL};

	t_pipex *pipex;
	pipex = parse_args_bonus(argc, argv, NULL);
	ASSERT_EQ(pipex->start, 2);
	ASSERT_EQ(pipex->end, 3);
	ASSERT_EQ(pipex->delimiter, -1);
	ASSERT_EQ(pipex->src, 1);
	ASSERT_EQ(pipex->dst, 4);
	ASSERT_EQ(pipex->o_flag, O_WRONLY | O_CREAT | O_TRUNC);
	free(pipex);
}

TEST_F(ParserBonusTest, equal_to_mandatory)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", "actual", NULL};

	pipex = parse_args_bonus(argc, argv, NULL);
	ASSERT_EQ(pipex->start, 2);
	ASSERT_EQ(pipex->end, 3);
	ASSERT_EQ(pipex->delimiter, -1);
	ASSERT_EQ(pipex->src, 1);
	ASSERT_EQ(pipex->dst, 4);
	ASSERT_EQ(pipex->o_flag, O_WRONLY | O_CREAT | O_TRUNC);
}


TEST_F(ParserBonusTest, multiple_pipes)
{
	int argc = 8;
	char *argv[] = {"./main", "infile", "/bin/pwd", "/bin/pwd", "/bin/pwd", "/bin/pwd", "/bin/pwd", "actual", NULL};

	pipex = parse_args_bonus(argc, argv, NULL);
	ASSERT_EQ(pipex->start, 2);
	ASSERT_EQ(pipex->end, 6);
	ASSERT_EQ(pipex->delimiter, -1);
	ASSERT_EQ(pipex->src, 1);
	ASSERT_EQ(pipex->dst, 7);
	ASSERT_EQ(pipex->o_flag, O_WRONLY | O_CREAT | O_TRUNC);
}

TEST_F(ParserBonusTest, here_doc)
{
	int argc = 6;
	char *argv[] = {"./main", "here_doc", "LIMITER", "/bin/pwd", "/bin/pwd", "actual", NULL};

	pipex = parse_args_bonus(argc, argv, NULL);
	ASSERT_EQ(pipex->start, 3);
	ASSERT_EQ(pipex->end, 4);
	ASSERT_EQ(pipex->delimiter, 2);
	ASSERT_EQ(pipex->src, -1);
	ASSERT_EQ(pipex->dst, 5);
	ASSERT_EQ(pipex->o_flag, O_WRONLY | O_CREAT | O_TRUNC);
}

TEST_F(ParserBonusTest, here_doc_multiple_pipes)
{
	int argc = 8;
	char *argv[] = {"./main", "here_doc", "LIMITER", "/bin/pwd", "/bin/pwd", "/bin/pwd", "/bin/pwd", "actual", NULL};

	pipex = parse_args_bonus(argc, argv, NULL);
	ASSERT_EQ(pipex->start, 3);
	ASSERT_EQ(pipex->end, 6);
	ASSERT_EQ(pipex->delimiter, 2);
	ASSERT_EQ(pipex->src, -1);
	ASSERT_EQ(pipex->dst, 7);
	ASSERT_EQ(pipex->o_flag, O_WRONLY | O_CREAT | O_TRUNC);
}
