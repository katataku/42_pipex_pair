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
	perror(command);
	exit(0);
}

int	pipex(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		filedes [2];
	int		fd;

	fd = open(argv[1], O_RDWR, S_IREAD);
	pipe(filedes);
	pid = fork();
	if (pid == 0)
		exec_child(argv[2], env, fd, filedes[WRITE_INDEX]);
	close(filedes[WRITE_INDEX]);
	fd = open(argv[4], O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
	pid = fork();
	if (pid == 0)
		exec_child(argv[3], env, filedes[READ_INDEX], fd);
	return (0);
}

/*
int pipex(void)
{
    do_command(command,in_fd, out_fd);   
    retudorn (0);

}

*/

/*
int main(argc, argv,env)
{
    if (check_args(argc,argv,env) == -1)
        return (-1);
    return pipex(argc,argv,env);    
}*/

/* タスクリスト

## 検証
- waitが効いていない（問題になるまで放置）

## テストケース
- setup/teardownの作成
- 高優先度のパスにpermissionあり
- 高優先度のパスにpermissionなし
- 低優先度のパスにpermissionあり
- 低優先度のパスにpermissionなし
- ./ls


## 正常系
- fdのクローズ(そのためにwait)

## 異常系
- file2が存在しない場合
- 作られるファイルのパーミッションをあわせる
- 子プロセスが異常した時のハンドリング
*/