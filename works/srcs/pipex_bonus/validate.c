/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 00:33:21 by ahayashi          #+#    #+#             */
/*   Updated: 2022/02/06 00:33:21 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_valid_args_bonus(int argc, char **argv)
{
	if (argc < 5)
		return (0);
	if (ft_strcmp("here_doc", argv[1]) == 0 && argc < 6)
		return (0);
	return (1);
}
