
#include "../../includes/minishell.h"

void	pipe_handling(t_exec **data)
{
	close((*data)->fds[0]);
	if (!(*data)->pipe_cnt)
		redirect_output(data, (*data)->redir_ptr);
	else
		dup2((*data)->fds[1], STDOUT_FILENO);
	close((*data)->fds[1]);
}

void	child_exec(char **envp, t_exec **data, t_cmd_list *list, char *path)
{
	char	**argv;

	pipe_handling(data);
	argv = set_argv_lst(list, list->elem);
	execve(path, argv, envp);
	perror_exit("execve");
}

	// int i = -1;
	// while (argv[++i])
	// 	fprintf(stderr, "argv[%i]: %s, pid: %d\n", i, argv[i], getpid());
	// fprintf(stderr, "path: %s\n", path);