#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	//if (check_args(argc,argv,env) == -1)
	//    return (-1);
	return (pipex(argc, argv, env));
}
