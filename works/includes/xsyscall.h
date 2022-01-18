#ifndef XSYSCALL_H
# define XSYSCALL_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

int	xopen(const char *path, int oflag, int mode);
#endif
