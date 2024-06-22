#include "../../includes/minishell.h"

bool	is_builtins(char *cmd, t_parsing *data, char **envp)
{
	if (!ft_strncmp(cmd, "exit", 4) || !ft_strncmp(cmd, "cd", 2)
		|| !ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5))
	{
		builtins_exec(data, envp);
		// free argv which is tkn[]
		return (TRUE);
	}
	else
		return (FALSE);
}
