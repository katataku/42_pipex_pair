/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:16:09 by ahayashi          #+#    #+#             */
/*   Updated: 2021/10/09 22:16:19 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*memo;
	char	cc;

	cc = (char)c;
	memo = NULL;
	while (1)
	{
		if (*s == cc)
			memo = (char *)s;
		if (*s == '\0')
			return (memo);
		s++;
	}
}
