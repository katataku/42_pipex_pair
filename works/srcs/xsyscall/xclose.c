/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:33:07 by ahayashi          #+#    #+#             */
/*   Updated: 2022/01/20 23:33:44 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

int	xclose(int fildes)
{
	int	status;

	status = close(fildes);
	if (status == -1)
	{
		perror("close");
		exit(ERR_CODE_GENERAL);
	}
	return (status);
}
