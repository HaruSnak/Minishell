
#include "../../includes/minishell.h"

void	parent_exec(t_exec *data, t_cmd_list *list, char *path)
{
	if (data->redir_ptr->redir_denied == TRUE)
		data->redir_ptr->redir_denied = FALSE;
	close(data->fds[1]);
	if(dup2(data->fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2");// error handling
		return ;
	}
	close(data->fds[0]);
	if (list->relative_path)
		free(path);
}

bool	pipe_handling(t_exec *data, t_cmd_list *list)
{
	close(data->fds[0]);
	if (data->outfile && 
		(!ft_strncmp(data->parsing_ptr->tkn[list->index + 1], ">", 1)
		|| !ft_strncmp(data->parsing_ptr->tkn[list->index + 1], ">>", 2)))
	{
		redirect_output(data, data->redir_ptr);
		close(data->fds[1]);
	}
	else if (!list->next)
		print_output(data->fds[1]);
	else
	if(dup2(data->fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");// error handling
		return (DUP_FAILURE);
	}
	close(data->fds[1]);
	return (TRUE);
}

void	child_exec(char **envp, t_exec *data, t_cmd_list *list, char *path)
{
	char	**argv;

	if (data->redir_ptr->redir_denied)
		exit(PERMISSION_DENY);
	if (pipe_handling(data, list))
	{
		argv = set_argv_lst(list, list->elem);
		execve(path, argv, envp);
		perror_exit("execve");// test to remove
	}
	else
		data->parsing_ptr->exit_value = EXIT_FAILURE;
}
