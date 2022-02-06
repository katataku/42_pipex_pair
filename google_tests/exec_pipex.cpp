#include <gtest/gtest.h>

extern "C" {
#include "pipex.h"
#include "pipex_bonus.h"
}

char *envp[] = {
		"LANG=ja_JP.UTF-8",
		"HOME=/Users/hayashi-ay",
		"SHELL=/bin/bash",
		"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
		"COLORTERM=truecolor",
		NULL
	};

class ExecPipexTest : public ::testing::Test {
protected:
	static void SetUpTestCase() {}
	static void TearDownTestCase() {}
	t_pipex	*pipex;
	int actual_status_code;
	int expect_status_code;
	std::string expect_stderr;
	std::string actual_stderr;

	virtual void SetUp() {
		system("echo bc > infile");
		system("echo ab >> infile");
	}
	virtual void TearDown() {
		unlink("actual");
		unlink("expected");
		free(pipex);
	}
	std::string build_cmd(t_pipex *pipex);
	void do_exec_pipes(t_pipex *pipex);
	void do_exec_pipes(t_pipex *pipex, std::string cmd);
};

std::string ExecPipexTest::build_cmd(t_pipex *pipex) {
	std::string cmd;

	cmd = "< ";
	cmd += pipex->argv[pipex->src];
	for (int i = 0; pipex->start + i <= pipex->end; i++)
	{
		if (i != 0)
			cmd += " | ";
		else
			cmd += " ";
		cmd += pipex->argv[ pipex->start + i];
	}
	cmd += " > expected";
	return (cmd);
}

void ExecPipexTest::do_exec_pipes(t_pipex *pipex) {
	std::string cmd;

	cmd = build_cmd(pipex);
	do_exec_pipes(pipex, cmd);
}

void ExecPipexTest::do_exec_pipes(t_pipex *pipex, std::string cmd) {
	testing::internal::CaptureStderr();
	actual_status_code = exec_pipex(pipex);
	actual_stderr = testing::internal::GetCapturedStderr();
	testing::internal::CaptureStderr();
	expect_status_code = system(cmd.c_str());
	expect_stderr = testing::internal::GetCapturedStderr();

	ASSERT_EQ(system("diff actual expected"), 0);
	ASSERT_EQ(actual_status_code, expect_status_code);
	if (!actual_stderr.empty() || !expect_stderr.empty()) {
		ASSERT_EQ(actual_stderr, expect_stderr.substr(4, size(expect_stderr)));
	}
}

TEST_F(ExecPipexTest, normal)
{
    int argc = 5;
    char *argv[] = {"./main", "infile", "/usr/bin/grep ab", "/usr/bin/wc -l -c", "actual", NULL};

    pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, resolve_path)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "grep ab", "wc -l -c", "actual", NULL};

	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, last_is_true)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/usr/bin/false", "/usr/bin/true", "actual", NULL};

	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, last_is_false)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/usr/bin/true", "/usr/bin/false", "actual", NULL};

	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, infile_is_not_exist)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/bin/ls", "/bin/cat", "actual", NULL};

	unlink("infile");
	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, outfile_is_not_exist)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/bin/ls", "/bin/cat", "vacant/outfile", NULL};
	std::string cmd = "< infile ls | cat > vacant/outfile";

	// actualとexpectedの比較処理を回避するために同じ内容で作成
	system("echo aa > actual");
	system("echo aa > expected");
	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex, cmd);
}

TEST_F(ExecPipexTest, newly_created_permission)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "cat", "cat", "actual", NULL};

	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
	// 権限についても確認
	system("ls -l actual | awk '{print $1}' > actual_permission");
	system("ls -l expected | awk '{print $1}'> expect_permission");
	ASSERT_EQ(system("diff actual_permission expect_permission"), 0);
	system("unlink actual_permission");
	system("unlink expect_permission");
}

