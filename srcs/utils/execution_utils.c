
#include "../../includes/minishell.h"

void	check_err_fork(pid_t pid)
{
	if (pid < 0)
		{
		perror("fork");
		exit(FORK_FAILURE);// error handling > good
	}
}

void	wait_pidz(t_exec *data)
{
	int		i;
	int		status;

	i = 0;
	while (data->pid_i)
	{
		waitpid(data->pidz[i], &status, 0);
		data->pid_i--;
		i++;
	}
}

void	init_pidz(t_exec *data, int cmd_count)
{
	data->pidz = (pid_t *)ft_calloc(1,
			(cmd_count + 1) * sizeof(pid_t));
	if (data->pidz == NULL)
		malloc_error("malloc: init data");
	data->pidz[cmd_count] = -1;
}

void	init_data(t_exec *data, t_redir *s_redir,
			t_parsing *parsing, char **envp)
{
	s_redir->redir_in = FALSE;
	s_redir->redir_denied = FALSE;
	s_redir->redir_out = FALSE;
	s_redir->here_doc = FALSE;
	s_redir->append = FALSE;
	parsing->exit_value = 0;
	data->redir_ptr = s_redir;
	data->parsing_ptr = parsing;
	data->paths = NULL;
	data->outfile = NULL;
	data->stdin_cpy = dup(0);
	data->stdout_cpy = dup(1);
	data->fds[0] = -1;
	data->fds[1] = -1;
	data->cmd_count = cmd_count(parsing->tkn, parsing->tkn_value, envp);
	if (data->cmd_count)
		init_pidz(data, data->cmd_count);
	else
		data->pidz = NULL;
	data->pid_i = 0;
	data->check_signal = 0;
}
