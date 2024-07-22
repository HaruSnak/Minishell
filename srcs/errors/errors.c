/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:13 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/22 10:33:44 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error_cmd_ext(int fd, char *str)
{
	if (fd == -1)
	{
		perror(str);
		return (-1);
	}
	return (0);
}

void	malloc_error_ptr(void *str, char *msg)
{
	if (!str)
	{
		perror(msg);
		exit(OUT_OF_MEMORY);
	}
}

void	malloc_error_dbl_ptr(char **str, char *msg)
{
	if (!str)
	{
		perror(msg);
		exit(OUT_OF_MEMORY);
	}
}

int	ft_error_quote(t_parsing *parsing, int s_quote, int d_quote)
{
	if (s_quote % 2 != 0)
	{
		printf("minishell: Syntax error, unmatched single quote\n");
		parsing->quote->check_s = FALSE;
		return (-1);
	}
	if (d_quote % 2 != 0)
	{
		printf("minishell: Syntax error, unmatched double quote\n");
		parsing->quote->check_d = FALSE;
		return (-1);
	}
	return (0);
}
