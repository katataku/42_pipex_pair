/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:14:03 by ahayashi          #+#    #+#             */
/*   Updated: 2022/02/06 01:00:47 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init(t_pipex *pipex)
{
	pipex->start = -1;
	pipex->end = -1;
	pipex->delimiter = -1;
	pipex->src = -1;
	pipex->dst = -1;
	pipex->o_flag = O_WRONLY | O_CREAT | O_TRUNC;
	pipex->argv = NULL;
	pipex->envp = NULL;
}

// writeのモードについてもやりたい
// 事前にバリデーションされている前提
t_pipex	*parse_args_bonus(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)ft_xcalloc(1, sizeof(t_pipex));
	init(pipex);
	if (ft_strcmp("here_doc", argv[1]) == 0)
	{
		pipex->delimiter = 2;
		pipex->start = 3;
	}
	else
	{
		pipex->src = 1;
		pipex->start = 2;
	}
	pipex->end = argc - 2;
	pipex->dst = argc - 1;
	pipex->argv = argv;
	pipex->envp = envp;
	return (pipex);
}
