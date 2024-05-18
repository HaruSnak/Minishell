
#include "../../includes/minishell.h"

void	parent_exec(struct s_parsing *parsing)
{
	close(parsing->fds[1]);
	close(parsing->prevpipe);
	dup2(parsing->fds[0], parsing->prevpipe);
	close(parsing->fds[0]);
}

void	command_found(struct s_parsing *parsing, char **path, char **envp, int i)
{
	parsing->pidz[i] = fork();
	check_err_fork(parsing->pidz[i]);
	if (parsing->pidz[i] == 0)
		child_exec(envp, parsing, i, *path);
	else
		parent_exec(parsing);
	free(*path);
}

void	command_not_found(struct s_parsing *parsing, int i)
{
	ft_printf("minishlag: %s: command not found\n", parsing->tkn[i]);
	close(parsing->prevpipe);
	parsing->prevpipe = dup(parsing->fds[0]);
	close(parsing->fds[1]);
	close(parsing->fds[0]);
}

void	execution(char *argv[], char **envp, struct s_parsing *parsing,
			bool check)
{
	char	*path;
	int		i;

	(void)argv;
	(void)check;
	i = -1;
	// printf("infile: %s\n", parsing->infile);
	// if (parsing->infile)
		// parsing->prevpipe = open(parsing->infile, O_RDONLY);
	// if ((parsing->prevpipe) == -1)
	// {
		// perror("infile");
		// exit(0);
	// }
	printf("tkn: %s\n", parsing->tkn[0]);
	while (parsing->tkn[++i])
	{
		PL;
		path = find_cmd_path(parsing, i);
		PL;
		if (pipe (parsing->fds) == -1)
		{
			perror("pipe");
			exit(errno);
		}
		if (path == NULL)
			command_not_found(parsing, i);
		else
			command_found(parsing, &path, envp, i);
	}
	close(parsing->prevpipe);
	// wait_pidz(parsing);
}
