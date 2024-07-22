/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:43 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 19:12:12 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_and_fetch_exit_value(pid_t pid, t_exec *data)
{
	int	status;
	
	if (!waitpid(pid, &status, 0))
	{
		perror("waitpid");
		exit(OUT_OF_MEMORY);
	}
	if (WIFEXITED(status))
		data->parsing_ptr->exit_value = WEXITSTATUS(status);
}
