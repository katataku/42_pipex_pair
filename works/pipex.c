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

char	*ft_xstrjoin(const char *s1, const char *s2)
{
	char	*fullpath;

	fullpath = ft_strjoin(s1, s2);
	if (fullpath == NULL)
	{
		perror("malloc");
		exit(ERR_CODE_GENERAL);
	}
	return (fullpath);
}

char	*ft_xstrdup(const char *s)
{
	char	*tmp;

	tmp = ft_strdup(s);
	if (tmp == NULL)
	{
		perror("malloc");
		exit(ERR_CODE_GENERAL);
	}
	return (tmp);
}

void	puterr(char *target, char *message)
{
	if (ft_putstr_fd(target, 2) == -1)
		exit(ERR_CODE_GENERAL);
	if (ft_putstr_fd(": ", 2) == -1)
		exit(ERR_CODE_GENERAL);
	if (ft_putstr_fd(message, 2) == -1)
		exit(ERR_CODE_GENERAL);
	if (ft_putstr_fd("\n", 2) == -1)
		exit(ERR_CODE_GENERAL);
}

char	**create_path_lst(char **env)
{
	int		index;
	char	**path;

	index = 0;
	while (1)
	{
		if (env[index] == NULL)
		{
			path = (char **)ft_calloc(1, sizeof(char *));
			break ;
		}
		if (ft_strncmp("PATH=", env[index], 5) == 0)
		{
			path = ft_split(env[index] + 5, ':');
			break ;
		}
		index++;
	}
	if (path == NULL)
	{
		perror("malloc");
		exit(ERR_CODE_GENERAL);
	}
	return (path);
}

char	*get_command(char *file_name, char **env)
{
	int		index;
	char	**path;
	char	*fullpath;
	char	*file_name_with_slash;
	int		access_check;
	char	*file_exists;

	if (ft_strchr(file_name, '/') != NULL)
	{
		access_check = access(file_name, X_OK);
		if (access_check == 0)
			return (file_name);
		access_check = access(file_name, F_OK);
		if (access_check == 0)
		{
			puterr(file_name, strerror(EACCES));
			exit(ERR_CODE_CAN_NOT_EXECUTE);
		}
		perror(file_name);
		exit(ERR_CODE_COMMAND_NOT_FOUND);
	}
	path = create_path_lst(env);
	file_name_with_slash = ft_xstrjoin("/", file_name);
	index = 0;
	file_exists = NULL;
	while (path[index] != NULL)
	{
		fullpath = ft_xstrjoin(path[index], file_name_with_slash);
		access_check = access(fullpath, X_OK);
		if (access_check == 0)
		{
			free(file_exists);
			free(file_name_with_slash);
			return (fullpath);
		}
		access_check = access(fullpath, F_OK);
		if (access_check == 0 && file_exists == NULL)
			file_exists = ft_xstrdup(fullpath);
		free(fullpath);
		index++;
	}
	if (file_exists != NULL)
	{
		puterr(file_exists, strerror(EACCES));
		exit(ERR_CODE_CAN_NOT_EXECUTE);
	}
	else
	{
		puterr(file_name, "command not found");
		exit(ERR_CODE_COMMAND_NOT_FOUND);
	}
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