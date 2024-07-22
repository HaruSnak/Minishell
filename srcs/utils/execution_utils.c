/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:40 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/22 10:04:09 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_err_fork(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork");
		exit(FORK_FAILURE);
	}
}

void	wait_pidz(t_exec *data)
{
	int		i;
	int		status;

	i = 0;
	while (data->pid_i)
	{
		if (!waitpid(data->pidz[i], &status, 0))
		{
			perror("waitpid");
			exit(OUT_OF_MEMORY);
		}
		if (WIFEXITED(status))
			data->parsing_ptr->exit_value = WEXITSTATUS(status);
		data->pid_i--;
		i++;
	}
}

void	init_pidz(t_exec *data, int cmd_count)
{
	data->pidz = (pid_t *)ft_calloc(1,
			(cmd_count + 1) * sizeof(pid_t));
	malloc_error_ptr(data->pidz, "malloc : init_pidz");
	data->pidz[cmd_count] = -1;
}

void	init_data(t_exec *data, t_redir *s_redir,
			t_parsing *parsing, char **envp)
{
	s_redir->redir_in = FALSE;
	s_redir->redir_denied = FALSE;
	s_redir->redir_out = FALSE;
	s_redir->here_doc = FALSE;
	s_redir->append = FALSE;
	parsing->exit_value = 0;
	data->redir_ptr = s_redir;
	data->parsing_ptr = parsing;
	data->paths = NULL;
	data->outfile = NULL;
	data->stdin_cpy = dup(0);
	data->stdout_cpy = dup(1);
	data->fds[0] = -1;
	data->fds[1] = -1;
	data->cmd_count = cmd_count(parsing->tkn, parsing->tkn_value, envp);
	if (data->cmd_count)
		init_pidz(data, data->cmd_count);
	else
		data->pidz = NULL;
	data->pid_i = 0;
	data->check_signal = 0;
}
