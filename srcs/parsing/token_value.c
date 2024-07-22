/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:20 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 17:02:47 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Add the token value to the parsing structure
void	ft_tkn_value_bis(t_parsing *parsing, int i)
{
	if (i > 0 && (!ft_strncmp(parsing->tkn[i - 1], "<", 1)
			|| !ft_strncmp(parsing->tkn[i - 1], ">", 1)))
		parsing->tkn_value[i] = FILE;
	else if (i > 0 && parsing->tkn_value[i - 1] == CMD)
		parsing->tkn_value[i] = ARG;
	else if (i > 0 && parsing->tkn_value[i - 1] == ARG)
		parsing->tkn_value[i] = ARG;
	else
		parsing->tkn_value[i] = CMD;
}

int	ft_token_value(t_parsing *parsing)
{
	int	i;

	i = -1;
	parsing->tkn_value = malloc(sizeof(int)
			* (ft_count_index(parsing->tkn) + 1));
	malloc_error_ptr(parsing->tkn_value, "malloc : ft_token_value");
	while (parsing->tkn[++i] != NULL)
	{
		if (ft_strlen(parsing->tkn[i]) == 0)
			parsing->tkn_value[i] = ARG;
		else if (!ft_strncmp(parsing->tkn[i], "<", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = IN;
		else if (!ft_strncmp(parsing->tkn[i], ">", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = OUT;
		else if (!ft_strncmp(parsing->tkn[i], ">>", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = APPEND;
		else if (!ft_strncmp(parsing->tkn[i], "<<", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = HEREDOC;
		else if (!ft_strncmp(parsing->tkn[i], "|", ft_strlen(parsing->tkn[i])))
			parsing->tkn_value[i] = PIPE;
		else
			ft_tkn_value_bis(parsing, i);
	}
	return (parsing->tkn_value[i] = 0, 0);
}
