
#include "../../includes/minishell.h"

void perror_exit(const char *msg)// tests remove
{
	perror(msg);
	exit(errno);
}

void	command_found(t_exec *data, t_cmd_list *list, char *path, char **envp)
{
	data->pid_i++;
	if (pipe(data->fds) == -1)
	{
		perror("pipe");
		return ;// error handling, fd closing and reprompt?
	}
	data->pidz[data->pid_i] = fork();
	check_err_fork(data->pidz[data->pid_i]);
	if (data->pidz[data->pid_i] == 0)
		child_exec(envp, data, list, path);
	else
		parent_exec(data);
}

void	command_not_found(t_exec *data, char *wrong_cmd)
{
	ft_printf("minishlag: %s: command not found\n", wrong_cmd);
	data->parsing_ptr->exit_value = 127;
	close(data->fds[1]);
	if (data->fds[0])
	{
		if(dup2(data->fds[0], STDIN_FILENO) == -1)// error handling,
			perror("dup2");
	}
	close(data->fds[0]);
}

void	multi_execution(t_exec *data, char **envp)
{
	t_cmd_list	*list;
	t_cmd_list	*list_cpy;
	char		*path;

	list = set_cmd_list(data->parsing_ptr->tkn,
			data->parsing_ptr->tkn_value);
	list_cpy = list;
	while (list)
	{
		if (list->cmd)
			path = find_cmd_path(data, list->elem);
		if (path && list->cmd)
			command_found(data, list, path, envp);
		else if (list->cmd)
			command_not_found(data, list->elem);
		if (path && list->cmd)
			free(path);
		if (list->next)
			list->next->index = list->index + 1;
		check_and_reset_outfile(data, list->index);
		list = list->next;
	}
	free_list(&list_cpy);
}

void	execution(char *tkn[], char **envp, t_parsing *parsing)
{
	t_exec	data;
	t_redir	s_redir;

	parsing->path = ft_path_envp(envp);
	init_data(&data, &s_redir, parsing);
	check_for_redirection(tkn, parsing->tkn_value, &data, envp);
	if (there_is_pipeline(parsing->tkn_value))
	{
		multi_execution(&data, envp);
		wait_pidz(&data);
	}
	else if (*tkn)
		single_cmd_execution(&data, envp, tkn);
	reset_and_free(&data, parsing);
}
