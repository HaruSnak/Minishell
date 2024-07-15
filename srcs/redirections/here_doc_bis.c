

#include "../../includes/minishell.h"

void	ft_dup_heredoc(int heredoc)
{
	heredoc = open("obj/srcs/redirections/heredoc.txt",
			O_CREAT | O_RDONLY, 0777);
	if (dup2(heredoc, STDIN_FILENO) == -1)
	{
		perror("redir_heredoc");
		close(heredoc);
		return ; // error handling
	}
	close(heredoc);
}

int	ft_g_signal_exit(char *line, int heredoc)
{
	int	fd;

	if (g_signal_number == SIGINT)
	{
		free(line);
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

void	ft_write_heredoc(int heredoc, char *line, char **g_env, t_exec *data)
{
	if (data->parsing_ptr->quote_heredoc == false)
		line = ft_var_env(data, g_env, line);
	else
		data->parsing_ptr->quote_heredoc = false;
	write(heredoc, line, ft_strlen(line));
	write(heredoc, "\n", 1);
}

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
