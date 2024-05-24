
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

void	cmds_execution(t_exec **data, char **envp)
{
	char	*path;
	int		i;

	i = -1;
	while ((*data)->parsing_ptr->tkn[++i])
	{
		// printf("tkn[%d]: %s\n", i, (*data)->parsing_ptr->tkn[i]);
		if (*(*data)->parsing_ptr->tkn_value[i] != CMD)
			continue ;
		path = find_cmd_path(data, (*data)->parsing_ptr->tkn[i]);
		if (pipe((*data)->fds) == -1)
		{
			perror("pipe");
			exit(errno);
		}
		if (path == NULL)
			command_not_found(data, i);
		else
			command_found(data, &path, envp, i);
	}
}

void	execution(char *tkn[], char **envp, struct s_parsing *parsing)
{
	t_exec	*data;
	t_redir	*s_redir;

	parsing->path = ft_path_envp(envp);
	init_data(&data, &s_redir, parsing);
	check_for_redirection(tkn, parsing->tkn_value, &data, &s_redir);
	// if (data->infile)       	 // make sure the redirection inside
		// redirect_input(data); // the check_access is fine;
	if (there_is_pipeline(*parsing->tkn_value) == TRUE)
		cmds_execution(&data, envp);
	else
		single_cmd_execution(&data, s_redir, envp, tkn);
	close(data->prevpipe);
	wait_pidz(&data);
}

// < in cat > out
//-----// to come back to //-----//

// Single execution 
// 

