/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 02:02:30 by ahayashi          #+#    #+#             */
/*   Updated: 2021/10/09 02:03:02 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (n == 0 || dst == src)
		return (dst);
	while (n-- > 0)
		((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
	return (dst);
}
