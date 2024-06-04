

#include "../../includes/minishell.h"

// Find the environment variable in the input
// Replace the environment variable with the value in the input
void	ft_find_env(t_parsing *parsing, char **envp, int i, char *env_var)
{
	char	*tmp_after;
	char	*tmp_env;
	char	*tmp_before;
	int		p;

	p = -1;
	while (envp[++p] != NULL)
	{
		if (ft_strncmp(envp[p], env_var, ft_strlen(env_var)) == 0)
		{
			tmp_after = ft_substr(parsing->tkn[i], 0, parsing->quote->p);
			tmp_env = ft_strjoin(tmp_after, envp[p] + ft_strlen(env_var) + 1);
			tmp_before = ft_strjoin(tmp_env, parsing->tkn[i]
					+ ft_strlen(tmp_env) + 1);
			free(parsing->tkn[i]);
			parsing->tkn[i] = ft_strdup(tmp_before);
			free(tmp_after);
			free(tmp_env);
			free(tmp_before);
			break ;
		}
	}
}

void	ft_pre_find(t_parsing *parsing, char **envp, int i, int k)
{
	char	*env_var;

	if (parsing->tkn[i][0] == '\"' && parsing->tkn[i][k] == '$'
		&& k > 0 && parsing->tkn[i][k - 1] != '\\')
	{
		env_var = ft_substr(parsing->tkn[i], k + 1,
				ft_strlen_quote(parsing->tkn[i], ' ', k + 1));
		if (ft_strchr(env_var, '\"') != NULL)
			env_var = ft_strtrim(env_var, "\"");
		else if (ft_strchr(env_var, ' ') != NULL)
			env_var = ft_strtrim(env_var, " ");
		parsing->quote->p = k;
		ft_find_env(parsing, envp, i, env_var);
		free(env_var);
	}
}

int	ft_env_quote(char **envp, t_parsing *parsing)
{
	int		i;
	int		k;

	i = -1;
	k = -1;
	while (parsing->tkn[++i] != NULL)
	{
		while (parsing->tkn[i][++k] != '\0')
		{
			ft_pre_find(parsing, envp, i, k);
		}
		k = -1;
	}
	return (0);
}

// Check the quotes in the input
// Delete the quotes in the input and set the token value
int	ft_check_quote(char **envp, t_parsing *parsing)
{
	char	*tmp;
	int		i;

	i = -1;
	ft_env_quote(envp, parsing);
	while (parsing->tkn[++i] != NULL)
	{
		tmp = ft_strdup(parsing->tkn[i]);
		if (parsing->tkn[i][0] == '\'')
		{
			free(parsing->tkn[i]);
			parsing->tkn[i] = ft_strtrim(tmp, "\'");
		}
		else if (parsing->tkn[i][0] == '\"')
		{
			free(parsing->tkn[i]);
			parsing->tkn[i] = ft_strtrim(tmp, "\"");
		}
		free(tmp);
	}
	return (0);
}
