/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:54:07 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 16:54:09 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_condition_envp(t_parsing *parsing, char **envp, char *env, int i)
{
	char	*tmp_after;
	char	*tmp_env;
	char	*tmp;
	int		p;

	p = -1;
	while (envp[++p] != NULL)
	{
		if (ft_strncmp(envp[p], env, ft_strlen(env)) == 0
			&& envp[p][ft_strlen(env)] == '=')
		{
			tmp_after = ft_substr(parsing->tkn[i], 0, parsing->quote->p);
			tmp_env = ft_strjoin(tmp_after, envp[p] + ft_strlen(env) + 1);
			free(tmp_after);
			tmp = ft_strjoin(tmp_env, parsing->tkn[i]
					+ parsing->quote->p + ft_strlen(env) + 1);
			free(tmp_env);
			free(parsing->tkn[i]);
			parsing->tkn[i] = ft_strdup(tmp);
			free(tmp);
			p = -1;
			break ;
		}
	}
	return (p);
}
