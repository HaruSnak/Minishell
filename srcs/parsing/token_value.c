
#include "../../includes/minishell.h"

// Add the token value to the parsing structure
void	ft_tkn_value_bis(t_parsing *parsing, int i)
{
	if (i > 0 && parsing->tkn_value[i - 1] == CMD)
		parsing->tkn_value[i] = ARG;
	else if (i > 0 && parsing->tkn_value[i - 1] == ARG)
		parsing->tkn_value[i] = ARG;
	else
		parsing->tkn_value[i] = CMD;
}

int	ft_token_value(t_parsing *parsing)
{
	int	i;

	i = -1;
	parsing->tkn_value = malloc(sizeof(int) * 100);
	while (parsing->tkn[++i] != NULL)
	{
		// parsing->tkn_value[i] = malloc(sizeof(int) * 100);
		if (!ft_strncmp(parsing->tkn[i], "<", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = IN;
		else if (!ft_strncmp(parsing->tkn[i], ">", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = OUT;
		else if (!ft_strncmp(parsing->tkn[i], ">>", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = APPEND;
		else if (!ft_strncmp(parsing->tkn[i], "<<", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = HEREDOC;
		else if (!ft_strncmp(parsing->tkn[i], "|", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = PIPE;
		else if (i > 0 && (!ft_strncmp(parsing->tkn[i - 1], "<", 1)
				|| !ft_strncmp(parsing->tkn[i - 1], ">", 1)))
			parsing->tkn_value[i] = FILE;
		else
			ft_tkn_value_bis(parsing, i);
	}
	return (parsing->tkn_value[i] = 0, 0);
}
