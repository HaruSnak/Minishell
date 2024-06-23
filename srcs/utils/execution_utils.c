

#include "../../includes/minishell.h"

void	check_err_fork(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork");
		exit(FORK_FAILURE);// error handling > good
	}
}

int	is_cmd(char *path)
{
	if (path[ft_strlen(path) - 1] == '/')
		return (FALSE);
	return (TRUE);
}

char	*find_cmd_path(t_cmd_list *list, t_exec *data, char *cmd)
{
	char	*path;
	int		j;

	j = 0;
	if (access(cmd, X_OK) == 0 && is_cmd(cmd) == TRUE)
	{
		list->relative_path = TRUE;
		return (cmd);
	}
	while (j < 8)
	{
		path = ft_strjoin_fs(data->paths[j], cmd);
		if (!path)
			malloc_error();
		if (access(path, X_OK) == 0 && is_cmd(path) == TRUE)
			return (path);
		else
			free(path);
		j++;
	}
	return (NULL);
}

void	wait_pidz(t_exec *data)
{
	int		i;
	int		status;
	pid_t	result;

	i = 0;
	while (data->pidz[i] > -1)
	{
		if (*data->pidz)
		{
			result = waitpid(data->pidz[i], &status, 0);
			if (result == -1)
				perror("waitpid");// error handling > enough?
			i++;
		}
	}
	free(data->pidz);
}

void	init_data(t_exec *data, t_redir *s_redir, t_parsing *parsing)
{
	s_redir->redir_in = FALSE;
	s_redir->redir_denied = FALSE;
	s_redir->redir_out = FALSE;
	s_redir->here_doc = FALSE;
	s_redir->append = FALSE;
	data->redir_ptr = s_redir;
	data->parsing_ptr = parsing;
	data->paths = NULL;
	data->outfile = NULL;
	data->stdin_cpy = dup(0);
	data->stdout_cpy = dup(1);
	data->pidz = malloc((cmd_count(parsing->tkn_value) + 1) * sizeof(pid_t));
	if (data->pidz == NULL)
		malloc_error();
	data->pidz[cmd_count(parsing->tkn_value)] = -1;
	data->pid_i = -1;
	data->fds[0] = 0;
	data->fds[1] = 0;
}
