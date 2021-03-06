#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <string.h>
# include "xsyscall.h"
# define READ_INDEX 0
# define WRITE_INDEX 1

# define ERR_CODE_GENERAL 1
# define ERR_CODE_CAN_NOT_EXECUTE 126
# define ERR_CODE_COMMAND_NOT_FOUND 127

char	*get_fullpath(char *file_name, char **env);
int		pipex(int argc, char **argv, char **env);
int		is_valid_args(int argc, char **argv);

char	*ft_xstrjoin(const char *s1, const char *s2);
char	*ft_xstrdup(const char *s);
char	**ft_xsplit(const char *s, char c);
char	*ft_xcalloc(size_t count, size_t size);

#endif
