/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:31:41 by ahayashi          #+#    #+#             */
/*   Updated: 2022/02/06 02:31:41 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	replace_fd(int old_fd, int new_fd)
{
	xdup2(old_fd, new_fd);
	xclose(old_fd);
}

static void	do_command(char *path, char **env, int read_fd, int write_fd)
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

/*
 * パイプを閉じる。基本的にはそのループで作成した子プロセスで使用するパイプを閉じる
 */
static void	close_pipes(t_pipex *pipex, int i, int pipes[2][2])
{
	if (i == 0)
	{
		xclose(pipes[0][WRITE_INDEX]);
	}
	else if (pipex->start + i == pipex->end)
	{
		xclose(pipes[(i + 1) % 2][READ_INDEX]);
	}
	else
	{
		xclose(pipes[(i + 1) % 2][READ_INDEX]);
		xclose(pipes[i % 2][WRITE_INDEX]);
	}
}

static void	exec_child(t_pipex *pipex, int i, int pipes[2][2])
{
	int		read_fd;
	int		write_fd;

	if (i == 0)
	{
		xclose(pipes[0][READ_INDEX]);
		read_fd = xopen(pipex->argv[pipex->src], O_RDONLY, 0);
		write_fd = pipes[0][WRITE_INDEX];
	}
	else if (pipex->start + i == pipex->end)
	{
		read_fd = pipes[(i + 1) % 2][READ_INDEX];
		write_fd = xopen(pipex->argv[pipex->dst], pipex->o_flag, 0644);
	}
	else
	{
		xclose(pipes[i % 2][READ_INDEX]);
		read_fd = pipes[(i + 1) % 2][READ_INDEX];
		write_fd = pipes[i % 2][WRITE_INDEX];
	}
	do_command(pipex->argv[pipex->start + i], pipex->envp, read_fd, write_fd);
}

/*
 * パイプは書き手が作る。正確には書き手を生成する直前に親プロセスで作る。
 * 最後のプロセスはpipeには書き込もを行わない。
 * パイプは2つを使い回す。奇数番目のコマンドがpipes[0]を偶数番目のコマンドがpipes[1]を。
 */
int	exec_pipex(t_pipex *pipex)
{
	int	i;
	int	pid;
	int	status;
	int	pipes[2][2];

	i = 0;
	while (pipex->start + i <= pipex->end)
	{
		if (pipex->start + i != pipex->end)
			xpipe(pipes[i % 2]);
		pid = xfork();
		if (pid == 0)
			exec_child(pipex, i, pipes);
		close_pipes(pipex, i, pipes);
		i++;
	}
	xwaitpid(pid, &status, 0);
	return (status);
}
