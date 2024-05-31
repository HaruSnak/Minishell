
#include "../../includes/minishell.h"

int	is_cmd(char *path)
{
	if (path[ft_strlen(path) - 1] == '/')
		return (FALSE);
	return (TRUE);
}

char	*find_cmd_path(t_exec **data, char *cmd)
{
	char	*path;
	int		accss;
	int		j;

	j = 0;
	while (j < 8)
	{
		path = ft_strjoin_fs((*data)->parsing_ptr->path[j], cmd);
		if (!path)
			return (NULL);
		accss = access(path, X_OK);
		if (accss == 0 && is_cmd(path) == TRUE)
			return (path);
		else
			free(path);
		j++;
	}
	return (NULL);
}

void	wait_pidz(t_exec **data)
{
	int		i;
	int		status;
	pid_t	result;

	i = 0;
	printf("%d\n", (*data)->pidz[i]);
	while ((*data)->pidz[i] != -1)
	{
		result = waitpid((*data)->pidz[i], &status, 0);
		if (result == -1)
			perror("waitpid");
		i++;
	}
}

void	check_err_fork(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork");
		exit(0);
	}
}

void	init_data(t_exec **data, t_redir **s_redir, t_parsing *parsing)
{
	*s_redir = malloc(sizeof(t_redir));
	(*s_redir)->redir_in = FALSE;
	(*s_redir)->redir_out = FALSE;
	(*s_redir)->here_doc = FALSE;
	(*s_redir)->append = FALSE;
	*data = malloc(sizeof(t_exec));
	(*data)->parsing_ptr = parsing;
	(*data)->outfile = NULL;
	(*data)->pidz = malloc(cmd_count(parsing->tkn_value) * sizeof(pid_t));
	(*data)->prevpipe = 0;
	// (*data)->cmds = NULL;
	// (*data)->fds[0] = 0;
	// (*data)->fds[1] = 0;
}
