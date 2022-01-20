#include "pipex.h"

int	is_valid_args(int argc, char **argv)
{
	(void)argv;
	return (argc == 5);
}

void	replace_fd(int old_fd, int new_fd)
{
	xdup2(old_fd, new_fd);
	xclose(old_fd);
}

void	exec_child(char *path, char **env, int read_fd, int write_fd)
{
	char	**argv;
	char	*command;

	argv = ft_xsplit(path, ' ');
	replace_fd(read_fd, 0);
	replace_fd(write_fd, 1);
	command = get_fullpath(argv[0], env);
	execve(command, argv, env);
	perror("execve");
	exit(ERR_CODE_GENERAL);
}

int	pipex(int argc, char **argv, char **env)
{
	pid_t	pid[2];
	int		filedes[2];
	int		fd;
	int		status[2];

	(void)argc;
	xpipe(filedes);
	pid[0] = xfork();
	if (pid[0] == 0)
	{
		xclose(filedes[READ_INDEX]);
		fd = xopen(argv[1], O_RDONLY, 0);
		exec_child(argv[2], env, fd, filedes[WRITE_INDEX]);
	}
	xclose(filedes[WRITE_INDEX]);
	pid[1] = xfork();
	if (pid[1] == 0)
	{
		fd = xopen(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		exec_child(argv[3], env, filedes[READ_INDEX], fd);
	}
	xclose(filedes[READ_INDEX]);
	xwaitpid(pid[0], &status[0], 0);
	xwaitpid(pid[1], &status[1], 0);
	return (status[1]);
}

/* タスクリスト
Next: 
- get_commandの分割
- 文字列関数のallocateエラー
	* ft_splitなどのNULLのケース
- 提出に向けてnorm対応
- メモリリークのチェック
*/