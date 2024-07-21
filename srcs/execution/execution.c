/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:39:46 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 17:37:39 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_next_cmd_found(t_cmd_list *list, t_exec *data)
{
	if (list->next && data->outfile && !ft_strncmp(list->next->elem,
			data->outfile, ft_strlen(data->outfile)))
		return (1);
	while (list->next && !list->is_cmd)
		list = list->next;
	if (list->cmd_found || list->absolute_path)
		return (1);
	else
	{
		data->pidz[data->pid_i + 1] = 0;
		return (0);
	}
}

void	command_found(t_exec *data, t_cmd_list *list, char **envp)
{
	data->cmd_count--;
	if (data->cmd_count && list->next && !is_next_cmd_found(list->next, data))
		return ;
	else if (list->next && !is_next_cmd_found(list, data))
		return ;
	if (pipe(data->fds) == -1)
	{
		perror("pipe");
		return ;// error handling
	}
	data->pidz[data->pid_i] = fork();
	check_err_fork(data->pidz[data->pid_i]);
	if (data->pidz[data->pid_i] == 0)
		child_exec(envp, data, list, list->elem);
	else
		parent_exec(data);
	data->pid_i++;
}

void	command_not_found(t_exec *data, char *wrong_path)
{
	ft_printf("%s: command not found\n", wrong_path);
	data->parsing_ptr->exit_value = 127;
	handle_input();
}

void	multi_execution(t_cmd_list *list, t_exec *data, char **envp)
{
	t_cmd_list	*list_cpy;

	list_cpy = list;
	while (list)
	{
		if (!ft_strncmp(list->elem, "echo", 4))
			ft_handle_echo(data->parsing_ptr, data->parsing_ptr->tkn,
				data->parsing_ptr->tkn_value, list->index);
		else if (list->cmd_found || list->absolute_path)
			command_found(data, list, envp);
		else if (list->is_cmd)
			command_not_found(data, data->parsing_ptr->tkn[list->index]);
		if (list->next)
			list->next->index = list->index + 1;
		reset_outfile(data, list->index);
		list = list->next;
	}
	free_strs(data->paths);
	free_list(list_cpy);
	wait_pidz(data);
}

bool	execution(char *tkn[], char **envp, t_parsing *parsing)
{
	t_exec		data;
	t_redir		s_redir;
	t_cmd_list	*list;
	int			out_index;

	init_data(&data, &s_redir, parsing, envp);
	data.paths = ft_path_envp(envp);
	if (!data.paths)
		return (no_such_file(parsing, tkn, data.parsing_ptr->tkn_value));
	list = set_cmd_list(&data, data.parsing_ptr->tkn,
			data.parsing_ptr->tkn_value);
	out_index = check_for_redirection(&data, envp);
	if (ft_g_signal(parsing) == 1)
		return (FALSE);
	if (there_is_pipeline(parsing->tkn_value))
		multi_execution(list, &data, envp);
	else if (*tkn)
	{
		single_cmd_execution(list, &data, envp, tkn);
		reset_outfile(&data, out_index);
		free_strs(data.paths);
		free_single_list(list);
	}
	reset_and_free(&data);
	return (TRUE);
}
