
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

void	redirect_output(t_exec **data)
{
	int		fd_out;

	printf("outpath: %s\n", (*data)->outfile);
	fd_out = open((*data)->outfile, O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0);
	if (fd_out == -1)
	{
		perror("outfile");
		exit(0);
	}
	dup2(fd_out, STDOUT_FILENO);
}

void	pipe_handling(t_exec **data, int i)
{
	dup2((*data)->prevpipe, STDIN_FILENO);
	close((*data)->prevpipe);
	close((*data)->fds[0]);
	if ((*data)->parsing_ptr->tkn[i + 1] == NULL)
		;
		// redirect_output(parsing);
	else
		dup2((*data)->fds[1], STDOUT_FILENO);
	close((*data)->fds[1]);
}

void	child_exec(char **envp, t_exec **data, int i, char *path)
{
	pipe_handling(data, i);
	execve(path, (*data)->parsing_ptr->tkn, envp);
}
