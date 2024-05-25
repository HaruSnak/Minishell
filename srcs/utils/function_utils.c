
#include "../../includes/minishell.h"

int	ft_count_index(char **input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] != NULL && input[i][0] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}
