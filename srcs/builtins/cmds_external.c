
#include "../../includes/minishell.h"

int	ft_handle_empty_cmd(char **input)
{
	int	i;

	i = 0;
	if (*input[0] == '\0')
		return (-1);
	while ((*input)[i] != '\0')
	{
		if (!((*input)[i] >= 9 && (*input)[i] <= 13) || (*input)[i] == 32)
			return (0);
	}
	return (-1);
}

void	ft_multi_args_exit(t_parsing *parsing)
{
	int		i;

	i = -1;
	while (parsing->tkn[1][++i] != '\0')
	{
		if (parsing->tkn[1][i] < '0' || parsing->tkn[1][i] > '9')
		{
			printf("minishell: exit: %s: numeric argument required\n",
				parsing->tkn[1]);
			exit(255);
		}
	}
}

int	ft_handle_exit(t_parsing *parsing)
{
	if (ft_strncmp(parsing->tkn[0], "exit",
			ft_strlen(parsing->tkn[0])) == 0 && parsing->tkn[1] == NULL)
	{
		exit(parsing->exit_value);
	}
	else if (ft_strncmp(parsing->tkn[0], "exit",
			ft_strlen(parsing->tkn[0])) == 0 && parsing->tkn[1] != NULL
		&& parsing->tkn[2] == NULL)
	{
		ft_multi_args_exit(parsing);
		exit(ft_atoi(parsing->tkn[1]));
	}
	return (-1);
}

int	ft_return_value_echo(t_parsing *parsing, int i, int j)
{
	while (parsing->tkn[++j] != NULL)
	{
		while (parsing->tkn[j][++i] != '\0')
		{
			if (parsing->tkn[j][i] == '$' && parsing->tkn[j][i + 1] == '?')
			{
				i += 1;
				printf("%d", parsing->exit_value);
			}
			else
			{
				if (i + 1 == ft_strlen(parsing->tkn[j])
					&& parsing->tkn[j + 1] != NULL)
					printf("%c ", parsing->tkn[j][i]);
				else
					printf("%c", parsing->tkn[j][i]);
			}
		}
		i = -1;
	}
	printf("\n");
	return (0);
}

int	ft_handle_echo(t_parsing *parsing)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (ft_strncmp(parsing->tkn[0], "echo", ft_strlen(parsing->tkn[0])) == 0
		|| !ft_strncmp(parsing->tkn[0], "echo ", ft_strlen(parsing->tkn[0])))
	{
		printf("\n");
		return (0);
	}
	if (ft_strncmp(parsing->tkn[0], "echo ", ft_strlen(parsing->tkn[0])) == 0
		&& ft_strchr(parsing->tkn[1], '$')
		!= NULL && ft_strchr(parsing->tkn[1], '?') != NULL)
	{
		if (ft_return_value_echo(parsing, i, j) == 0)
			return (0);
	}
	return (-1);
}
