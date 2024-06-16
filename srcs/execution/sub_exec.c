
#include "../../includes/minishell.h"

void	parent_exec(t_exec *data)
{
	close(data->fds[1]);
	if (data->pipe_cnt)
	{
		if(dup2(data->fds[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(DUP_FAILURE);
		}
	}
	close(data->fds[0]);
}

void	pipe_handling(t_exec *data)
{
	close(data->fds[0]);
	if (!data->pipe_cnt)
		redirect_output(data, data->redir_ptr);
	else
		dup2(data->fds[1], STDOUT_FILENO);
	close(data->fds[1]);
}

void	child_exec(char **envp, t_exec *data, t_cmd_list *list, char *path)
{
	char	**argv;

	pipe_handling(data);
	argv = set_argv_lst(list, list->elem);
	execve(path, argv, envp);
	perror_exit("execve");
}
