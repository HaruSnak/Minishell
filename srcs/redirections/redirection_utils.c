
#include "../../includes/minishell.h"

void	check_and_reset_outfile(t_exec *data, int i)
{
	if (!ft_strncmp(data->parsing_ptr->tkn[i], ">", 1)
	|| !ft_strncmp(data->parsing_ptr->tkn[i], ">>", 2))
	{
		free(data->outfile);
		data->outfile = NULL;
	}
}

void	redirect_infile(int *fd, char *path)
{
	*fd = open(path, O_CREAT | O_RDONLY, 0777);
	if (*fd == -1)
	{
		perror("outfile open");
		return ;// error handling
	}	
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		perror("redir_infile");
		close(*fd);
		return ;// error handling
	}
	close(*fd);
}
