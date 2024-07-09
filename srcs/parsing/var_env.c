

#include "../../includes/minishell.h"

int	ft_return_value_echo(t_parsing *parsing, int k)
{
	char	*tmp_after;
	char	*tmp_env;
	char	*tmp;
	int		i;

	i = -1;
	while (parsing->tkn[k][++i] != '\0')
	{
		if (parsing->tkn[k][i] == '$' && parsing->tkn[k][i + 1] == '?'
		&& (parsing->tkn[k][i + 2] == '\0' || parsing->tkn[k][i + 2] == ' '
		|| parsing->tkn[k][i + 2] == '\"'))
		{
			tmp_after = ft_substr(parsing->tkn[k], 0, i);
			tmp = ft_itoa(parsing->exit_value);
			tmp_env = ft_strjoin(tmp_after, tmp);
			free(tmp);
			tmp = ft_strjoin(tmp_env, parsing->tkn[k] + i + 2);
			free(parsing->tkn[k]);
			parsing->tkn[k] = ft_strdup(tmp);
			free(tmp_after);
			free(tmp_env);
			return (free(tmp), 1);
		}
	}
	return (0);
}

void	ft_interpret_bis(t_parsing *parsing, int k, char **envp)
{
	char	*env_cmd;
	int		i;

	i = -1;
	env_cmd = ft_substr(parsing->tkn[k], 1,
			ft_strlen(parsing->tkn[k]) - 1);
	ft_return_value_echo(parsing, k);
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
		free(parsing->tkn[k]);
		parsing->tkn[k] = ft_strdup("");
	}
	free(env_cmd);
}

void	ft_simple_quote(t_parsing *parsing, int i)
{
	char	*tmp;

	if (parsing->tkn[i][0] == '\'' && parsing->simple_quote)
	{
		tmp = ft_strdup(parsing->tkn[i]);
		free(parsing->tkn[i]);
		parsing->tkn[i] = ft_strtrim(tmp, "\'");
		free(tmp);
		parsing->simple_quote = false;
	}
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
		i = -1;
		while (parsing->tkn[k][++i] != '\0')
		{
			if (parsing->tkn[k][0] != '\'' && parsing->tkn[k][0] != '\"'
				&& parsing->tkn[k][i] == '$' && parsing->tkn[k][i + 1] != '\0'
				&& i + 1 < ft_strlen(parsing->tkn[k]))
			{
				ft_interpret_bis(parsing, k, envp);
				i = -1;
				continue ;
			}
			ft_simple_quote(parsing, k);
		}
	}
}
