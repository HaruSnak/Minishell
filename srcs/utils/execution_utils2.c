
#include "../../includes/minishell.h"

int	cmd_count(int *tkn_value)
{
	int	cmd;
	int i;

	cmd = 0;
	i = -1;
	while (tkn_value[++i])
	{
		if (tkn_value[i] == PIPE)
			cmd++;
	}
	return (cmd + 1);
}

int	there_is_pipeline(int *tkn_value)
{
	int	i;
	int	pipe_cnt;

	i = -1;
	pipe_cnt = 0;
	while (tkn_value[++i])
	{
		if (tkn_value[i] == PIPE)
			pipe_cnt++;
	}
	if (pipe_cnt > 0)
		pipe_cnt++;
	return (pipe_cnt);
}

int	get_argv_cnt(t_cmd_list *list)
{
	int			argv_cnt;
	t_cmd_list	*temp;

	argv_cnt = 0;
	temp = list;
	while (temp->next && (temp->cmd == TRUE || temp->arg == TRUE))
	{
		argv_cnt++;
		temp = temp->next;
	}
	return (argv_cnt);
}

char	**iter_through_list(t_cmd_list *list, char **argv)
{
	int	i;

	i = -1;
	while (list)
	{
		if (list->pipe)
			break ;
		if (list->cmd == TRUE || list->arg == TRUE)
		{
			i++;
			argv[i] = ft_strdup(list->elem);
		}
		list = list->next;
	}
	if (i == 0)
		i++;
	argv[i] = NULL;
	return (argv);
}

char	**set_argv_lst(t_cmd_list *list, char *cmd)
{
	char	**argv;

	while (list && ft_strncmp(list->elem, cmd, ft_strlen(cmd)) != 0)
		list = list->next;
	argv = malloc((get_argv_cnt(list) + 1) * sizeof(char *));
	if (!argv)
	{
		perror("set_argv:");
		return (NULL);//      gestion d'erreur
	}
	argv = iter_through_list(list, argv);
	return (argv);
}
