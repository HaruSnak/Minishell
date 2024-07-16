

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

int	ft_error_quote(int s_quote, int d_quote)
{
	if (s_quote % 2 != 0)
	{
		printf("minishell: Syntax error, unmatched single quote\n");
		return (-1);
	}
	if (d_quote % 2 != 0)
	{
		printf("minishell: Syntax error, unmatched double quote\n");
		return (-1);
	}
	return (0);
}
