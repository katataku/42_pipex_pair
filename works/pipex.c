#include "pipex.h"

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
		close(filedes2[READ_INDEX]);
		dup2(filedes2[WRITE_INDEX], 1);
		close(filedes2[WRITE_INDEX]);
		execve(argv[2], test_argv, env);
		perror("execve");
		exit(0);
	}
	close(filedes2[WRITE_INDEX]);
	pipe(filedes);
	pid = fork();
	if (pid == 0)
	{
		dup2(filedes2[READ_INDEX], 0);
		close(filedes2[READ_INDEX]);
		close(filedes[READ_INDEX]);
		dup2(filedes[WRITE_INDEX], 1);
		close(filedes[WRITE_INDEX]);
		execve(argv[3], test_argv, env);
		perror("execve");
		exit(0);
	}
	else
	{
		close(filedes[WRITE_INDEX]);
		fd = open("actual", O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
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
- lsで渡されてきたら/user/bin/lsみたいにパス解決
- 引数を分割して渡してあげる
- 
## 異常系
- file2が存在しない場合
- 作られるファイルのパーミッションをあわせる
*/