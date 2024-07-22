/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:37:40 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 13:37:46 by shmoreno         ###   ########.fr       */
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

void	ft_cmd_clear(void)
{
	printf("\033[H\033[J");
}
