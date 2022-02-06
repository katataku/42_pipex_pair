/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:33:15 by ahayashi          #+#    #+#             */
/*   Updated: 2022/01/20 23:33:15 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

pid_t	xfork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(ERR_CODE_GENERAL);
	}
	return (pid);
}
