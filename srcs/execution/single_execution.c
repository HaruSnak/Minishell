
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
		malloc_error();
	while (tkn_value[i] && (tkn_value[i] == ARG || tkn_value[i] == CMD))
	{
		argv[j] = ft_strdup(tkn[i]);// error handling
		if (!argv)
			malloc_error();
		i++;
		j++;
	}
	argv[j] = NULL;
	return (argv);
}

void	exec_cmd(t_cmd_list *list, t_exec *data, char **argv, char **envp)
{
	char	*path;

	path = find_cmd_path(list, data, argv[0]); // argv[0] bad
	if (data->outfile)
		redirect_output(data, data->redir_ptr);
	if (path)
		execve(path, argv, envp);
	else
	{
		free(path);
		perror("execve");
	}
}

char	**find_path_set_argv(t_exec *data, t_cmd_list *list, int *tkn_value, char **tkn)
{
	char	*cmd_path;
	char	**argv;
	int		i;

	i = -1;
	cmd_path = NULL;
	while(list && !list->cmd)
		list = list->next;
	while (tkn[++i])
	{
		if (tkn_value[i] == CMD)
			cmd_path = ft_strdup(find_cmd_path(list, data, tkn[i]));
	}
	if (!cmd_path)
		malloc_error();
	else
	{
		free(cmd_path);
		argv = set_argv(tkn, tkn_value);
		return (argv);
	}
	return (NULL);
}

void	single_cmd_execution(t_cmd_list *list, t_exec *data, char **envp, char *tkn[])
{
	char	**argv;

	ft_init_signal_block();
	if (data->redir_ptr->redir_denied)
		return ;
	argv = find_path_set_argv(data, list, data->parsing_ptr->tkn_value, tkn);
	if (argv)
	{
		data->pidz[0] = fork();
		check_err_fork(data->pidz[0]);
		if (data->pidz[0] == 0)
			exec_cmd(list, data, argv, envp);
		wait_pidz(data);
		free_strs(argv);
	}
	else if (data->parsing_ptr->tkn_value[list->index] == CMD)
	{
		ft_printf("minishlag: %s: command not found\n", tkn[0]);
		data->parsing_ptr->exit_value = 127;
	}
}
