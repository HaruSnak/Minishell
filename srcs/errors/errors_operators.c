/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:40:46 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/26 17:00:59 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// The functions below handle errors related to redirection and pipe operators.
// Function for pipe
int	error_operator_pipe(t_parsing *parsing, int i, int k)
{
	if (parsing->tkn[i][k] == '|' && (parsing->tkn[0][0] == '|'
	|| parsing->tkn[i - 1] == NULL || parsing->tkn[i + 1] == NULL
	|| parsing->tkn[i][k + 1] == ' ' || parsing->tkn[i + 1][k] == '\0'
	|| parsing->tkn[i + 1][k] == '>' || parsing->tkn[i + 1][k] == '<'
	|| parsing->tkn[i + 1][k] == '|' || parsing->tkn[i + 1][k] == ')'
	|| parsing->tkn[i + 1][k] == '(' || parsing->tkn[i + 1][k] == ';'
	|| parsing->tkn[i + 1][k] == '&'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			parsing->tkn[i][k]);
		return (parsing->exit_value = 2, -1);
	}
	return (0);
}

// Function for redirection
int	error_operator_redic(t_parsing *parsing, int i, int k)
{
	if (((parsing->tkn[i][k] == '<' && ft_strlen(parsing->tkn[i]) == 1)
		|| (parsing->tkn[i][k] == '>' && ft_strlen(parsing->tkn[i]) == 1)
		|| (parsing->tkn[i][k] == '<' && parsing->tkn[i][k + 1] == '<')
		|| (parsing->tkn[i][k] == '>' && parsing->tkn[i][k + 1] == '>'))
	&& (parsing->tkn[i + 1] == NULL || parsing->tkn[i + 1][k] == '\0'
	|| parsing->tkn[i][k + 1] == ' ' || parsing->tkn[i + 1][k] == '>'
	|| parsing->tkn[i + 1][k] == '<' || parsing->tkn[i + 1][k] == '|'
	|| parsing->tkn[i + 1][k] == ')' || parsing->tkn[i + 1][k] == '('
	|| parsing->tkn[i + 1][k] == ';' || parsing->tkn[i + 1][k] == '&'))
	{
		if (parsing->tkn[i + 1] == NULL)
			printf("minishell: syntax error near unexpected token `newline'\n");
		else
			printf("minishell: syntax error near unexpected token `%c'\n",
				parsing->tkn[i + 1][k]);
		return (parsing->exit_value = 2, -1);
	}
	return (0);
}

// Function for other redirection errors
int	error_operator_other(t_parsing *parsing, int i, int k)
{
	if ((parsing->tkn[i][k] == '<' || parsing->tkn[i][k] == '>')
	&& ((parsing->tkn[i + 1][0] == '.' && parsing->tkn[i + 1][1] != '/')
	|| parsing->tkn[i + 1][k] == '/' || parsing->tkn[i + 1][k] == '~'
	|| parsing->tkn[i + 1][k] == '?' || parsing->tkn[i + 1][k] == '*'))
	{
		if ((parsing->tkn[i + 1][0] == '.' && parsing->tkn[i + 1][1] != '/')
		|| parsing->tkn[i + 1][k] == '/' || parsing->tkn[i + 1][k] == '~')
		{
			printf("minishell: %c: Is a directory\n", parsing->tkn[i + 1][k]);
			return (parsing->exit_value = 2, -1);
		}
		else
		{
			printf("minishell: %c: ambiguous redirect\n",
				parsing->tkn[i + 1][k]);
			return (parsing->exit_value = 2, -1);
		}
	}
	return (0);
}

int	ft_error_operator(t_parsing *parsing)
{
	int		i;
	int		k;

	i = -1;
	k = -1;
	while (parsing->tkn[++i] != NULL)
	{
		while (parsing->tkn[i][++k] != '\0')
		{
			if (parsing->tkn[i][0] == '\'' || parsing->tkn[i][0] == '\"')
				break ;
			if (error_operator_redic(parsing, i, k) == -1)
				return (-1);
			if (error_operator_other(parsing, i, k) == -1)
				return (-1);
			if (error_operator_pipe(parsing, i, k) == -1)
				return (-1);
		}
		k = -1;
	}
	return (0);
}
