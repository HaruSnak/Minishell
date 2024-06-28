
#include "../../includes/minishell.h"

void	malloc_error()
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

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
	{
		free(strs[i]);
		strs[i] = NULL;
	}
	free(strs);
}

void	reset_and_free(t_exec *data)
{
	if (dup2(data->stdin_cpy, STDIN_FILENO) == -1)// error handling
	{
		perror("dup22");
		// return ;
	}
	if (dup2(data->stdout_cpy, STDOUT_FILENO) == -1)// error handling
	{
		perror("dup222");
		// return ;
	}
	close(data->stdin_cpy);
	close(data->stdout_cpy);
	free_data(data);
}
