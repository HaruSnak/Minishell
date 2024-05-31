
#include "../../includes/minishell.h"

int	get_argv_len(int i, int *tkn_value)
{
	int	argv_len;

	argv_len = 0;
	while (tkn_value[i] && tkn_value[i] == CMD)
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

	i = -1;
	j = 0;
	while (tkn_value[++i] != CMD)
		;
	argv = malloc((get_argv_len(i, tkn_value) + 1) * sizeof(char*));
	while (tkn_value[i] && tkn_value[i] == CMD)
	{
		argv[j] = ft_strdup(tkn[i]);
		i++;
		j++;
	}
	argv[j] = NULL;
	return (argv);
}

void	single_cmd_execution(t_exec **data, t_redir *s_redir,
			char **envp, char *tkn[])
{
	pid_t	pid;
	char 	**argv;
	char	*path;

	argv = set_argv(tkn, (*data)->parsing_ptr->tkn_value);
	path = find_cmd_path(data, argv[0]);
	pid = fork();
	if (pid == 0)
	{
		if (s_redir->redir_out || s_redir->append)
			redirect_output(data, s_redir);
		execve(path, argv, envp);
	}
}
