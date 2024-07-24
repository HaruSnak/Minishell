/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:40:34 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/24 17:06:02 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Duplicate the file descriptor of the heredoc file
void	ft_dup_heredoc(int heredoc)
{
	heredoc = open("obj/srcs/redirections/heredoc.txt",
			O_CREAT | O_RDONLY, 0777);
	if (dup2(heredoc, STDIN_FILENO) == -1)
	{
		perror("redir_heredoc");
		close(heredoc);
		return ;
	}
	close(heredoc);
}

// Function that handles the SIGINT signal,
//it deletes the heredoc file and reopens stdin if the signal is received
int	ft_g_signal_exit(char *line, int heredoc)
{
	int	fd;

	if (g_signal_number == SIGINT)
	{
		free(line);
		line = NULL;
		close(heredoc);
		ft_delete_file_heredoc();
		fd = open("/dev/tty", O_RDONLY);
		if (fd != 0)
		{
			fprintf(stderr, "Erreur lors de la réouverture de stdin\n");
			exit(1);
		}
		return (1);
	}
	return (0);
}

// Write the heredoc in the file
// If the quote_heredoc is false, the function will replace
// the environment variables with their values
void	ft_write_heredoc(int heredoc, char *line, char **g_env, t_exec *data)
{
	char	*tmp;

	tmp = ft_strdup(line);
	if (data->parsing_ptr->quote_heredoc == false)
	{
		tmp = ft_var_env(data, g_env, tmp);
	}
	write(heredoc, tmp, ft_strlen(tmp));
	write(heredoc, "\n", 1);
	free(tmp);
	tmp = NULL;
	free(line);
	line = NULL;
}

// Function if line is NULL
int	ft_line_null_msg(char *line, int count)
{
	if (line == NULL)
	{
		printf("minishell: warning: here-document at line %d", count);
		printf(" delimited by end-of-file (wanted `EOF')\n");
		return (1);
	}
	return (0);
}
