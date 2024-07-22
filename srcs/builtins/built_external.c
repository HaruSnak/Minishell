/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_external.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:40:25 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 13:40:26 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (!ft_isdigit(parsing->tkn[1][i])
		&& !(i == 0 && (parsing->tkn[1][0] == '-' || parsing->tkn[1][0] == '+'
		|| ft_isdigit(parsing->tkn[1][0]))))
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
		if (ft_atoi(parsing->tkn[1]) < 0)
			exit(256 + (ft_atoi(parsing->tkn[1]) % 256));
		else if (ft_atoi(parsing->tkn[1]) > 255)
			exit(ft_atoi(parsing->tkn[1]) % 256);
		else
			exit(ft_atoi(parsing->tkn[1]));
	}
	else if (ft_strncmp(parsing->tkn[0], "exit",
			ft_strlen(parsing->tkn[0])) == 0 && parsing->tkn[1] != NULL
		&& parsing->tkn[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		return (parsing->exit_value = 1, 1);
	}
	return (-1);
}
