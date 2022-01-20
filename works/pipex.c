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

char	*ft_xsplit(const char *s, char c)
{
	char	*tmp;

	tmp = ft_split(s, c);
	if (tmp == NULL)
	{
		perror("malloc");
		exit(ERR_CODE_GENERAL);
	}
	return (tmp);
}

char	*ft_xcalloc(size_t count, size_t size)
{
	char	*tmp;

	tmp = ft_calloc(count, size);
	if (tmp == NULL)
	{
		perror("malloc");
		exit(ERR_CODE_GENERAL);
	}
	return (tmp);
}

void	puterr_exit(char *target, char *message, int exit_status)
{
	if (ft_putstr_fd(target, 2) == -1)
		exit(ERR_CODE_GENERAL);
	if (ft_putstr_fd(": ", 2) == -1)
		exit(ERR_CODE_GENERAL);
	if (ft_putstr_fd(message, 2) == -1)
		exit(ERR_CODE_GENERAL);
	if (ft_putstr_fd("\n", 2) == -1)
		exit(ERR_CODE_GENERAL);
	exit(exit_status);
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
			path = (char **)ft_xcalloc(1, sizeof(char *));
			break ;
		}
		if (ft_strncmp("PATH=", env[index], 5) == 0)
		{
			path = ft_xsplit(env[index] + 5, ':');
			break ;
		}
		index++;
	}
	return (path);
}

char	*get_fullpath_find_from_path(char	*filepath)
{
	if (access(filepath, X_OK) == 0)
			return (filepath);
		if (access(filepath, F_OK) == 0)
			puterr_exit(filepath, strerror(EACCES), ERR_CODE_CAN_NOT_EXECUTE);
		perror(filepath);
		exit(ERR_CODE_COMMAND_NOT_FOUND);
}

char	*get_fullpath_find_from_command(char **path, char *file_name)
{
	int		index;
	char	*fullpath;
	char	*file_name_with_slash;
	char	*found_filepath;

	index = 0;
	found_filepath = NULL;
	file_name_with_slash = ft_xstrjoin("/", file_name);
	while (path[index] != NULL)
	{
		fullpath = ft_xstrjoin(path[index], file_name_with_slash);
		if (access(fullpath, X_OK) == 0)
			return (fullpath);
		if (found_filepath == NULL && access(fullpath, F_OK) == 0)
			found_filepath = ft_xstrdup(fullpath);
		index++;
	}
	if (found_filepath != NULL)
		puterr_exit(found_filepath, strerror(EACCES), ERR_CODE_CAN_NOT_EXECUTE);
	else
		puterr_exit(file_name, "command not found", ERR_CODE_COMMAND_NOT_FOUND);
	return (NULL);	
}
	
char	*get_fullpath(char *file_name, char **env)
{
	char	**path;

	if (ft_strchr(file_name, '/') != NULL)
		return (get_fullpath_find_from_path(file_name));
	path = create_path_lst(env);
	return (get_fullpath_find_from_command(path, file_name));
}

//char	*get_command(char *file_name, char **env)
//{
//	int		index;
//	char	**path;
//	char	*fullpath;
//	char	*file_name_with_slash;
//	char	*found_filepath;

//	if (ft_strchr(file_name, '/') != NULL)
//	{
//		return (get_fullpath_find_from_path(file_name));
//	}
//	path = create_path_lst(env);
//	file_name_with_slash = ft_xstrjoin("/", file_name);
//	index = 0;
//	found_filepath = NULL;
//	while (path[index] != NULL)
//	{
//		fullpath = ft_xstrjoin(path[index], file_name_with_slash);
//		if (access(fullpath, X_OK) == 0)
//			return (fullpath);
//		if (found_filepath == NULL && access(fullpath, F_OK) == 0)
//			found_filepath = ft_xstrdup(fullpath);
//		index++;
//	}
//	if (found_filepath != NULL)
//		puterr_exit(found_filepath, strerror(EACCES), ERR_CODE_CAN_NOT_EXECUTE);
//	else
//		puterr_exit(file_name, "command not found", ERR_CODE_COMMAND_NOT_FOUND);
//	return (NULL);
//}

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