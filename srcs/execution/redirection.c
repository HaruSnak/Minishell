
#include "../../includes/minishell.h"

void	check_access_infile(char *infile, int *tkn_value, t_exec **data)
{
	if (*tkn_value == HEREDOC)
	{
		(*data)->heredoc = TRUE;
		return ;
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

void	redirection(char **tkn, int **tkn_value,
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
