/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:37:28 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 13:37:30 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_outfile(t_exec *data, int tkn_i)
{
	if (!ft_strncmp(data->parsing_ptr->tkn[tkn_i], ">", 1)
		|| !ft_strncmp(data->parsing_ptr->tkn[tkn_i], ">>", 2))
	{
		free(data->outfile);
		data->outfile = NULL;
	}
}

bool	handle_single_redir(t_cmd_list *list, t_exec *data)
{
	if (data->redir_ptr->redir_denied)
		return (0);
	else if (data->outfile)
		redirect_output(data, data->redir_ptr);
	if (!ft_strncmp(list->elem, "/usr/bin/echo", 13))
	{
		ft_handle_echo(data->parsing_ptr, data->parsing_ptr->tkn,
			data->parsing_ptr->tkn_value, list->index);
		return (0);
	}
	return (1);
}

void	print_output(int fd)
{
	char	*line;

	if (!fd)
		return ;
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	redirect_infile(t_exec *data, int *fd, char *path)
{
	*fd = open(path, O_CREAT | O_RDONLY, 0644);
	if (*fd == -1)
	{
		perror("outfile open");
		return ;// error handling
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		data->parsing_ptr->exit_value = PERMISSION_DENY;
		perror("redir_infile");
	}
	close(*fd);
}

void	redirect_output(t_exec *data, t_redir *s_redir)
{
	int		fd_out;

	if (data->outfile && access(data->outfile, F_OK | R_OK) == -1)
	{
		perror("access");
		return ;
	}
	if (s_redir->redir_out == TRUE)
		fd_out = open(data->outfile, O_RDWR | O_TRUNC, 0644);
	else if (s_redir->append == TRUE)
		fd_out = open(data->outfile, O_RDWR | O_APPEND, 0644);
	if (fd_out == -1)
	{
		perror("outfile");
		data->parsing_ptr->exit_value = PERMISSION_DENY;
		return ;// error handling
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("redir outfile");// error handling
		data->parsing_ptr->exit_value = DUP_FAILURE;
	}
	close(fd_out);
}
