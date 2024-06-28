
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
		list->absolute_path = TRUE;
		return (ft_strdup(cmd));
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

	i = -1;
	while (data->pidz[++i] > -1)
		waitpid(data->pidz[i], &status, 0);
	free(data->pidz);
}

void	init_data(t_exec *data, t_redir *s_redir,
			t_parsing *parsing, char **envp)
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
	data->fds[0] = 0;
	data->fds[1] = 0;
	data->cmd_count = cmd_count(parsing->tkn, parsing->tkn_value, envp);
	if (data->cmd_count)
	{
		data->pidz = (pid_t *)ft_calloc(1,
			(data->cmd_count + 1) * sizeof(pid_t));
		if (data->pidz == NULL)
			malloc_error();
		data->pidz[data->cmd_count] = -1;
	}
	data->pid_i = -1;
	data->check_signal = 0;
}
