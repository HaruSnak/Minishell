
#include "../../includes/minishell.h"

void	free_single_list(t_cmd_list *list)
{
	t_cmd_list *next_node;

	while (list)
	{
		next_node = list->next;
		if (list->cmd && list->relative_path == FALSE)
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
		if (list->cmd)
			free(list->elem);
		free(list);
		list = next_node;
	}
}

void	free_data(t_exec *data)
{
	if (data->redir_ptr->here_doc)
		ft_delete_file_heredoc();
	if (data->outfile)
		free(data->outfile);
}
