
#include "../../includes/minishell.h"

int	get_argv_cnt(t_cmd_list *list)
{
	int			argv_cnt;
	t_cmd_list	*temp;

	argv_cnt = 0;
	temp = list;
	while (temp && (temp->cmd == TRUE || temp->arg == TRUE))
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
			argv[i] = ft_strdup(list->elem);// error handling
			if(!argv[i])
				malloc_error();
		}
		list = list->next;
	}
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
		malloc_error();
	argv = iter_through_list(list, argv);
	return (argv);
}
