
#include "../../includes/minishell.h"

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
			path = ft_strjoin(envp[i] + 5, "/usr/bin:/bin");
			break ;// error handling
		}
		i++;
	}
	path_f = ft_split(path, ':');// error handling
	free(path);
	return (path_f);
}
