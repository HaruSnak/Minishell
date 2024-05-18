
#include "../../includes/minishell.h"

void	ft_condition_operator(char *input, int *i, int *k, char *tmp)
{
	if (((input[*i] == '>' || input[*i] == '<' || input[*i] == '|')
			&& (input[*i + 1] != ' ' && input[*i - 1] != ' '))
		|| (input[*i] == '<' && input[*i + 1] == '<'
			&& input[*i + 2] != ' ' && input[*i - 1] != ' ')
		|| (input[*i] == '>' && input[*i + 1] == '>'
			&& input[*i + 2] != ' ' && input[*i - 1] != ' '))
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
	// printf("%s\n", tmp); //delete
	return (tmp);
}

int	ft_token_value(struct s_parsing *parsing)
{
	int	i;

	i = -1;
	parsing->tkn_value = malloc(sizeof(int *) * 100);
	while (parsing->tkn[++i] != NULL)
	{
		parsing->tkn_value[i] = malloc(sizeof(int) * 100);
		if (!ft_strncmp(parsing->tkn[i], "<", 1))
			parsing->tkn_value[i][0] = IN;
		else if (!ft_strncmp(parsing->tkn[i], ">", 1))
			parsing->tkn_value[i][0] = OUT;
		else if (!ft_strncmp(parsing->tkn[i], ">>", 2))
			parsing->tkn_value[i][0] = APPEND;
		else if (!ft_strncmp(parsing->tkn[i], "<<", 2))
			parsing->tkn_value[i][0] = HEREDOC;
		else if (!ft_strncmp(parsing->tkn[i], "|", 1))
			parsing->tkn_value[i][0] = PIPE;
		else if (i > 0 && (!ft_strncmp(parsing->tkn[i - 1], "<", 1)
				|| !ft_strncmp(parsing->tkn[i - 1], ">", 1)
				|| !ft_strncmp(parsing->tkn[i - 1], "<<", 1)
				|| !ft_strncmp(parsing->tkn[i - 1], ">>", 1)))
			parsing->tkn_value[i][0] = FILE;
		else // PEUT-ETRE VERIF ICI A VOIR
			parsing->tkn_value[i][0] = CMD;
	}
	return (0);
}

/*int	ft_end_verify(char *input, struct s_parsing *parsing)
{
	free(input);
	free(parsing->tkn_cpy);
	return (0);
}*/	

int	ft_handle_verify(char **input, struct s_parsing *parsing, char **envp)
{
	parsing->tkn_cpy = ft_strdup(*input);
	*input = ft_separe_operator(*input);
	parsing->tkn = ft_split(*input, ' ');
	// HERE // Function to quote and double quote
	ft_token_value(parsing);
	// for (int k = 0; parsing->tkn[k] != NULL; k++)
	// {
		// printf("parsing->tkn[%d] = %s ; FLAG: %d\n", k, parsing->tkn[k], *parsing->tkn_value[k]);
	// }
	execution(parsing->tkn, envp, parsing);
	exit(0);
	if (ft_external_cmds(input, parsing, envp) == 0)
		return (ft_end_verify(input, parsing), 0);
	if (ft_find_execve(envp, parsing) == -1)
	{
		printf("%s: command not found\n", *input);
		return (ft_end_verify(input, parsing), -1);
	}
	ft_end_verify(input, parsing);
	return (0);
}
