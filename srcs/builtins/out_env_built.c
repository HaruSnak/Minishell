
#include "../../includes/minishell.h"

void	ft_setenv_last(char **envp, t_parsing *parsing, int i)
{
	char				*tmp_equal;
	static int			j;

	if (parsing->tmp_setenv == NULL)
		parsing->tmp_setenv = malloc(sizeof(char *) * 100);
	if (parsing->v_senv != NULL)
	{
		tmp_equal = ft_strjoin(parsing->n_senv, "=");
		parsing->tmp_setenv[j] = ft_strjoin(tmp_equal, parsing->v_senv);
		free(tmp_equal);
	}
	else
		parsing->tmp_setenv[j] = ft_strdup(parsing->n_senv);
	parsing->tmp_setenv[j + 1] = NULL;
	envp[i + 1] = parsing->tmp_setenv[j];
	envp[i + 2] = NULL;
	j++;
}

void	ft_envp_external(t_parsing *parsing, char **envp, int i)
{
	char	*tmp_equal;
	char	*tmp;
	int		j;

	j = 0;
	while (parsing->tmp_setenv[j] != NULL)
	{
		if (ft_strncmp(envp[i], parsing->tmp_setenv[j],
				ft_strlen(parsing->tmp_setenv[j])) == 0)
		{
			tmp_equal = ft_strjoin(parsing->n_senv, "=");
			tmp = ft_strjoin(tmp_equal, parsing->v_senv);
			free(tmp_equal);
			free(parsing->tmp_setenv[j]);
			parsing->tmp_setenv[j] = ft_strdup(tmp);
			free(tmp);
			envp[i] = parsing->tmp_setenv[j];
			break ;
		}
		j++;
	}
}

void	ft_setenv_bis(t_parsing *parsing, char **envp, int i, char *tmp_equal)
{
	char	*tmp_last;

	if (parsing->v_senv != NULL)
	{
		if (i < parsing->count_envp)
		{
			tmp_equal = ft_strjoin(parsing->n_senv, "=");
			tmp_last = ft_strjoin(tmp_equal, parsing->v_senv);
			ft_strlcpy(envp[i], tmp_last, ft_strlen(tmp_last) + 1);
			free(tmp_last);
			free(tmp_equal);
		}
		else
		{
			ft_envp_external(parsing, envp, i);
		}
	}
	else
		ft_strlcpy(envp[i], parsing->n_senv, ft_strlen(parsing->n_senv) + 1);
}

int	ft_setenv(char **envp, t_parsing *parsing)
{
	char	*tmp;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (!ft_strncmp(envp[i], parsing->n_senv, ft_strlen(parsing->n_senv)))
		{
			tmp = ft_strnstr(envp[i], "\n", ft_strlen(envp[i]));
			if (tmp != NULL)
				ft_memmove(envp[i], tmp + 1, ft_strlen(tmp) - 1);
			ft_setenv_bis(parsing, envp, i, tmp);
			parsing->exit_value = 0;
			return (0);
		}
		else if (envp[i + 1] == NULL)
			return (parsing->exit_value = 0,
				ft_setenv_last(envp, parsing, i), 0);
	}
	return (-1);
}
