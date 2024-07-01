
#include "../../includes/minishell.h"

void	malloc_error(void)
{
	perror("malloc");
	exit(OUT_OF_MEMORY);
}

bool	there_is_pipeline(int *tkn_value)
{
	int	i;

	i = -1;
	while (tkn_value[++i])
	{
		if (tkn_value[i] == PIPE)
			return (TRUE);
	}
	return (FALSE);
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
			{
				PL;
				malloc_error();
			}
			break ;
		}
		i++;
	}
	path_f = ft_split(path, ':');// error handling > good
	if (!path_f)
	{
		PL;
		malloc_error();
	}
	free(path);
	return (path_f);
}
