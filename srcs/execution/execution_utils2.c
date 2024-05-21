
#include "../../includes/minishell.h"

int	cmd_count(int **tkn_value)
{
	int	cmd;
	int i;

	cmd = 0;
	i = -1;
	while (tkn_value[++i])
	{
		if (*tkn_value[i] == PIPE)
			cmd++;
	}
	return (cmd + 1);
}

bool there_is_pipeline(int **tkn_value)
{
	int	i;

	i = -1;
	while (tkn_value[++i])
	{
		if (tkn_value[i] == PIPE)
			return (TRUE);
	}
	return (FALSE);
}
