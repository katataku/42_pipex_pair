#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <unistd.h> 

int	pipex(int argc, char **argv, char **env);

#endif
