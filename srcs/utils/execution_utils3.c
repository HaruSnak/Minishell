
#include "../../includes/minishell.h"

void	malloc_error()
{
	perror("malloc");
	exit(OUT_OF_MEMORY);
}

char	**ft_path_envp(char **envp)
{
	int		i;
	char	*path;
	char	**path_f;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strjoin(envp[i] + 5, "/usr/bin:/bin");// error handling > good
			if (!path)
				malloc_error();
			break ;
		}
		i++;
	}
	path_f = ft_split(path, ':');// error handling > good
	if (!path_f)
		malloc_error();
	free(path);
	return (path_f);
}
