/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:39:52 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/22 14:44:02 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_exec(t_exec *data)
{
	if (data->fds[WRIT] != -1)
	{
		close(data->fds[WRIT]);
		data->fds[WRIT] = -1;
	}
	if (dup2(data->fds[READ], STDIN_FILENO) == -1)
		perror("dup2 parent");
	if (data->fds[READ] != -1)
	{
		close(data->fds[READ]);
		data->fds[READ] = -1;
	}
}

void	redir_handling(t_exec *data, t_cmd_list *list)
{
	close(data->fds[READ]);
	data->fds[READ] = -1;
	if (data->outfile && is_redir_next(list))
		redirect_output(data, data->redir_ptr);
	else if (!data->cmd_count)
		print_output(data->fds[WRIT]);
	else if (dup2(data->fds[WRIT], STDOUT_FILENO) == -1)
		perror("dup2 child");
	close(data->fds[WRIT]);
	data->fds[WRIT] = -1;
}

void	child_exec(char **envp, t_exec *data, t_cmd_list *list, char *path)
{
	char	**argv;

	if (data->redir_ptr->redir_denied)
		exit(PERMISSION_DENY);
	redir_handling(data, list);
	argv = set_argv_lst(list, list->elem);
	execve(path, argv, envp);
	data->parsing_ptr->exit_value = CMD_NOT_EXECUTABLE;
	exit(CMD_NOT_EXECUTABLE);
}
