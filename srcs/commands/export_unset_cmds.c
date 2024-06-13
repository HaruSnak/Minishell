

#include "../../includes/minishell.h"

/*int	ft_handle_echo_backslash(char *input)
{
	char	**tmp;
	int		i;
	int		k;

	i = -1;
	k = 0;
	tmp = ft_split(input, ' ');
	if (ft_strchr(input, '\\') != ft_strrchr(input, '\\'))
	{
		while (tmp[++i] != NULL)
		{
			while (tmp[++k] != '\0')
			{
				if (input[i] == '\\' && input[i + 1] == '\\')
				{
					tmp = ft_strtrim(tmp, "\\");
				}
			}
			k = 0;
		}
	}
	return (0);
}*/

int	ft_handle_unset(char **input, char **envp)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(*input, ' ');
	if (tmp[1] == NULL)
		return (-1);
	else
	{
		while (envp[++i] != NULL)
		{
			if (ft_strncmp(envp[i], tmp[1], ft_strlen(tmp[1])) == 0)
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
	ft_free_d_ptr((void ***)tmp);
	return (0);
}

void	ft_handle_export(char **input, t_parsing *parsing, char **envp)
{
	char	**tmp;
	char	**tmp2;
	int		i;

	i = -1;
	tmp = ft_split(*input, ' ');
	if (tmp[1] == NULL)
	{
		while (envp[++i] != NULL)
		{
			printf("declare -x %s\n", envp[i]);
		}
	}
	else if (ft_strchr(tmp[1], '=') != NULL)
	{
		tmp2 = ft_split(tmp[1], '=');
		parsing->n_senv = tmp2[0];
		parsing->v_senv = tmp2[1];
		ft_setenv(envp, parsing);
		ft_free_d_ptr((void ***)tmp2);
	}
	ft_free_d_ptr((void ***)tmp);
}

int	ft_external_cmds_bis(char **input, t_parsing *parsing, char **envp)
{
	if (ft_strncmp(*input, "export", 6) == 0)
	{
		ft_handle_export(input, parsing, envp);
		add_history(*input);
		return (0);
	}
	if (ft_strncmp(*input, "unset", 5) == 0)
	{
		ft_handle_unset(input, envp);
		add_history(*input);
		return (0);
	}
	/*if (ft_strncmp(*input, "echo", ft_strlen(*input)) == 0
		|| ft_strncmp(*input, "echo ", ft_strlen(*input)) == 0)
	{
		printf("\n");
		add_history(*input);
		return (0);
	}*/
	if (ft_handle_echo(*input, parsing) == 0 && ft_strncmp(*input, "echo", 4) == 0)
		return (0);
	return (-1);
}
