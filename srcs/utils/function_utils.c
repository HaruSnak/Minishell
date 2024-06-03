
#include "../../includes/minishell.h"

int	ft_count_index(char **input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] != NULL && input[i][0] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

int	ft_condition_replace(t_parsing *parsing, char *input, int i, int *k)
{
	if (input[i] == '\"' && !parsing->quote->check_s)
	{
		parsing->quote->check_d = !parsing->quote->check_d;
		return (0);
	}
	else if (input[i] == '\'' && !parsing->quote->check_d)
	{
		parsing->quote->check_s = !parsing->quote->check_s;
		return (0);
	}
	if ((parsing->quote->check_s == true && parsing->quote->check_d == false)
		|| (parsing->quote->check_s == false
			&& parsing->quote->check_d == true))
		(*k) = i;
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
		PI("l", l);
		parsing->tmp_env[parsing->quote->p] = ft_substr(input, k, l);
		old_ptr = parsing->tmp_env[parsing->quote->p];
		parsing->tmp_env[parsing->quote->p]
			= ft_strjoin(parsing->tmp_env[parsing->quote->p], "\0");
		free(old_ptr);
		parsing->quote->p++;
	}
}

/*void	ft_condit_replace(t_parsing *parsing, char *input,
	char *tmp, int i)
{
	int static	j;

	if (input[i] == ' ' && (parsing->check_s == true
			|| parsing->check_d == true))
		tmp[++j] = '1';
	else
		tmp[++j] = input[i];
}*/

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
	tmp[ft_strlen(tmp) + 1] = '\0'; // tmp[++j] = '\0';
	parsing->tmp_env[ft_count_index(parsing->tmp_env)] = NULL;
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
			PS("tkn[i]", parsing->tkn[i]);
			PI("k", k);
			k++;
		}
	}
	if (parsing->tmp_env != NULL)
		ft_free_d_ptr((void ***)&parsing->tmp_env);
}
