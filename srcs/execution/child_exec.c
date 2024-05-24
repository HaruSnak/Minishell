
#include "../../includes/minishell.h"

// char	**set_argv( struct s_parsing *parsing, char **exec_argv, char **flag_splited, int j)
// {
// 	int	i;

// 	exec_argv[0] = ft_strdup(parsing->cmd_ptr[j]);
// 	i = -1;
// 	while (flag_splited[++i])
// 		exec_argv[i + 1] = ft_strdup(flag_splited[i]);
// 	exec_argv[i + 1] = NULL;
// 	return (exec_argv);
// }

void	pipe_handling(t_exec **data, int i)
{
	dup2((*data)->prevpipe, STDIN_FILENO);
	sleep(10);
	close((*data)->prevpipe);
	close((*data)->fds[0]);
	if (*(*data)->parsing_ptr->tkn_value[i + 1] == OUT
		|| *(*data)->parsing_ptr->tkn_value[i + 1] == APPEND)
	{
		fprintf(stderr, "tkn_value[%d]: %d\n", i, *(*data)->parsing_ptr->tkn_value[i + 1]);
		fprintf(stderr, "tkn[%d]: %s\n", i, (*data)->parsing_ptr->tkn[i + 1]);
		redirect_output(data, (*data)->redir_ptr);
	}
	else
		dup2((*data)->fds[1], STDOUT_FILENO);
		sleep(10);
	close((*data)->fds[1]);
}

void	child_exec(char **envp, t_exec **data, int i, char *path)
{
	pipe_handling(data, i);
	exit(0); // DO NOT REMOVE
	execve(path, (*data)->parsing_ptr->tkn, envp); // setup real argv
}
