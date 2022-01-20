#include "pipex.h"

char	*ft_xstrjoin(const char *s1, const char *s2)
{
	char	*fullpath;

	fullpath = ft_strjoin(s1, s2);
	if (fullpath == NULL)
	{
		perror("malloc");
		exit(ERR_CODE_GENERAL);
	}
	return (fullpath);
}

char	*ft_xstrdup(const char *s)
{
	char	*tmp;

	tmp = ft_strdup(s);
	if (tmp == NULL)
	{
		perror("malloc");
		exit(ERR_CODE_GENERAL);
	}
	return (tmp);
}

char	**ft_xsplit(const char *s, char c)
{
	char	**tmp;

	tmp = ft_split(s, c);
	if (tmp == NULL)
	{
		perror("malloc");
		exit(ERR_CODE_GENERAL);
	}
	return (tmp);
}

char	*ft_xcalloc(size_t count, size_t size)
{
	char	*tmp;

	tmp = ft_calloc(count, size);
	if (tmp == NULL)
	{
		perror("malloc");
		exit(ERR_CODE_GENERAL);
	}
	return (tmp);
}
