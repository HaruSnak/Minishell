
#include "../../includes/minishell.h"

void	parent_exec(t_exec *data, t_cmd_list *list)
{
	close(data->fds[1]);
	if (list)
	{
		if(dup2(data->fds[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(DUP_FAILURE);
		}
	}
	close(data->fds[0]);
}

bool	pipe_handling(t_exec *data, t_cmd_list *list)
{
	PI(list->index + 1);
	PS(list->elem);
	close(data->fds[0]);
	if (list)
	{
		PL;
		redirect_output(data, data->redir_ptr);
		close(data->fds[1]);
	}
	else
		dup2(data->fds[1], STDOUT_FILENO);
	close(data->fds[1]);
	return (TRUE);
}

void	child_exec(char **envp, t_exec *data, t_cmd_list *list, char *path)
{
	char	**argv;

	if (pipe_handling(data, list))
	{
		argv = set_argv_lst(list, list->elem);
		execve(path, argv, envp);
		perror_exit("execve");// test to remove
	}
	else
		data->parsing_ptr->exit_value = 1;
}
