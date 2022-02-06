/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xwaitpid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:33:26 by ahayashi          #+#    #+#             */
/*   Updated: 2022/01/20 23:33:26 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

pid_t	xwaitpid(pid_t pid, int *stat_loc, int options)
{
	pid_t	ret;

	ret = waitpid(pid, stat_loc, options);
	if (ret == -1)
	{
		perror("waitpid");
		exit(ERR_CODE_GENERAL);
	}
	return (ret);
}
