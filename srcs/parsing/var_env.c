/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:27 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/24 17:06:40 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Find the environment variable in the input
// Replace the environment variable with the value in the input
void	ft_find_env(t_parsing *parsing, char **envp, int i, char *env)
{
	int	p;

	p = ft_condition_envp(parsing, envp, env, i);
	if (p != -1)
		parsing->tkn[i] = ft_f_null_q(parsing, env, i, parsing->quote->p);
}

void	ft_pre_find(t_parsing *parsing, char **envp, int i, int *k)
{
	char	*env_var;

	env_var = ft_substr(parsing->tkn[i], *k + 1,
			ft_strlen_quote_b(parsing->tkn[i], ' ', *k + 1));
	parsing->quote->p = *k;
	if (ft_return_value_quote(parsing, i) == 1)
	{
		free(env_var);
		return ;
	}
	ft_find_env(parsing, envp, i, env_var);
	free(env_var);
	*k -= 1;
}

void	ft_verify_quote(t_parsing *parsing, int i, int k)
{
	if (parsing->tkn[i][k] == '\"' && !parsing->quote->check_s)
		parsing->quote->check_d = !parsing->quote->check_d;
	else if (parsing->tkn[i][k] == '\'' && !parsing->quote->check_d)
		parsing->quote->check_s = !parsing->quote->check_s;
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
			ft_verify_quote(parsing, i, k);
			if (parsing->quote->check_d && parsing->tkn[i][k] == '$'
			&& parsing->tkn[i][k + 1] != ' '
			&& parsing->tkn[i][k + 1] != '\"'
			&& k + 1 < ft_strlen(parsing->tkn[i]))
				ft_pre_find(parsing, envp, i, &k);
			if (!parsing->quote->check_d && !parsing->quote->check_s
				&& parsing->tkn[i][k] == '$' && parsing->tkn[i][k + 1] != '\0'
			&& parsing->tkn[i][k + 1] != ' '
			&& k + 1 < ft_strlen(parsing->tkn[i]))
				ft_pre_find(parsing, envp, i, &k);
		}
		k = -1;
	}
	return (0);
}

// Check the quotes in the input
// Delete the quotes in the input and set the token value
int	ft_interpret_env(char **envp, t_parsing *parsing)
{
	char	*tmp;
	int		i;

	i = -1;
	ft_env_quote(envp, parsing);
	while (parsing->tkn[++i] != NULL)
	{
		tmp = ft_strdup(parsing->tkn[i]);
		if (ft_quote_empty_pipe(parsing, i) == 1)
		{
			free(tmp);
			continue ;
		}
		if (i > 0 && parsing->tkn[i - 1][0] == '<'
			&& parsing->tkn[i - 1][1] == '<'
			&& (parsing->tkn[i][0] == '\'' || parsing->tkn[i][0] == '\"'))
			parsing->quote_heredoc = true;
		else
			parsing->quote_heredoc = false;
		free(tmp);
	}
	return (0);
}
