
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

void	redirect_output( struct s_parsing *parsing)
{
	int		fd_out;

	printf("outpath: %s\n", parsing->outfile);
	fd_out = open(parsing->outfile, O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0);
	if (fd_out == -1)
	{
		perror("outfile");
		exit(0);
	}
	dup2(fd_out, STDOUT_FILENO);
}

void	pipe_handling( struct s_parsing *parsing, int i)
{
	dup2(parsing->prevpipe, STDIN_FILENO);
	close(parsing->prevpipe);
	close(parsing->fds[0]);
	if (parsing->tkn[i + 1] == NULL)
		;
		// redirect_output(parsing);
	else
		dup2(parsing->fds[1], STDOUT_FILENO);
	close(parsing->fds[1]);
}

void	child_exec(char **envp,  struct s_parsing *parsing, int i, char *path)
{
	pipe_handling(parsing, i);
	execve(path, parsing->tkn, envp);
}
