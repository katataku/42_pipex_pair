/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:32:38 by ahayashi          #+#    #+#             */
/*   Updated: 2022/02/06 02:30:06 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex		*pipex;
	int			status;

	if (!is_valid_args(argc, argv))
		return (ERR_CODE_GENERAL);
	pipex = parse_args(argc, argv, envp);
	status = exec_pipex(pipex);
	return (status);
}
