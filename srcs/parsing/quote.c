
#include "../../includes/minishell.h"

int	ft_return_value_quote(t_parsing *parsing, int k)
{
	char	*tmp_after;
	char	*tmp_env;
	char	*tmp;
	int		i;

	i = parsing->quote->p;
	if (parsing->tkn[k][i] == '$' && parsing->tkn[k][i + 1] == '?'
	&& (parsing->tkn[k][i + 2] == '\0' || parsing->tkn[k][i + 2] == ' '
	|| parsing->tkn[k][i + 2] == '\"'))
	{
		tmp_after = ft_substr(parsing->tkn[k], 0, i);
		tmp = ft_itoa(parsing->exit_value);
		tmp_env = ft_strjoin(tmp_after, tmp);
		free(tmp);
		tmp = ft_strjoin(tmp_env, parsing->tkn[k] + i + 2);
		free(parsing->tkn[k]);
		parsing->tkn[k] = ft_strdup(tmp);
		free(tmp_after);
		free(tmp_env);
		return (free(tmp), 1);
	}
	return (0);
}

int	ft_quote_empty_pipe(t_parsing *parsing, int i)
{

	if (((parsing->tkn[i][0] == '\"'
			&& parsing->tkn[i][1] == '\"') || (parsing->tkn[i][0] == '\''
		&& parsing->tkn[i][1] == '\'')))
	{
		return (1);
	}
	return (0);
}

void	check_quote_heredoc(t_parsing *parsing, int i)
{
	if (i > 0 && parsing->tkn[i - 1][0] == '<' && parsing->tkn[i - 1][1] == '<')
	{
		parsing->quote_heredoc = true;
	}
}

int	ft_check_odd_quote(char *input)
{
	int		i;
	int		s_quote;
	int		d_quote;

	i = -1;
	s_quote = 0;
	d_quote = 0;
	while (input[++i] != '\0')
	{
		if (input[i] == '\'')
			s_quote++;
		else if (input[i] == '\"')
			d_quote++;
	}
	if (s_quote % 2 != 0)
	{
		printf("minishell: Syntax error, unmatched single quote\n");
		return (-1);
	}
	if (d_quote % 2 != 0)
	{
		printf("minishell: Syntax error, unmatched double quote\n");
		return (-1);
	}
	return (0);
}
