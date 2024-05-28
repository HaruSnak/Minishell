
#include "../../includes/minishell.h"

void	parent_exec(t_exec **data)
{
	close((*data)->fds[1]);
	dup2((*data)->fds[0], STDIN_FILENO);
	close((*data)->fds[0]);
}

void	command_found(t_exec **data, t_cmd_list *list, char *path, char **envp)
{
	static int	i;

	i = -1;
	(*data)->pidz[++i] = fork();
	check_err_fork((*data)->pidz[i]);
	if (!(*data)->fds[0] && pipe((*data)->fds) == -1)
	{
		perror("pipe");
		exit(errno); // Error handling, no exit?
	}
	if ((*data)->pidz[i] == 0)
	{
		child_exec(envp, data, list, path);
	}
	else
		parent_exec(data);
}

void	command_not_found(t_exec **data, char *wrong_cmd)
{
	ft_printf("minishlag: %s: command not found\n", wrong_cmd);
	close((*data)->fds[1]);
	if ((*data)->fds[0])
		dup2((*data)->fds[0], STDIN_FILENO);
	close((*data)->fds[0]);
}

void	multi_execution(t_exec **data, char **envp)
{
	t_cmd_list	*list;
	char		*path;
	int			i;

	i = -1;
	list = set_cmd_list((*data)->parsing_ptr->tkn, (*data)->parsing_ptr->tkn_value);
	while (list)
	{
		if (list->cmd) 
		{
			(*data)->cmd_cnt--;
			path = find_cmd_path(data, list->elem);
		}
		if (path && list->cmd)
			command_found(data, list, path, envp);
		else if (list->cmd)		
			command_not_found(data, list->elem);
		list = list->next;
	}
	free(path);
}

void	execution(char *tkn[], char **envp, t_parsing *parsing)
{
	t_exec	*data;
	t_redir	*s_redir;

	parsing->path = ft_path_envp(envp);
	init_data(&data, &s_redir, parsing);
	check_for_redirection(tkn, parsing->tkn_value, &data, &s_redir);
	data->cmd_cnt = there_is_pipeline(parsing->tkn_value);
	if (data->cmd_cnt)
		multi_execution(&data, envp);
	else
		single_cmd_execution(&data, s_redir, envp, tkn);
	wait_pidz(&data);
}

//-----// to come back to //-----//

// Multi pipes:
// 
// 
// Builtins exec:
// 
// 
// Heredoc

// < in ls -l | wc > out