TEST_F(ExecPipexTest, command_not_found)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "cat", "dog", "actual", NULL};

	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, filepath_not_found)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "cat", "./dog", "actual", NULL};

	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, command_not_executed)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "cat", "dog", "actual", NULL};

	// catからwrite権限を取り除く
	system("cp /bin/cat dog");
	system("chmod 644 dog");
	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
	// copyしてきたファイルを削除
	system("rm dog");
}

TEST_F(ExecPipexTest, filtpath_not_executed)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "cat", "./dog", "actual", NULL};

	// catからwrite権限を取り除く
	system("cp /bin/cat dog");
	system("chmod 644 dog");
	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
	// copyしてきたファイルを削除
	system("rm dog");
}

TEST_F(ExecPipexTest, first_is_not_executable)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/bin/cat", "cat2", "actual", NULL};
	char *env[] = {
		"SHELL=/bin/bash",
		"PATH=/tmp/first:/tmp/second",
		NULL
	};
	std::string cmd = "PATH='/tmp/first:/tmp/second' ; < infile /bin/cat | cat2 > expected";

	// /tmp/first/cat2と/tmp/second/cat2を作成し、前者から実行権限を除く
	system("mkdir /tmp/first");
	system("mkdir /tmp/second");
	system("cp /bin/cat /tmp/first/cat2");
	system("chmod 644 /tmp/first/cat2");
	system("cp /bin/cat /tmp/second/cat2");
	pipex = parse_args(argc, argv, env);
	do_exec_pipes(pipex, cmd);
	system("rm -rf /tmp/first");
	system("rm -rf /tmp/second");
}

TEST_F(ExecPipexTest, both_are_not_executable)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/bin/cat", "cat2", "actual", NULL};
	char *env[] = {
		"SHELL=/bin/bash",
		"PATH=/tmp/first:/tmp/second",
		NULL
	};
	std::string cmd = "PATH='/tmp/first:/tmp/second' ; < infile /bin/cat | cat2 > expected";

	// /tmp/first/cat2と/tmp/second/cat2を作成し、両者から実行権限を除く
	system("mkdir /tmp/first");
	system("mkdir /tmp/second");
	system("cp /bin/cat /tmp/first/cat2");
	system("chmod 644 /tmp/first/cat2");
	system("cp /bin/cat /tmp/second/cat2");
	system("chmod 644 /tmp/second/cat2");
	pipex = parse_args(argc, argv, env);
	do_exec_pipes(pipex, cmd);
	system("rm -rf /tmp/first");
	system("rm -rf /tmp/second");
}

TEST_F(ExecPipexTest, SIGPIPE_occur)
{
	int argc = 5;
	char *argv[] = {"./main", "/dev/urandom", "cat", "true", "actual", NULL};

	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, larger_than_pipe_buffer)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "cat", "cat", "actual", NULL};

	// パイプバッファの上限は確認したい
	system("python -c \"print('a'* 256 * 256)\" > infile");

	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, overwrite_outfile)
{
    int argc = 5;
    char *argv[] = {"./main", "infile", "cat", "head -1", "actual", NULL};

	// 書き込み対象に予め書き込んでおく
    system("cp infile actual");
    system("cp infile expected");
	pipex = parse_args(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, equal_to_mandatory)
{
	int argc = 5;
	char *argv[] = {"./main", "infile", "/usr/bin/grep ab", "/usr/bin/wc -l -c", "actual", NULL};

	pipex = parse_args_bonus(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, multiple_pipes)
{
	int argc = 6;
	char *argv[] = {"./main", "infile", "cat", "cat", "cat", "actual", NULL};

	pipex = parse_args_bonus(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, pipe_num_is_odd)
{
	int argc = 9;
	char *argv[] = {"./main", "infile", "cat", "cat", "cat", "cat", "cat", "cat", "actual", NULL};

	pipex = parse_args_bonus(argc, argv, envp);
	do_exec_pipes(pipex);
}

TEST_F(ExecPipexTest, pipe_num_is_even)
{
	int argc = 10;
	char *argv[] = {"./main", "infile", "cat", "cat", "cat", "cat", "cat", "cat", "cat", "actual", NULL};

	pipex = parse_args_bonus(argc, argv, envp);
	do_exec_pipes(pipex);
}
