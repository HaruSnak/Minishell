
#include "../../includes/minishell.h"

// 0 = tkn
// 1 = double or simple quote
// 2 = space
void	ft_count_tkn_input(char **input, t_parsing *parsing)
{
	bool	d_quote;
	bool	s_quote;
	int		i;
	int		k;

	i = -1;
	k = -1;
	d_quote = false;
	s_quote = false;
	while (*(input[++i]))
	{
		if (*(input[i]) == '\"' && !s_quote)
			d_quote = !d_quote;
		else if (*(input[i]) == '\'' && !d_quote)
			s_quote = !s_quote;
		if (*(input[i]) == '$' && *(input)[i + 1] != ' ')
			d_quote = !d_quote;
		if (d_quote || s_quote)
			parsing->tkn_count[++k] = 1;
		else if (*(input)[i] == ' ')
			parsing->tkn_count[++k] = 2;
		else
			parsing->tkn_count[++k] = 0;
	}
}
