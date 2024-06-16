
#include "../../includes/minishell.h"

int	get_argv_len(int i, int *tkn_value)
{
	int	argv_len;

	argv_len = 0;
	while (tkn_value[i] && (tkn_value[i] == CMD || tkn_value[i] == ARG))
	{
		argv_len++;
		i++;
	}
	return (argv_len);
}

char	**set_argv(char *tkn[], int *tkn_value)
{
	char	**argv;
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (tkn_value[++i] != CMD)
		;
	argv = malloc((get_argv_len(i, tkn_value) + 1) * sizeof(char *));
	if (!argv)
	{
		perror("set_argv");
		exit(EXIT_FAILURE);
	}
	while (tkn_value[i] && (tkn_value[i] == ARG || tkn_value[i] == CMD))
	{
		argv[j] = ft_strdup(tkn[i]);
		i++;
		j++;
	}
	argv[j] = NULL;
	return (argv);
}

bool	there_is_cmds(t_exec *data, char *tkn[], int *tkn_value)
{
	int		i;
	char	*path;

	i = -1;
	while (tkn_value[++i])
	{
		if (tkn_value[i] == CMD)
		{
			path = find_cmd_path(data, tkn[i]);
			if (!path)
				return (FALSE);
			else
			{
				free(path);
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

void	exec_cmd(t_exec *data, char **argv, char **envp)
{
	char	*path;

	path = find_cmd_path(data, argv[0]);
	if (data->redir_ptr->redir_out || data->redir_ptr->append)
		redirect_output(data, data->redir_ptr);
	else if (path)
		execve(path, argv, envp);
	else 
	{
		ft_printf("minishlag: %s: command not found\n", argv[0]);
		data->parsing_ptr->exit_value = 127;
	}
}

void	single_cmd_execution(t_exec *data, char **envp, char *tkn[])
{
	pid_t	pid;
	int		status;
	char	**argv;

	ft_init_signal_block();
	if (is_builtins(tkn[0], tkn, data->parsing_ptr, envp))
		return ;
	if (there_is_cmds(data, tkn, data->parsing_ptr->tkn_value))
	{
		argv = set_argv(tkn, data->parsing_ptr->tkn_value);
		pid = fork();
		check_err_fork(pid);
		if (pid == 0)
			exec_cmd(data, argv, envp);
		waitpid(pid, &status, 0);
	}
}
