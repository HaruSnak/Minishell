
#include "../../includes/minishell.h"

// Check if the character is a quote and if it is,
// check if it is a single or double quote
// and if it is, add a space after the quote
// and copy the character to the tmp_quote variable
// and add a space after the quote
int	ft_condition_replace(t_parsing *parsing, char *input, int i, int *k)
{
	if (input[i] == '\"' && !parsing->quote->check_s)
	{
		parsing->quote->check_d = !parsing->quote->check_d;
		(*k) = i;
		return (0);
	}
	else if (input[i] == '\'' && !parsing->quote->check_d)
	{
		parsing->quote->check_s = !parsing->quote->check_s;
		(*k) = i;
		return (0);
	}
	return (-1);
}

void	ft_copy_var(t_parsing *parsing, char *input, int i, int k)
{
	char		*old_ptr;
	int			l;

	if ((input[i + 1] == '\'' && parsing->quote->check_s)
		|| (input[i + 1] == '\"' && parsing->quote->check_d))
	{
		l = i - k + 2;
		parsing->tmp_env[parsing->quote->p] = ft_substr(input, k, l);
		old_ptr = parsing->tmp_env[parsing->quote->p];
		parsing->tmp_env[parsing->quote->p]
			= ft_strjoin(parsing->tmp_env[parsing->quote->p], "\0");
		free(old_ptr);
		parsing->quote->p++;
	}
}

char	*ft_replace_espace(char *input, t_parsing *parsing)
{
	char	*tmp;
	int		i;
	int		k;
	int		j;

	i = -1;
	k = 0;
	j = -1;
	tmp = malloc(sizeof(char) * ft_strlen(input) + 1);
	parsing->tmp_env = malloc(sizeof(char *) * 100);
	parsing->quote->p = 0;
	while (input[++i] != '\0')
	{
		ft_condition_replace(parsing, input, i, &k);
		if (input[i] == ' ' && (parsing->quote->check_s
				|| parsing->quote->check_d))
			tmp[++j] = '1';
		else
			tmp[++j] = input[i];
		ft_copy_var(parsing, input, i, k);
	}
	tmp[++j] = '\0';
	parsing->tmp_env[parsing->quote->p] = NULL;
	return (tmp);
}

void	ft_delete_espace(t_parsing *parsing)
{
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (parsing->tkn[++i] != NULL)
	{
		if (ft_strchr(parsing->tkn[i], '\'')
			!= ft_strrchr(parsing->tkn[i], '\'')
			|| ft_strchr(parsing->tkn[i], '\"')
			!= ft_strrchr(parsing->tkn[i], '\"'))
		{
			ft_strlcpy(parsing->tkn[i], parsing->tmp_env[k],
				ft_strlen(parsing->tmp_env[k]) + 1);
			k++;
		}
	}
	if (parsing->tmp_env != NULL)
		ft_free_d_ptr((void ***)&parsing->tmp_env);
}
