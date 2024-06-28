
#include "../../includes/minishell.h"

void	command_found(t_exec *data, t_cmd_list *list, char **envp)
{
	data->pid_i++;
	data->cmd_count--;
	if (pipe(data->fds) == -1)
	{
		perror("pipe");
		return ;// error handling, fd closing and reprompt?
	}
	data->pidz[data->pid_i] = fork();
	check_err_fork(data->pidz[data->pid_i]);
	if (data->pidz[data->pid_i] == 0)
		child_exec(envp, data, list, list->elem);
	else
		parent_exec(data, list, list->elem);
}

void	command_not_found(t_exec *data, char *wrong_cmd)
{
	ft_printf("minishlag: %s: command not found\n", wrong_cmd);
	data->parsing_ptr->exit_value = 127;
	handle_input();
}

void	multi_execution(t_cmd_list *list, t_exec *data, char **envp)
{
	t_cmd_list	*list_cpy;

	list_cpy = list;
	while (list)
	{
		if (list->cmd_found || list->relative_path)
			command_found(data, list, envp);
		else if (list->cmd)
			command_not_found(data, list->elem);
		if (list->next)
			list->next->index = list->index + 1;
		reset_outfile(data, list->index);
		list = list->next;
	}
	free_strs(data->paths);
	free_list(list_cpy);	
	wait_pidz(data);
}

void	execution(char *tkn[], char **envp, t_parsing *parsing)
{
	t_exec		data;
	t_redir		s_redir;
	t_cmd_list	*list;
	int			out_index;

	init_data(&data, &s_redir, parsing, envp);
	data.paths = ft_path_envp(envp);
	list = set_cmd_list(&data, data.parsing_ptr->tkn,
			data.parsing_ptr->tkn_value);
	out_index = check_for_redirection(list, &data, envp);
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
}
