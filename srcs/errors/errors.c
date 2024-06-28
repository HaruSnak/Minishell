
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
