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

void	exec_child(char *path, char **env, int read_fd, int write_fd)
{
	char	*test_argv[] = {"./a.out", NULL};

	safely_dup(read_fd, 0);
	safely_dup(write_fd, 1);
	execve(path, test_argv, env);
	perror("execve");
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

## 正常系
- 入力ファイルから読み込みを実装
- lsで渡されてきたら/user/bin/lsみたいにパス解決
- 引数を分割して渡してあげる
- 
## 異常系
- file2が存在しない場合
- 作られるファイルのパーミッションをあわせる
- 子プロセスが異常した時のハンドリング
*/