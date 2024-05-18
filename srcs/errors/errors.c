

#include "../../includes/minishell.h"

void	ft_error_cmd_ext(char *error, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(status);
}

void	ft_free_d_ptr(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	ft_end_verify(char **input, struct s_parsing *parsing)
{
	add_history(*input);
	ft_free_d_ptr((void **)parsing->tkn);
	ft_free_d_ptr((void **)parsing->tkn_value);
	free(parsing->tkn_cpy);
	free(*input);
}
