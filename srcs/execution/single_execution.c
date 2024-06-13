
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
		perror("set_argv:");
		return (NULL);//      gestion d'erreur
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

void	single_cmd_execution(t_exec *data, t_redir *s_redir,
			char **envp, char *tkn[])
{
	pid_t	pid;
	int		status;
	char	**argv;
	char	*path;

	ft_init_signal_block();
	if (there_is_cmds(data, tkn, data->parsing_ptr->tkn_value))
	{
		pid = fork();
		if (pid == 0)
		{
			argv = set_argv(tkn, data->parsing_ptr->tkn_value);
			path = find_cmd_path(data, argv[0]);
			// if (ft_external_cmds(argv, data->parsing_ptr, envp) == 0)
			if (s_redir->redir_out || s_redir->append)
				redirect_output(data, s_redir);
			else
				execve(path, argv, envp);
		}
		waitpid(pid, &status, 0);
	}
}
