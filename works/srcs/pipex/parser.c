/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:21:04 by ahayashi          #+#    #+#             */
/*   Updated: 2022/02/06 02:21:04 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*parse_args(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	(void)argc;
	pipex = (t_pipex *)ft_xcalloc(1, sizeof(t_pipex));
	pipex->start = 2;
	pipex->end = 3;
	pipex->delimiter = -1;
	pipex->src = 1;
	pipex->dst = 4;
	pipex->o_flag = O_WRONLY | O_CREAT | O_TRUNC;
	pipex->argv = argv;
	pipex->envp = envp;
	return (pipex);
}
