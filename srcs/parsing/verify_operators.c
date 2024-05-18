
#include "../../includes/minishell.h"

char	**ft_quote(char **input)
{
	int	k;
	int	i;

	k = 0;
	i = -1;
	while (input[++i] != NULL)
	{
		if (ft_strchr(input[i], '\''))
		{
			if (ft_strchr(input[i], '\'') != ft_strrchr(input[i], '\''))
			{

			}
			else if (ft_strchr(input[i], '\'') == ft_strrchr(input[i], '\''))
			{
				input[i] = ft_strtrim(input[i], "\'");
				input[k] = ft_strdup(input[i]);
				k++;
			}
		}
	}
	return (input);
}

char	*ft_separe_operator(char *input)
{
	int		i;
	int		k;
	char	*tmp;

	i = -1;
	k = 0;
	tmp = malloc(sizeof(char) * ft_strlen(input) + 1000);
	while (input[++i] != '\0')
	{
		ft_condition_operator(input, &i, &k, tmp);
	}
	tmp[k] = '\0';
	printf("%s\n", tmp); //delete
	return (tmp);
}

int	ft_handle_verify(char **input, struct s_parsing *parsing, char **envp)
{
	bool	check;
	int		i;
	int		k;

	(void)envp;
	i = -1;
	k = -1;
	check = false;
	*input = ft_separe_operator(*input);
	parsing->test = ft_split(*input, ' ');
	// for (int k = 0; parsing->test[k] != NULL; k++)
		// printf("parsing->test[%d] = %s\n", k, parsing->test[k]);
	// HERE TRANSFORM '' AND ""
	while (parsing->test[++i] != NULL)
	{
		while (parsing->test[i][++k] != '\0')
		{
			if ((parsing->test[i][k] == '>' && parsing->test[i][k + 1] != '>')
			|| (parsing->test[i][k] == '<' && parsing->test[i][k + 1] != '<')
			|| (parsing->test[i][k] == '<' && parsing->test[i][k + 1] == '<')
			|| (parsing->test[i][k] == '>' && parsing->test[i][k + 1] == '>'))
			{
				check = true;
				parsing->k = i;
				//printf("k = %d\n", parsing->k);
				// if (ft_find_execve(parsing->test, envp, parsing, check) == -1)
					// printf("%s: command not found\n", *input);
				break ;
			}
		}
		k = -1;
	}
	add_history(*input);
	ft_free_char(parsing->test);
	if (!check)
		return (-1);
	free(*input);
	return (0);
}
