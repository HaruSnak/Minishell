
#include "../../includes/minishell.h"

void	ft_error_cmd_ext(char *error, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(status);
}

void	ft_free_data(t_exec *data, t_parsing *parsing)
{
	ft_free_d_ptr((void ***)&parsing->path);
	ft_free_d_ptr((void ***)&data->envp);
	free(data->outfile);
	free(data->pidz);
	// free(data);
	// free(s_redir);
}

// Free a double pointer and set it to NULL
void	ft_free_d_ptr(void ***ptr)
{
	int	i;
	int	count;

	i = 0;
	count = ft_count_index((char **)*ptr);
	while (i < count)
	{
		free((*ptr)[i]);
		i++;
	}
	free(*ptr);
	*ptr = NULL;
}

// verify_operations function commands free
void	ft_end_verify(t_parsing *parsing)
{
	ft_free_d_ptr((void ***)&parsing->tkn);
	free(parsing->tkn_value);
	free(parsing->tkn_cpy);
}

void	ft_free_and_compact(char **str, int index, int size)
{
	int	i;

	i = index;
	free(str[index]);
	while (i < size - 1)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[size - 1] = NULL;
}
