
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

void	ft_setenv_bis(t_parsing *parsing, char **envp, int i, char *tmp)
{
	if (parsing->v_senv != NULL)
	{
		tmp = ft_strjoin(parsing->n_senv, "=");
		parsing->tmp = ft_strjoin(tmp, parsing->v_senv);
		ft_strlcpy(envp[i], parsing->tmp, ft_strlen(parsing->tmp) + 1);
		free(parsing->tmp);
		free(tmp);
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
			return (0);
		}
		else if (envp[i + 1] == NULL)
			return (ft_setenv_last(envp, parsing, i), 0);
	}
	return (-1);
}
