
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
			path = ft_strjoin(envp[i] + 5, "/usr/bin:/bin");// error handling > good
			if (!path)
			{
				perror("malloc");
				exit(OUT_OF_MEMORY);
			}
			break ;
		}
		i++;
	}
	path_f = ft_split(path, ':');// error handling > good
	if (!path_f)
	{
		perror("malloc");
		exit(OUT_OF_MEMORY);
	}
	free(path);
	return (path_f);
}

void	reset_and_free(t_exec *data, t_parsing *parsing)
{
	if (dup2(data->stdin_cpy, STDIN_FILENO) == -1)// error handling > good
	{
		perror("dup2");
		exit(OUT_OF_MEMORY);
	}
	if (dup2(data->stdout_cpy, STDOUT_FILENO) == -1)// error handling > good
	{
		perror("dup2");
		exit(OUT_OF_MEMORY);
	}
	close(data->stdin_cpy);
	close(data->stdout_cpy);
	ft_free_data(data, parsing);
}