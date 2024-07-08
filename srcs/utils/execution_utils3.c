
#include "../../includes/minishell.h"

void	malloc_error(char *str)
{
	perror(str);
	exit(OUT_OF_MEMORY);
}

bool	no_such_file(t_parsing *data, char *tkn[], int *tkn_value)
{
	int	i;

	i = -1;
	data->exit_value = 127;
	while (tkn[++i])
	{
		if (!ft_strncmp(tkn[i], "echo", 4)
			&& !there_is_pipeline(tkn_value))
			ft_handle_echo(data, tkn, tkn_value, i);
		else if (!ft_strncmp(tkn[i], "echo", 4)
			&& there_is_pipeline(tkn_value))
			continue ;
		else if (tkn_value[i] == CMD)
			printf("minishell: %s: no such file or directory\n", tkn[i]);
	}
	return (FALSE);
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

	i = -1;
	path = NULL;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strjoin(envp[i] + 5, "/usr/bin:/bin");// error handling > good
			if (!path)
				malloc_error("malloc : path_envp");
			break ;
		}
	}
	if (!path)
		return (NULL);
	else
	{
		path_f = ft_split(path, ':');// error handling > good
		if (!path_f)
			malloc_error("malloc : path_f_envp");
		free(path);
		path = NULL;
		return (path_f);
	}
}
