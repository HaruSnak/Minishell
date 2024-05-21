
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

int	ft_condition_replace(char *input, int i, bool *check_s, bool *check_d)
{
	if (input[i] == '\"' && !(*check_s))
	{
		*check_d = !(*check_d);
		printf("ici\n");
		return (0);
	}
	else if (input[i] == '\'' && !(*check_d))
	{
		*check_s = !(*check_s);
		return (0);
	}
	return (-1);
}

char	*ft_replace_espace(char *input, struct s_parsing *parsing)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;
	int 	p;
	int 	l;
	bool	check_s;
	bool	check_d;

	i = -1;
	j = -1;
	k = 0;
	l = 0;
	p = 0;
	check_s = false;
	check_d = false;
	if (ft_strchr(input, '\'') != ft_strrchr(input, '\'')
		|| ft_strchr(input, '\"') != ft_strrchr(input, '\"'))
	{
		tmp = malloc(sizeof(char) * ft_strlen(input) + 1);
		parsing->tmp_env = malloc(sizeof(char *) * 100);
		while (input[++i] != '\0')
		{
			if (ft_condition_replace(input, i, &check_s, &check_d) == 0)
			{
				if ((check_s == true && check_d == false)
					|| (check_s == false && check_d == true))
					k = i;
			}
			if (input[i] == ' ' && (check_s == true || check_d == true))
				tmp[++j] = '1';
			else
				tmp[++j] = input[i];
			printf("tmp = %c\n", tmp[j]);
			if ((input[i + 1] == '\'' && check_s)
				|| (input[i + 1] == '\"' && check_d))
			{
				l = i - k + 2;
				printf("l = %d\n", l);
				parsing->tmp_env[p] = ft_substr(input, k, l);
				char *old_ptr = parsing->tmp_env[p];
				parsing->tmp_env[p] = ft_strjoin(parsing->tmp_env[p], "\0");
				free(old_ptr);
				p++;
			}
		}
		tmp[++j] = '\0';
		parsing->tmp_env[p] = NULL;
	}
	return (tmp);
}

void	ft_delete_espace(struct s_parsing *parsing)
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
			printf("parsing->tkn[i] = %s\n", parsing->tkn[i]);
			printf("k = %d\n", k);
			k++;
		}
	}
	if (parsing->tmp_env != NULL)
		ft_free_d_ptr((void ***)&parsing->tmp_env);
}
