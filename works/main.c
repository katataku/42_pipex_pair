#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	status;

	if (!is_valid_args(argc, argv))
		return (ERR_CODE_GENERAL);
	status = pipex(argc, argv, env);
	return (status);
}
