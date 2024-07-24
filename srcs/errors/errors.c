/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:13 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/24 15:55:36 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function for errors in the command execution
int	ft_error_cmd_ext(int fd, char *str)
{
	if (fd == -1)
	{
		perror(str);
		return (-1);
	}
	return (0);
}

// Function for malloc errors on single pointer
void	malloc_error_ptr(void *str, char *msg)
{
	if (!str)
	{
		perror(msg);
		exit(OUT_OF_MEMORY);
	}
}

// Function for malloc errors on double pointer
void	malloc_error_dbl_ptr(char **str, char *msg)
{
	if (!str)
	{
		perror(msg);
		exit(OUT_OF_MEMORY);
	}
}

// Function for quote errors if odd or not
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
