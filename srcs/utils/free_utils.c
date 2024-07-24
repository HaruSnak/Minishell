/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:48 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/24 11:04:45 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_single_list(t_cmd_list *list)
{
	t_cmd_list	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list->elem);
		list->elem = NULL;
		free(list);
		list = NULL;
		list = next_node;
	}
}

void	free_list(t_cmd_list *list)
{
	t_cmd_list	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list->elem);
		list->elem = NULL;
		free(list);
		list = NULL;
		list = next_node;
	}
}

void	free_data(t_exec *data)
{
	if (data->redir_ptr->here_doc)
		ft_delete_file_heredoc();
	if (data->outfile)
	{
		free(data->outfile);
		data->outfile = NULL;
	}
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
	strs = NULL;
}

void	reset_and_free(t_exec *data)
{
	if (dup2(data->stdin_cpy, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return ;
	}
	if (dup2(data->stdout_cpy, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return ;
	}
	close(data->stdin_cpy);
	close(data->stdout_cpy);
	if (data->pidz)
	{
		free(data->pidz);
		data->pidz = NULL;
	}
	free_data(data);
	data = NULL;
}
