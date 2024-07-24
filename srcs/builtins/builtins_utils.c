/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:37:40 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/24 16:23:45 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtins(char *cmd, t_exec *data, char **envp)
{
	if (!ft_strncmp(cmd, "exit", 4) || !ft_strncmp(cmd, "cd", 2)
		|| !ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5))
	{
		builtins_exec(data->parsing_ptr, envp);
		return (TRUE);
	}
	else
		return (FALSE);
}

// Function to clear the terminal
// when the clear token is encountered
void	ft_cmd_clear(void)
{
	printf("\033[H\033[J");
}

void	ft_cmd_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
		printf("%s\n", envp[i]);
}
