
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