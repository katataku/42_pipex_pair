#include "pipex.h"

void	safely_dup(int fd, int tar_fd)
{
	if (dup2(fd, tar_fd) < 0)
	{
		perror("dup2");
		exit (1);
	}
	if (close(fd) < 0)
	{
		perror("close");
		exit (1);
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
		exit (1);
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
	exit(1);
}

//char*	get_command (file_name, env)
//{
//	//errorはexit

//	// 例外ケース。PATHがない。
//	// envからPATHを探す
//	int	index = 0;
//	while (True)
//	{
//		if (env[i] == NULL)
//			return 'ありまえｓん'
//		if (ft_strncmp("PATH=", env[i], 5);
//			break;
//		i++;
//		env[i] + 5
//	}
//	// PATHを分割
//	path = ft_split(env[i]+5, ':');
//	i = 0;
//	while (path[i] != NULL)
//	{
//		// PATHとコマンドをくっつける
//		fullpath = ft_strjoin(path[i],file_name);
//		// accessをつかって権限やファイルなどがあるか
//		access(fullpath,XX);
//		if (OK)
//			return 
//		return get_command(filename,next(env));
//	}
//}

void	exec_child(char *path, char **env, int read_fd, int write_fd)
{
	char	**argv;
	char	*command;

	argv = ft_split(path, ' ');
	safely_dup(read_fd, 0);
	safely_dup(write_fd, 1);
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
			exit(1);
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

## 正常系
- check_args関数を作成する。
	- 引数が足りない。
	- 引数が多い。

## 検証
- 環境変数にPATHがない場合(検証が大変そう)
- 「ファイルアクセスのエラー」と「execveのエラー」のエラー、どちらのエラーを出力するかの優先順位

## テストケース
- setup/teardownの作成
- 高優先度のパスにpermissionあり
- 高優先度のパスにpermissionなし
- 低優先度のパスにpermissionあり
- 低優先度のパスにpermissionなし

## 異常系
- 子プロセスが異常した時のハンドリング
- コマンドが見つからないケース
- システムコールのエラーハンドリング
	- fork
	- e.t.c.
get_commandの異常系。
- 異常系の動作確認も踏まえて
- PATHがない場合 bash: ./fasdfa: No such file or directory
- コマンドが見つからない場合 bash: ojoa: command not found
*/