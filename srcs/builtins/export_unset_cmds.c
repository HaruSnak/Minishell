

#include "../../includes/minishell.h"

void	ft_cmd_clear(void)
{
	printf("\033[H\033[J");
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
		{
			printf("declare -x %s\n", envp[i]);
		}
	}
	else if (ft_strchr(parsing->tkn[1], '=') != NULL)
	{
		tmp2 = ft_split(parsing->tkn[1], '=');
		parsing->n_senv = tmp2[0];
		parsing->v_senv = tmp2[1];
		ft_setenv(envp, parsing);
		//ft_free_d_ptr((void ***)tmp2);
	}
	else if (ft_strchr(parsing->tkn[1], '=') == NULL)
	{
		parsing->n_senv = parsing->tkn[1];
		parsing->v_senv = NULL;
		ft_setenv(envp, parsing);
	}
}

int	ft_external_cmds_bis(t_parsing *parsing, char **envp)
{
	if (ft_strncmp(parsing->tkn[0], "export", ft_strlen(parsing->tkn[0])) == 0)
	{
		ft_handle_export(parsing, envp);
		return (0);
	}
	if (ft_strncmp(parsing->tkn[0], "unset", ft_strlen(parsing->tkn[0])) == 0)
	{
		ft_handle_unset(parsing, envp);
		return (0);
	}
	if (ft_strncmp(parsing->tkn[0], "clear", ft_strlen(parsing->tkn[0])) == 0)
	{
		ft_cmd_clear();
		return (0);
	}
	if (ft_handle_echo(parsing) == 0 && !ft_strncmp(parsing->tkn[0], "echo", 4))
		return (0);
	return (-1);
}
