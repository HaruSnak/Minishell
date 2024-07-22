/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:37:14 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/22 10:38:56 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_delete_quote_bis(t_parsing *parsing, int i, int *k, int stack)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	if ((parsing->tkn[i][*k] == '\"' || parsing->tkn[i][*k] == '\'')
	&& (parsing->quote->check_d || parsing->quote->check_s))
	{
		stack = ft_strlen_quote(parsing, parsing->tkn[i], '\0', *k + 1);
		tmp = ft_substr(parsing->tkn[i], 0, *k);
		tmp2 = ft_substr(parsing->tkn[i], *k + 1,
				ft_strlen_quote(parsing, parsing->tkn[i], '\0', *k + 1));
		tmp3 = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		tmp = ft_substr(parsing->tkn[i], *k
				+ ft_strlen_quote(parsing, parsing->tkn[i], '\0', *k + 1) + 2,
				ft_strlen(parsing->tkn[i]) - *k - 1
				- ft_strlen_quote(parsing, parsing->tkn[i], '\0', *k + 1));
		free(parsing->tkn[i]);
		parsing->tkn[i] = ft_strjoin(tmp3, tmp);
		free(tmp);
		free(tmp3);
		return (*k += stack - 1, 1);
	}
	return (-1);
}

void	ft_delete_quote(t_parsing *parsing)
{
	int		i;
	int		k;
	int		stack;

	i = -1;
	stack = 0;
	while (parsing->tkn[++i] != NULL)
	{
		k = -1;
		while (parsing->tkn[i][++k] != '\0')
		{
			ft_verify_quote(parsing, i, k);
			if (ft_delete_quote_bis(parsing, i, &k, stack) == 1)
			{
				parsing->quote->check_d = false;
				parsing->quote->check_s = false;
			}
		}
	}
}
