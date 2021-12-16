/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:27:59 by ahayashi          #+#    #+#             */
/*   Updated: 2021/10/09 19:28:01 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;

	cc = (char)c;
	while (1)
	{
		if (*s == cc)
			return ((char *)s);
		if (*s == '\0')
			return (NULL);
		s++;
	}
}
