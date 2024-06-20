
#include "../../includes/minishell.h"

// Count the number of elements in a 2D array
int	ft_count_index(char **input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] != NULL)
	{
		count++;
		i++;
	}
	return (count);
}

// Count the number of characters in a string until a specific character
int	ft_strlen_quote(char *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i] != c && str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
	{
		count++;
		i++;
	}
	return (count);
}
