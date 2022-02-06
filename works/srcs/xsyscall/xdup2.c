/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:33:11 by ahayashi          #+#    #+#             */
/*   Updated: 2022/01/20 23:33:11 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

int	xdup2(int fildes, int fildes2)
{
	int	status;

	status = dup2(fildes, fildes2);
	if (status == -1)
	{
		perror("dup2");
		exit(ERR_CODE_GENERAL);
	}
	return (status);
}
