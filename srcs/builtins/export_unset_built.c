

#include "../../includes/minishell.h"

int	ft_check_error(t_parsing *parsing)
{
	int	i;

	i = -1;
	while (parsing->tkn[1][++i] != '\0')
	{
		if (parsing->tkn[1][i] == '=')
			break ;
		if (!ft_isalnum(parsing->tkn[1][i]) && parsing->tkn[1][i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				parsing->tkn[1]);
			return (parsing->exit_value = 1, -1);
		}
	}
	return (0);
}

int	ft_handle_unset(t_parsing *parsing, char **envp)
{
	int		i;

	i = -1;
	if (parsing->tkn[1] == NULL)
		return (-1);
	else
	{
		while (envp[++i] != NULL)
		{
			if (ft_strncmp(envp[i], parsing->tkn[1],
					ft_strlen(parsing->tkn[1])) == 0)
			{
				while (envp[i + 1] != NULL)
				{
					envp[i] = envp[i + 1];
					i++;
				}
				envp[i] = NULL;
				break ;
			}
		}
	}
	return (0);
}

void	ft_handle_export(t_parsing *parsing, char **envp)
{
	char	**tmp2;
	int		i;

	i = -1;
	if (parsing->tkn[1] == NULL)
	{
		while (envp[++i] != NULL)
			printf("declare -x %s\n", envp[i]);
		parsing->exit_value = 0;
	}
	else if (ft_strchr(parsing->tkn[1], '=') && ft_check_error(parsing) == 0)
	{
		tmp2 = ft_split(parsing->tkn[1], '=');
		parsing->n_senv = tmp2[0];
		parsing->v_senv = tmp2[1];
		ft_setenv(envp, parsing);
		ft_free_d_ptr((void ***)&tmp2);
	}
	else if (!ft_strchr(parsing->tkn[1], '=') && ft_check_error(parsing) == 0)
	{
		parsing->n_senv = parsing->tkn[1];
		parsing->v_senv = NULL;
		ft_setenv(envp, parsing);
	}
}
