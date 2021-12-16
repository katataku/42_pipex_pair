/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:47:45 by ahayashi          #+#    #+#             */
/*   Updated: 2021/10/12 12:47:46 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calc_digits(int n)
{
	int	num;

	num = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		num++;
	}
	return (num);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	int		is_minus;
	int		digits;
	char	*ptr;

	if (n < 0)
		is_minus = 1;
	else
		is_minus = 0;
	digits = ft_calc_digits(n);
	ptr = malloc(digits + is_minus + 1);
	if (ptr == NULL)
		return (NULL);
	if (is_minus)
		ptr[0] = '-';
	ptr[digits + is_minus] = '\0';
	while (digits > 0)
	{
		ptr[digits + is_minus - 1] = '0' + ft_abs(n % 10);
		n /= 10;
		digits--;
	}
	return (ptr);
}
