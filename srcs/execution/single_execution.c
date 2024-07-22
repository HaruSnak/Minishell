/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:39:11 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/22 11:21:44 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_cmd_list *list, t_exec *data, char **argv, char **envp)
{
	char	*path;

	path = find_cmd_path(list, data, argv[0]);
	if (path)
		execve(path, argv, envp);
	else
	{
		if (path)
			free(path);
		path = NULL;
		perror("execve");
	}
}

void	single_cmd_execution(t_cmd_list *list, t_exec *data,
	char **envp, char *tkn[])
{
	char	**argv;

	ft_init_signal_block();
	if (!handle_single_redir(list, data))
		return ;
	argv = find_path_set_argv(data, list, data->parsing_ptr->tkn_value, tkn);
	if (argv)
	{
		data->pidz[0] = fork();
		check_err_fork(data->pidz[0]);
		if (data->pidz[0] == 0)
		{
			exec_cmd(list, data, argv, envp);
			ft_g_signal(data->parsing_ptr);
		}
		wait_and_fetch_exit_value(data->pidz[0], data);
		free_strs(argv);
	}
	else if (data->parsing_ptr->tkn_value[list->index] == CMD)
	{
		ft_printf("%s: command not found\n", tkn[0]);
		data->parsing_ptr->exit_value = 127;
	}
}
