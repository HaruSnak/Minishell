

#include "../../includes/minishell.h"

void	ft_fill_envp(t_exec **data, char **envp)
{
	int	i;
	int	envp_len;

	envp_len = 0;
	i = -1;
	while (envp[envp_len])
		envp_len++;

	(*data)->envp = malloc((envp_len + 1) * sizeof(char *));
	if (!(*data)->envp)
		return ;
	while (envp[++i])
		(*data)->envp[i] = ft_strdup(envp[i]);
	(*data)->envp[i] = NULL;
}
