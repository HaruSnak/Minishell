
#include "../../includes/minishell.h"

void	free_single_list(t_cmd_list *list)
{
	t_cmd_list *next_node;

	while (list)
	{
		next_node = list->next;
		if (list->cmd && list->absolute_path == FALSE)
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

 void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
	{
		free(strs[i]);
		strs[i] = NULL;
	}
	free(strs);
}

void	reset_and_free(t_exec *data)
{
	if (dup2(data->stdin_cpy, STDIN_FILENO) == -1)// error handling
	{
		perror("dup22");
		// return ;
	}
	if (dup2(data->stdout_cpy, STDOUT_FILENO) == -1)// error handling
	{
		perror("dup222");
		// return ;
	}
	close(data->stdin_cpy);
	close(data->stdout_cpy);
	free_data(data);
}
