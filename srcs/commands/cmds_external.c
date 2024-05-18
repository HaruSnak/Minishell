

#include "../../includes/minishell.h"

int	ft_handle_empty_cmd(char **input)
{
	int	i;

	i = 0;
	if (*input[0] == '\0')
		return (0);
	while ((*input)[i] != '\0')
	{
		if (((*input)[i] >= 9 && (*input)[i] <= 13) || (*input)[i] == 32)
			i++;
		else
			return (-1);
	}
	return (0);
}

void	ft_multi_args_exit(struct s_parsing *parsing, int i, char **tmp)
{
	while (tmp[1][++i] != '\0')
	{
		if (tmp[1][i] < '0' || tmp[1][i] > '9')
		{
			printf("minishell: exit: %s: numeric argument required\n", tmp[1]);
			if (parsing->tmp_env != NULL)
				ft_free_d_ptr((void **)parsing->tmp_env);
			ft_free_d_ptr((void **)tmp);
			exit(255);
		}
	}
}

int	ft_handle_exit(char **input, struct s_parsing *parsing)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(*input, ' ');
	if (ft_strncmp(tmp[0], "exit", ft_strlen(tmp[0])) == 0 && tmp[1] == NULL)
	{
		if (parsing->tmp_env != NULL)
			ft_free_d_ptr((void **)parsing->tmp_env);
		ft_free_d_ptr((void **)tmp);
		exit (parsing->exit_value);
	}
	else if (ft_strncmp(tmp[0], "exit",
			ft_strlen(tmp[0])) == 0 && tmp[1] != NULL)
	{
		ft_multi_args_exit(parsing, i, tmp);
		exit(ft_atoi(tmp[1]));
	}
	ft_free_d_ptr((void **)tmp);
	return (-1);
}

int	ft_return_value_echo(struct s_parsing *parsing, char *input, int i, int j)
{
	char	**tmp;

	tmp = ft_split(input, ' ');
	while (tmp[++j] != NULL)
	{
		while (tmp[j][++i] != '\0')
		{
			if (tmp[j][i] == '$' && tmp[j][i + 1] == '?')
			{
				i += 1;
				printf("%d", parsing->exit_value);
			}
			else
			{
				if (i + 1 == ft_strlen(tmp[j]) && tmp[j + 1] != NULL)
					printf("%c ", tmp[j][i]);
				else
					printf("%c", tmp[j][i]);
			}
		}
		i = -1;
	}
	printf("\n");
	add_history(input);
	return (ft_free_d_ptr((void **)tmp), 0);
}

int	ft_handle_echo(char *input, struct s_parsing *parsing)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (ft_strncmp(input, "echo", ft_strlen(input)) == 0
		|| ft_strncmp(input, "echo ", ft_strlen(input)) == 0)
	{
		printf("\n");
		add_history(input);
		return (0);
	}
	if (ft_strncmp(input, "echo ", 5) == 0 && ft_strchr(input, '$')
		!= NULL && ft_strchr(input, '?') != NULL)
	{
		if (ft_return_value_echo(parsing, input, i, j) == 0)
			return (0);
	}
	return (-1);
}
