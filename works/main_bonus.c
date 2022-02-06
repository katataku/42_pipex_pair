/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:51:20 by ahayashi          #+#    #+#             */
/*   Updated: 2022/02/06 00:43:09 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex		*pipex;
	int			status;

	if (!is_valid_args_bonus(argc, argv))
		return (ERR_CODE_GENERAL);
	pipex = parse_args_bonus(argc, argv, envp);
	status = exec_pipex(pipex);
	return (status);
}
