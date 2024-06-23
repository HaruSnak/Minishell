
#include "../../includes/minishell.h"

void	free_single_list(t_cmd_list *list)
{
	t_cmd_list *next_node;

	while (list)
	{
		next_node = list->next;
		if (list->relative_path)
			free(list->elem);
		free(list);
		list = next_node;
	}
}

void	free_list(t_cmd_list *list)
{
	t_cmd_list *next_node;

	while (list)
	{
		next_node = list->next;
		free(list);
		list = next_node;
	}
}

