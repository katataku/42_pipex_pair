/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:33:18 by ahayashi          #+#    #+#             */
/*   Updated: 2022/01/20 23:33:18 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

int	xopen(const char *path, int oflag, int mode)
{
	int	fd;

	fd = open(path, oflag, mode);
	if (fd < 0)
	{
		perror(path);
		exit(ERR_CODE_GENERAL);
	}
	return (fd);
}
