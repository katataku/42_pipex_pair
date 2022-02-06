/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:33:22 by ahayashi          #+#    #+#             */
/*   Updated: 2022/01/20 23:33:22 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

int	xpipe(int fildes[2])
{
	int	status;

	status = pipe(fildes);
	if (status == -1)
	{
		perror("pipe");
		exit(ERR_CODE_GENERAL);
	}
	return (status);
}
