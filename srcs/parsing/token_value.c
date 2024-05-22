

#include "../../includes/minishell.h"

void	ft_test(struct s_parsing *parsing, int i)
{
	if (i > 0 && parsing->tkn_value[i - 1][0] == CMD)
		parsing->tkn_value[i][0] = ARG;
	else if (i > 0 && parsing->tkn_value[i - 1][0] == ARG)
		parsing->tkn_value[i][0] = ARG;
	else
		parsing->tkn_value[i][0] = CMD;
}

int	ft_token_value(struct s_parsing *parsing)
{
	int	i;

	i = -1;
	parsing->tkn_value = malloc(sizeof(int *) * 100);
	while (parsing->tkn[++i] != NULL)
	{
		parsing->tkn_value[i] = malloc(sizeof(int) * 100);
		if (!ft_strncmp(parsing->tkn[i], "<", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i][0] = IN;
		else if (!ft_strncmp(parsing->tkn[i], ">", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i][0] = OUT;
		else if (!ft_strncmp(parsing->tkn[i], ">>", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i][0] = APPEND;
		else if (!ft_strncmp(parsing->tkn[i], "<<", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i][0] = HEREDOC;
		else if (!ft_strncmp(parsing->tkn[i], "|", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i][0] = PIPE;
		else if (i > 0 && (!ft_strncmp(parsing->tkn[i - 1], "<", 1)
				|| !ft_strncmp(parsing->tkn[i - 1], ">", 1)))
			parsing->tkn_value[i][0] = FILE;
		else
			ft_test(parsing, i);
	}
	return (parsing->tkn_value[i] = NULL, 0);
}
