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

int	pipex(int argc, char **argv, char **env)
{
	pid_t	pid;
	pid_t	wait_pid;
	int		status_expect;
	int		filedes [2];
	int		filedes2 [2];
	int		fd;
	int		read_bytes;
	char	*test_argv[] = {"./a.out", NULL};
	char	buf[100];

	pipe(filedes2);
	pid = fork();
	if (pid == 0)
	{
		fd = open(argv[1], O_RDWR, S_IREAD);
		safely_dup(fd, 0);
		close(filedes2[READ_INDEX]);
		safely_dup(filedes2[WRITE_INDEX], 1);
		execve(argv[2], test_argv, env);
		perror("execve");
		exit(0);
	}
	close(filedes2[WRITE_INDEX]);
	pipe(filedes);
	pid = fork();
	if (pid == 0)
	{
		safely_dup(filedes2[READ_INDEX], 0);
		close(filedes[READ_INDEX]);
		safely_dup(filedes[WRITE_INDEX], 1);
		execve(argv[3], test_argv, env);
		perror("execve");
		exit(0);
	}
	else
	{
		close(filedes[WRITE_INDEX]);
		fd = open(argv[4], O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
		while (1)
		{
			read_bytes = read(filedes[READ_INDEX], buf, 100);
			if (read_bytes > 0)
				write(fd, buf, read_bytes);
			else
				break ;
		}
		close(filedes[READ_INDEX]);
	}
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