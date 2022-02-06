/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xsyscall.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:34:00 by ahayashi          #+#    #+#             */
/*   Updated: 2022/01/20 23:34:00 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XSYSCALL_H
# define XSYSCALL_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "typedefs.h"

int		xopen(const char *path, int oflag, int mode);
pid_t	xwaitpid(pid_t pid, int *stat_loc, int options);
int		xclose(int fildes);
int		xpipe(int fildes[2]);
pid_t	xfork(void);
int		xdup2(int fildes, int fildes2);
#endif
