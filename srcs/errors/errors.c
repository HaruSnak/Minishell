

#include "../../includes/minishell.h"

int	ft_error_cmd_ext(int fd, char *str)
{
	if (fd == -1)
	{
		perror(str);
		return (-1);
	}
	return (0);
}

/*void	ft_error_malloc(char *str)
{
	if (!str)
	{
		perror("malloc ");
		exit(EXIT_FAILURE);
	}
}*/
