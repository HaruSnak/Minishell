/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:12 by shmoreno          #+#    #+#             */
/*   Updated: 2024/05/15 17:10:37 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	i = -1;
	k = -1;
	check = false;
	*input = ft_separe_operator(*input);
	parsing->test = ft_split(*input, ' ');
	for (int k = 0; parsing->test[k] != NULL; k++)
	{
		printf("parsing->test[%d] = %s\n", k, parsing->test[k]);
	}
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
				if (ft_find_execve(parsing->test, envp, parsing, check) == -1)
				{
					printf("%s: command not found\n", *input);
				}
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
