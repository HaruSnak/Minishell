

#include "../../includes/minishell.h"

char	*ft_f_null_q(t_parsing *parsing, char *env_var, int i, int p)
{
	char	*tmp_after;
	char	*tmp_before;

	tmp_after = ft_substr(parsing->tkn[i], 0, p);
	tmp_before = ft_strjoin(tmp_after,
			parsing->tkn[i] + ft_strlen(tmp_after) + ft_strlen(env_var) + 1);
	free(parsing->tkn[i]);
	parsing->tkn[i] = ft_strdup(tmp_before);
	free(tmp_after);
	free(tmp_before);
	return (parsing->tkn[i]);
}

// Find the environment variable in the input
// Replace the environment variable with the value in the input
void	ft_find_env(t_parsing *parsing, char **envp, int i, char *env_var)
{
	char	*tmp_after;
	char	*tmp_env;
	char	*tmp;
	int		p;

	p = -1;
	while (envp[++p] != NULL)
	{
		if (ft_strncmp(envp[p], env_var, ft_strlen(env_var)) == 0)
		{
			tmp_after = ft_substr(parsing->tkn[i], 0, parsing->quote->p);
			tmp_env = ft_strjoin(tmp_after, envp[p] + ft_strlen(env_var) + 1);
			tmp = ft_strjoin(tmp_env, parsing->tkn[i] + ft_strlen(tmp_env) + 1);
			free(parsing->tkn[i]);
			parsing->tkn[i] = ft_strdup(tmp);
			free(tmp_after);
			free(tmp_env);
			free(tmp);
			p = -1;
			break ;
		}
	}
	if (p != -1)
		parsing->tkn[i] = ft_f_null_q(parsing, env_var, i, parsing->quote->p);
}

void	ft_pre_find(t_parsing *parsing, char **envp, int i, int k)
{
	char	*env_var;

	if (parsing->tkn[i][0] == '\"' && parsing->tkn[i][k] == '$')
	{
		env_var = ft_substr(parsing->tkn[i], k + 1,
				ft_strlen_quote(parsing->tkn[i], ' ', k + 1));
		printf("1parsing->tkn[i] = %s\n", parsing->tkn[i]);
		/*if (ft_strchr(env_var, '\"') != NULL)
			env_var = ft_strtrim(env_var, "\"");
		else if (ft_strchr(env_var, ' ') != NULL)
			env_var = ft_strtrim(env_var, " ");*/
		if (ft_strlen(parsing->tkn[i]) == (ft_strlen(env_var) + 3))
		{
			free(parsing->tkn[i]);
			parsing->tkn[i] = ft_strjoin("$", env_var);
			free(env_var);
			return ;
		}
		parsing->quote->p = k;
		printf("2parsing->tkn[i] = %s\n", parsing->tkn[i]);
		if (ft_return_value_echo(parsing, i) == 1)
		{
			free(env_var);
			return ;
		}
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

void	check_quote_heredoc(t_parsing *parsing, int i)
{
	if (i > 0 && parsing->tkn[i - 1][0] == '<' && parsing->tkn[i - 1][1] == '<')
	{
		parsing->quote_heredoc = true;
	}
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
		if (parsing->tkn[i][0] == '\"')
		{
			free(parsing->tkn[i]);
			parsing->tkn[i] = ft_strtrim(tmp, "\"");
			check_quote_heredoc(parsing, i);
			printf("parsing->tkn = %s\n", parsing->tkn[i - 1]);
		}
		else if (parsing->tkn[i][0] == '\'')
		{
			parsing->double_quote = true;
		}
		free(tmp);
	}
	return (0);
}
