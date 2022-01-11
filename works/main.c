#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (!is_valid_args(argc, argv))
		return (1);
	return (pipex(argc, argv, env));
}
