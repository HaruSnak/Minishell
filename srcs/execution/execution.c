
#include "../../includes/minishell.h"

void perror_exit(const char *msg)// tests
{
	perror(msg);
	exit(errno);
}

void	parent_exec(t_exec *data)
{
	close(data->fds[1]);
	if (data->pipe_cnt)
		dup2(data->fds[0], STDIN_FILENO);
	close(data->fds[0]);
}

void	command_found(t_exec *data, t_cmd_list *list, char *path, char **envp)
{
	if (pipe(data->fds) == -1)
	{
		perror("pipe");
		exit(errno); // Error handling, no exit?
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
	close(data->fds[1]);
	if (data->fds[0])
		dup2(data->fds[0], STDIN_FILENO);
	close(data->fds[0]);
}

void	multi_execution(t_exec *data, char **envp)
{
	t_cmd_list	*list;
	char		*path;

	list = set_cmd_list(data->parsing_ptr->tkn,
			data->parsing_ptr->tkn_value);
	while (data->pipe_cnt)
	{
		if (list->cmd)
			path = find_cmd_path(data, list->elem);
		if (path && list->cmd)
		{
			data->pipe_cnt--;
			data->pid_i++;
			command_found(data, list, path, envp);
		}
		else if (list->cmd)
			command_not_found(data, list->elem);
		list = list->next;
	}
	if (path && list)
		free(path);
	// free list ;
}

void	execution(char *tkn[], char **envp, t_parsing *parsing)
{
	t_exec	data;
	t_redir	s_redir;

	parsing->path = ft_path_envp(envp);
	init_data(&data, &s_redir, parsing);
	ft_fill_envp(&data, envp);
	check_for_redirection(tkn, parsing->tkn_value, &data, &s_redir);
	data.pipe_cnt = there_is_pipeline(parsing->tkn_value);
	if (data.pipe_cnt)
	{
		multi_execution(&data, envp);
		wait_pidz(&data);
	}
	else if (*tkn)
		single_cmd_execution(&data, &s_redir, envp, tkn);
	dup2(data.stdin_cpy, STDIN_FILENO);
	dup2(data.stdout_cpy, STDOUT_FILENO);
	close(data.stdin_cpy);
	close(data.stdout_cpy);
	ft_free_data(&data, parsing);
}

		// if (ft_external_cmds(list->elem, data->parsing_ptr, envp) == 0)
		// 	continue ;

//-----// to come back to //-----//

// Multi pipes:
// 
// 
// Builtins exec:
// 
// 
// Heredoc

// < in cat | wc > out