

#include "../../includes/minishell.h"

void	ft_interpret_bis(t_parsing *parsing, int k, char **envp)
{
	char	*env_cmd;
	int		i;

	i = -1;
	env_cmd = ft_substr(parsing->tkn[k], 1,
			ft_strlen(parsing->tkn[k]) - 1);
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], env_cmd, ft_strlen(env_cmd)) == 0)
		{
			free(parsing->tkn[k]);
			parsing->tkn[k] = ft_strdup(envp[i]
					+ ft_strlen(env_cmd) + 1);
			break ;
		}
	}
	if (parsing->tkn[k][0] == '$')
	{
		free(env_cmd);
		env_cmd = ft_strdup("");
		free(parsing->tkn[k]);
		parsing->tkn[k] = ft_strjoin(parsing->tkn[k], env_cmd);
	}
	free(env_cmd);
}

// Interpret the environment variable in the input
// Replace the environment variable with the value in the input
// Function replace token not in quote
void	ft_interpret_envp(char **envp, t_parsing *parsing)
{
	int		i;
	int		k;

	i = -1;
	k = -1;
	while (parsing->tkn[++k] != NULL)
	{
		while (parsing->tkn[k][++i] != '\0')
		{
			if (parsing->tkn[k][0] != '\'' && parsing->tkn[k][0] != '\"'
				&& parsing->tkn[k][ft_strlen(parsing->tkn[k]) - 1] != '\''
				&& parsing->tkn[k][ft_strlen(parsing->tkn[k]) - 1] != '\"'
				&& parsing->tkn[k][i] == '$' && parsing->tkn[k][i + 1] != '\0'
				&& i + 1 < ft_strlen(parsing->tkn[k]))
			{
				ft_interpret_bis(parsing, k, envp);
			}
		}
		i = -1;
	}
}
