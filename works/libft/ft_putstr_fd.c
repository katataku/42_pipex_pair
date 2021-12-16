/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:59:23 by ahayashi          #+#    #+#             */
/*   Updated: 2021/11/16 19:28:42 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return (-1);
	len = ft_strlen(s);
	return (write(fd, s, len));
}
