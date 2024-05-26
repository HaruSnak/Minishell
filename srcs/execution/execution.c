
#include "../../includes/minishell.h"

void	parent_exec(t_exec **data)
{
	close((*data)->fds[1]);
	close((*data)->prevpipe);
	dup2((*data)->fds[0], (*data)->prevpipe);
	close((*data)->fds[0]);
}

void	command_found(t_exec **data, char **path, char **envp, int i)
{
	(*data)->pidz[i] = fork();
	if (pipe((*data)->fds) == -1)
	{
		perror("pipe");
		exit(errno);
	}
	check_err_fork((*data)->pidz[i]);
	if ((*data)->pidz[i] == 0)
		child_exec(envp, data, i, *path);
	else
		parent_exec(data);
	free(*path);
}

void	command_not_found(t_exec **data, int i)
{
	ft_printf("minishlag: %s: command not found\n",
		(*data)->parsing_ptr->tkn[i]);
	close((*data)->prevpipe);
	(*data)->prevpipe = dup((*data)->fds[0]);
	close((*data)->fds[1]);
	close((*data)->fds[0]);
}

void	multi_execution(t_exec **data, char **envp)
{
	t_cmd_list	*cmd;
	// char	*path;
	int		i;

	(void)envp;
	i = -1;
	cmd = set_cmd_list((*data)->parsing_ptr->tkn, (*data)->parsing_ptr->tkn_value);
	while (cmd)
	{
		printf("tkn: %s\n", cmd->elem);
		cmd = cmd->next;
	}
}

void	execution(char *tkn[], char **envp, t_parsing *parsing)
{
	t_exec	*data;
	t_redir	*s_redir;


	parsing->path = ft_path_envp(envp);
	init_data(&data, &s_redir, parsing);
	check_for_redirection(tkn, parsing->tkn_value, &data, &s_redir);
	if (there_is_pipeline(parsing->tkn_value) == TRUE)
		multi_execution(&data, envp);
	else
		single_cmd_execution(&data, s_redir, envp, tkn);
	close(data->prevpipe);
	wait_pidz(&data);
}

//-----// to come back to //-----//

// Multi pipes:
// Gerer le metachar '|'
// 
// 
// Builtins exec:
// 
// 
// Heredoc
// cat < in | wc > out


/*		if (is_builtin())
			continue ;
		if ((*data)->parsing_ptr->tkn_value[i] != CMD)
			continue ;
		path = find_cmd_path(data, (*data)->parsing_ptr->tkn[i]);
		if (path == NULL && (*data)->parsing_ptr->tkn_value[i] == CMD)
			command_not_found(data, i);
		else if ((*data)->parsing_ptr->tkn_value[i] == CMD)
			command_found(data, &path, envp, i);
*/