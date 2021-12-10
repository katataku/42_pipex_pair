#include "pipex.h"

int	pipex(int argc, char **argv, char **env)
{
	pid_t pid;
	pid_t wait_pid;
	int	status_expect;
	int filedes [2];
	int	fd;
	char *test_argv[] = {"./a.out"};
	//char	*buf = calloc(1,100);
	unsigned int buf[100];

	pipe(filedes);
	pid = fork();
	if (pid == 0)
	{
		close(filedes[0]);
		dup2(filedes[1] , 1);
		dup2(filedes[1] , 2);
		execve("/bin/pwd", test_argv, env);
		exit(0);
	}
	else
	{
		close(filedes[1]);
		wait_pid = wait(&status_expect);
		read(filedes[0], buf, 100);
		fd = open("actual", O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
		printf("%s\n", buf);
		//write(fd, buf, 100);
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
## 正常系
- lsで渡されてきたら/user/bin/lsみたいにパス解決
- 引数を分割して渡してあげる
- 
## 異常系
- file2が存在しない場合
- 作られるファイルのパーミッションをあわせる
*/