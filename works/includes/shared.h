/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:03:07 by ahayashi          #+#    #+#             */
/*   Updated: 2022/02/06 13:03:07 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"
# include "typedefs.h"
# include "xlibft.h"
# include "xsyscall.h"

int		exec_pipex(t_pipex *pipex);
char	*get_fullpath(char *file_name, char **env);

#endif
