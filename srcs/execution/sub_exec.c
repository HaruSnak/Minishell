
#include "../../includes/minishell.h"

void	parent_exec(t_exec *data)
{
	if (data->redir_ptr->redir_denied == TRUE)
		data->redir_ptr->redir_denied = FALSE;
	if (data->fds[WRIT] != -1)
	{
		close(data->fds[WRIT]);
		data->fds[WRIT] = -1;
	}
	if(dup2(data->fds[READ], STDIN_FILENO) == -1)
		perror("dup2 parent");// error handling
	if (data->fds[READ] != -1)
	{
		close(data->fds[READ]);
		data->fds[READ] = -1;
	}
}

bool	redir_handling(t_exec *data)
{
	close(data->fds[READ]);
	data->fds[READ] = -1;
	if (data->outfile && !data->cmd_count)
		redirect_output(data, data->redir_ptr);
	else if (!data->cmd_count && !data->redir_ptr->redir_out)
		print_output(data->fds[WRIT]);
	else if(dup2(data->fds[WRIT], STDOUT_FILENO) == -1)
		perror("dup2 child"); // error handling
	close(data->fds[WRIT]);
	data->fds[WRIT] = -1;
	return (TRUE);
}

void	child_exec(char **envp, t_exec *data, t_cmd_list *list, char *path)
{
	char	**argv;

	if (data->redir_ptr->redir_denied)
		exit(PERMISSION_DENY);
	if (redir_handling(data))
	{
		argv = set_argv_lst(list, list->elem);
		execve(path, argv, envp);
	}
	else
	{
		data->parsing_ptr->exit_value = CMD_NOT_EXECUTABLE;
		exit(CMD_NOT_EXECUTABLE);
	}
}
