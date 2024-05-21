
#include "../../includes/minishell.h"

void	redirect_output(t_exec **data, int tkn_value)
{
	int		fd_out;

	fd_out = -1;
	if (tkn_value == OUT)
		fd_out = open((*data)->outfile, O_WRONLY | O_RDONLY | O_TRUNC, 0777);
	else if (tkn_value == APPEND)
		fd_out = open((*data)->outfile, O_WRONLY | O_RDONLY | O_APPEND, 0777);
	if (fd_out == -1)
	{
		perror("outfile");
		exit(0);
	}
	dup2(fd_out, STDOUT_FILENO);
}

void	check_access_infile(char *infile, int *tkn_value, t_exec **data)
{
	if (*tkn_value == HEREDOC)
	{
		(*data)->heredoc = TRUE;
		return ; // Unfinished bullshit
	}
	if (access(infile, F_OK | R_OK) < 0)
	{
		perror("infile");
		return ;
	}
	(*data)->infile = malloc((ft_strlen(infile) + 1) * sizeof(char));
	if (!(*data)->infile)
	{
		perror("infile");
		return ;
	}
	ft_strlcpy((*data)->infile, infile, ft_strlen(infile) + 1);
	(*data)->prevpipe = open((*data)->infile, O_RDONLY);
	if ((*data)->prevpipe == -1)
	{
		perror("infile");
		return ;
	}
	dup2((*data)->prevpipe, STDIN_FILENO);
}

void	check_access_outfile(char *outfile, int	*tkn_value, t_exec **data)
{
	int		fd;

	if (*tkn_value == APPEND)
		fd = open(outfile, O_CREAT | O_WRONLY
				| O_RDONLY | O_APPEND, 0777);
	else
		fd = open(outfile, O_CREAT | O_WRONLY
				| O_RDONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("outfile");
		exit(0);
	}
	close(fd);
	(*data)->outfile = malloc((ft_strlen(outfile) + 1) * sizeof(char));
	if (!(*data)->outfile)
	{
		perror("outfile");
		exit(0);
	}
	ft_strlcpy((*data)->outfile, outfile, ft_strlen(outfile) + 1);
}

void	check_for_redirection(char **tkn, int **tkn_value,
		t_exec **data, t_redir **s_redir)
{
	int	i;

	i = -1;
	while (tkn[++i])
	{
		if (*tkn_value[i] == IN)
		{ 
			(*s_redir)->redir_in = TRUE;
			check_access_infile(tkn[i + 1], tkn_value[i], data);
		}
		if (*tkn_value[i] == OUT)
		{
			(*s_redir)->redir_out = TRUE;
			check_access_outfile(tkn[i + 1], tkn_value[i], data);
		}
	}
}
