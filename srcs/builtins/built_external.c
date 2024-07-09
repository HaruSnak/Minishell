
#include "../../includes/minishell.h"

int	ft_handle_empty_cmd(char **input)
{
	int	i;

	i = 0;
	if (*input[0] == '\0')
		return (-1);
	while ((*input)[i] != '\0')
	{
		if ((*input)[i] >= 33 && (*input)[i] <= 126)
			return (0);
		i++;
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
