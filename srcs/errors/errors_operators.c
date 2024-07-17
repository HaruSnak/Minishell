
#include "../../includes/minishell.h"

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

int	error_operator_redic(t_parsing *parsing, int i, int k)
{
	if ((parsing->tkn[i][k] == '<' || parsing->tkn[i][k] == '>')
	&& (parsing->tkn[i + 1] == NULL || parsing->tkn[i + 1][k] == '\0'
	|| parsing->tkn[i][k + 1] == ' ' || parsing->tkn[i + 1][k] == '\0'
	|| parsing->tkn[i + 1][k] == '>' || parsing->tkn[i + 1][k] == '<'
	|| parsing->tkn[i + 1][k] == '|' || parsing->tkn[i + 1][k] == ')'
	|| parsing->tkn[i + 1][k] == '(' || parsing->tkn[i + 1][k] == ';'
	|| parsing->tkn[i + 1][k] == '&'))
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
