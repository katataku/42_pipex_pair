#include "pipex.h"

int	is_valid_args(int argc, char **argv)
{
	(void)argv;
	return (argc == 5);
}

void	replace_fd(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
	{
		perror("dup2");
		exit (ERR_CODE_GENERAL);
	}
	if (close(old_fd) < 0)
	{
		perror("close");
		exit (ERR_CODE_GENERAL);
	}
}

char	*get_command(char *file_name, char **env)
{
	int		index;
	char	**path;
	char	*fullpath;
	char	*file_name_with_slash;
	int		access_check;

	index = 0;
	if (ft_strchr(file_name, '/') != NULL)
	{
		return (file_name);
	}
	while (1)
	{
		if (env[index] == NULL)
			return (NULL);
		if (ft_strncmp("PATH=", env[index], 5) == 0)
			break ;
		index++;
	}
	path = ft_split(env[index] + 5, ':');
	file_name_with_slash = ft_strjoin("/", file_name);
	if (file_name_with_slash == NULL)
	{
		exit (ERR_CODE_GENERAL);
	}
	index = 0;
	while (path[index] != NULL)
	{
		fullpath = ft_strjoin(path[index], file_name_with_slash);
		if (fullpath == NULL)
		{
			exit(1);
		}
		access_check = access(fullpath, F_OK);
		if (access_check == 0)
		{
			free(file_name_with_slash);
			return (fullpath);
		}
		free(fullpath);
		index++;
	}
	write(2, "commnd not found ", 15);
	exit(ERR_CODE_COMMAND_NOT_FOUND);
}

void	exec_child(char *path, char **env, int read_fd, int write_fd)
{
	char	**argv;
	char	*command;

	argv = ft_split(path, ' ');
	replace_fd(read_fd, 0);
	replace_fd(write_fd, 1);
	command = get_command(argv[0], env);
	execve(command, argv, env);
	perror("execve");
	exit(0);
}

int	pipex(int argc, char **argv, char **env)
{
	pid_t	pid[2];
	int		filedes[2];
	int		fd;
	int		status[2];

	(void)argc;
	pipe(filedes);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror(argv[1]);
			exit(1); // 終了ステータス127かもあってる？
		}
		exec_child(argv[2], env, fd, filedes[WRITE_INDEX]);
	}
	close(filedes[WRITE_INDEX]);
	pid[1] = fork();
	if (pid[1] == 0)
	{
		fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
		{
			perror(argv[4]);
			exit(1);
		}
		exec_child(argv[3], env, filedes[READ_INDEX], fd);
	}
	close(filedes[READ_INDEX]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	return (status[1]);
}

/* タスクリスト
Next: 
- システムコールのエラーハンドリング
	* fork
	* pipe
	* close
	* waitpid
	* access
- 文字列関数のallocateエラー
	* ft_splitなどのNULLのケース
- 提出に向けてnorm対応
- 追記：ファイルのopenに失敗したときの終了ステータスが違うかも。1ではなく127

方針：
	関数を意味ある単位に分割して真正面からシステムコールと対峙する。
	辛くなったらシステムコールのラッパー関数で逃げる。

## 異常系
- 子プロセスが異常した時のハンドリング
- コマンドが見つからないケース
get_commandの異常系。
- 異常系の動作確認も踏まえて
- PATHがない場合 bash: ./fasdfa: No such file or directory
- コマンドが見つからない場合 bash: ojoa: command not found

終了ステータス
126	コマンドを実行できなかった（実行権限がなかった）
127	コマンドが見つからなかった
*/