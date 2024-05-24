
#include "../../includes/minishell.h"

void	redirect_output(t_exec **data, t_redir *s_redir)
{
	int		fd_out;

	fd_out = -1;
	if (s_redir->redir_out == TRUE)
		fd_out = open((*data)->outfile, O_WRONLY | O_RDONLY | O_TRUNC, 0777);
	else if (s_redir->append == TRUE)
		fd_out = open((*data)->outfile, O_WRONLY | O_RDONLY | O_APPEND, 0777);
	if (fd_out == -1)
	{
		perror("outfile");
		exit(0);
	}
	dup2(fd_out, STDOUT_FILENO);
}

void	check_access_infile(char *infile, t_exec **data)
{
	if (access(infile, F_OK | R_OK) < 0)
	{
		perror("infile");
		return ;
	}
	(*data)->prevpipe = open(infile, O_RDONLY);
	if ((*data)->prevpipe == -1)
	{
		perror("infile");
		return ;
	}
	dup2((*data)->prevpipe, STDIN_FILENO);
}

void	check_access_outfile(char *outfile, int	tkn_value, t_exec **data)
{
	int		fd;

	if (tkn_value == APPEND)
	{
		// PL
		fd = open(outfile, O_CREAT | O_WRONLY
				| O_RDONLY | O_APPEND, 0777);
	}
	else
	{
		// PL
		fd = open(outfile, O_CREAT | O_WRONLY
				| O_RDONLY | O_TRUNC, 0777);
	}
	if (fd == -1)
	{
		perror("outfile");
		return ;
	}
	close(fd);
	(*data)->outfile = malloc((ft_strlen(outfile) + 1) * sizeof(char));
	if (!(*data)->outfile)
	{
		perror("outfile");
		return ;
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
			check_access_infile(tkn[i + 1], data);
		// else if (*tkn_value[i] == HEREDOC) // last option would be to store
			// heredoc_handling(infile);      // in a hidenfile  
		if (*tkn_value[i] == OUT)
			(*s_redir)->redir_out = TRUE;
		else if (*tkn_value[i] == APPEND)
			(*s_redir)->append = TRUE;
		if (((*s_redir)->redir_out == TRUE || (*s_redir)->append == TRUE)
			&& !(*data)->outfile)
			check_access_outfile(tkn[i + 1], *tkn_value[i], data);
	}
}

	// (*data)->infile = malloc((ft_strlen(infile) + 1) * sizeof(char));
	// if (!(*data)->infile)
	// {
	// 	perror("infile");
	// 	return ;
	// }
	// ft_strlcpy((*data)->infile, infile, ft_strlen(infile) + 1);
