#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# define READ_INDEX 0
# define WRITE_INDEX 1

char*	get_command(char *file_name,char **env);
int	pipex(int argc, char **argv, char **env);

#endif
