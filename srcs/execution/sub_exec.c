
#include "../../includes/minishell.h"

void	parent_exec(t_exec *data)
{
	close(data->fds[1]);
	if(dup2(data->fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2");// error handling
		return ;
	}
	close(data->fds[0]);
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
		dup2(data->fds[1], STDOUT_FILENO);// error handling
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
