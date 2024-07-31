/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:37:21 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/31 14:51:28 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_access_infile(t_exec *data, char *infile)
{
	int	fd;

	if (access(infile, F_OK | R_OK) == -1)
	{
		perror("infile access");
		data->parsing_ptr->exit_value = PERMISSION_DENY;
		data->redir_ptr->redir_denied = TRUE;
		return ;
	}
	redirect_infile(data, &fd, infile);
}

void	check_access_outfile(char *outfile, int tkn_value, t_exec *data)
{
	int		fd;

	if (tkn_value == APPEND)
		fd = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("out");
		data->parsing_ptr->exit_value = PERMISSION_DENY;
		data->redir_ptr->redir_denied = TRUE;
		return ;
	}
	close(fd);
	data->outfile = malloc((ft_strlen(outfile) + 1) * sizeof(char));
	malloc_error_ptr(data->outfile, "malloc : check_access_outfile");
	ft_strlcpy(data->outfile, outfile, ft_strlen(outfile) + 1);
}

// Redirect standard in and output if necessary  
int	check_for_redirection(t_exec *data, char **envp)
{
	int	i;
	int	outfile_index;

	i = -1;
	outfile_index = 0;
	while (data->parsing_ptr->tkn[++i])
	{
		if (data->parsing_ptr->tkn_value[i] == HEREDOC)
			heredoc_handling(data, data->parsing_ptr->tkn[i + 1], envp);
		else if (data->parsing_ptr->tkn_value[i] == IN)
			check_access_infile(data, data->parsing_ptr->tkn[i + 1]);
		if (data->parsing_ptr->tkn_value[i] == OUT)
			data->redir_ptr->redir_out = TRUE;
		else if (data->parsing_ptr->tkn_value[i] == APPEND)
			data->redir_ptr->append = TRUE;
		if ((data->redir_ptr->redir_out || data->redir_ptr->append)
			&& !data->outfile && !data->redir_ptr->redir_denied)
		{
			check_access_outfile(data->parsing_ptr->tkn[i + 1],
				data->parsing_ptr->tkn_value[i], data);
			outfile_index = i;
		}
	}
	return (outfile_index);
}
