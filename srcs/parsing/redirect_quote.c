/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:40:53 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 14:11:53 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Check if the character is a quote and if it is,
// check if it is a single or double quote
// and if it is, add a space after the quote
void	ft_condit_quote(char *tmp_redir, int *i, int *k, char *tmp_quote)
{
	static bool	check_s;
	static bool	check_d;

	if (tmp_redir[*i] == '\"' && !check_s)
		check_d = !check_d;
	else if (tmp_redir[*i] == '\'' && !check_d)
		check_s = !check_s;
	if (((tmp_redir[*i] == '\'' && (tmp_redir[*i + 1] == '\''
					|| tmp_redir[*i + 1] == '\"') && (!check_d && !check_s))
			|| (tmp_redir[*i] == '\"' && (tmp_redir[*i + 1] == '\"'
					|| tmp_redir[*i + 1] == '\'') && (!check_d && !check_s)))
		|| ((tmp_redir[*i] == '\"' || tmp_redir[*i] == '\'')
			&& (tmp_redir[*i + 1] >= 35 && tmp_redir[*i + 1] <= 126)
			&& (!check_d && !check_s)) || (tmp_redir[*i] >= 35
			&& tmp_redir[*i] <= 126 && (tmp_redir[*i + 1] == '\"'
				|| tmp_redir[*i + 1] == '\'') && (!check_d && !check_s)))
	{
		tmp_quote[(*k)++] = tmp_redir[*i];
		tmp_quote[(*k)++] = ' ';
	}
	else
		tmp_quote[(*k)++] = tmp_redir[*i];
}

void	ft_condit_redirect(char *input, int *i, int *k, char *tmp)
{
	if (((input[*i] == '>' || input[*i] == '<' || input[*i] == '|')
			&& (input[*i + 1] != ' ' || (*i > 0 && input[*i - 1] != ' ')))
		|| ((input[*i] == '<' && input[*i + 1] == '<'
				&& input[*i + 2] != ' ' && *i > 0 && input[*i - 1] != ' '))
		|| (input[*i] == '>' && input[*i + 1] == '>'
			&& input[*i + 2] != ' ' && *i > 0 && input[*i - 1] != ' '))
	{
		tmp[*k] = ' ';
		(*k)++;
		tmp[*k] = input[*i];
		if (input[*i + 1] == '>' || input[*i + 1] == '<')
		{
			(*k)++;
			tmp[*k] = input[*i + 1];
			(*i)++;
		}
		(*k)++;
		tmp[*k] = ' ';
		(*k)++;
	}
	else
	{
		tmp[*k] = input[*i];
		(*k)++;
	}
}

void	ft_boucle_redirect(char *input, int *i, int *k, char *tmp_redir)
{
	static bool	check_s;
	static bool	check_d;

	while (input[++(*i)] != '\0')
	{
		if (input[*i] == '\"' && !check_s)
			check_d = !check_d;
		else if (input[*i] == '\'' && !check_d)
			check_s = !check_s;
		if (!check_s && !check_d)
			ft_condit_redirect(input, i, k, tmp_redir);
		else
		{
			tmp_redir[*k] = input[*i];
			(*k)++;
		}
	}
}

char	*ft_separe_operator(char *input)
{
	char	*tmp_redir;
	int		i;
	int		k;

	i = -1;
	k = 0;
	tmp_redir = malloc(sizeof(char) * ft_strlen(input) + 100);
	malloc_error_ptr(tmp_redir, "malloc : ft_separe_operator");
	ft_boucle_redirect(input, &i, &k, tmp_redir);
	tmp_redir[k] = '\0';
	free(input);
	input = NULL;
	return (tmp_redir);
}
