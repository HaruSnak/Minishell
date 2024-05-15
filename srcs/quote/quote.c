/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:03:36 by shmoreno          #+#    #+#             */
/*   Updated: 2024/05/15 17:03:54 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_quote(char **input)
{
	int	k;
	int	i;

	k = 0;
	i = -1;
	while (input[++i] != NULL)
	{
		if (ft_strchr(input[i], '\''))
		{
			if (ft_strchr(input[i], '\'') != ft_strrchr(input[i], '\''))
			{

			}
			else if (ft_strchr(input[i], '\'') == ft_strrchr(input[i], '\''))
			{
				input[i] = ft_strtrim(input[i], "\'");
				input[k] = ft_strdup(input[i]);
				k++;
			}
		}
	}
	return (input);
}
