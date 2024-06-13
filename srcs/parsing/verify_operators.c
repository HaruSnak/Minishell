
#include "../../includes/minishell.h"

// Verify the operators in the input
// Add the token value to the parsing structure
// Handle the verify process for the minishell program
// Return 0 if the process is successful
int	ft_handle_verify(char **input, t_parsing *parsing, char **envp)
{
	char	*tmp;

	parsing->tkn_cpy = ft_strdup(*input);
	*input = ft_separe_operator(*input);
	if (ft_strchr(*input, '\'') != ft_strrchr(*input, '\'')
		|| ft_strchr(*input, '\"') != ft_strrchr(*input, '\"'))
	{
		tmp = ft_strdup(*input);
		free(*input);
		*input = ft_replace_espace(tmp, parsing);
		free(tmp);
	}
	parsing->tkn = ft_split(*input, ' ');
	ft_delete_espace(parsing);
	ft_check_quote(envp, parsing);
	ft_interpret_envp(envp, parsing);
	ft_token_value(parsing);
	// for (int k = 1; parsing->tkn[k] != NULL; k++)
	// {
	// 	//printf("parsing->tkn[%d] = %s | FLAG: %d\n", k, parsing->tkn[k], parsing->tkn_value[k]);
	// 	printf("%s", parsing->tkn[k]);
	// }
	// printf("\n");
	execution(parsing->tkn, envp, parsing);
	ft_end_verify(parsing);
	return (0);
}

	//exit(0);
	/*if (ft_external_cmds(input, parsing, envp) == 0)
		return (ft_end_verify(input, parsing), 0);
	if (ft_find_execve(envp, parsing) == -1)
	{
		printf("%s: command not found\n", *input);
		return (ft_end_verify(input, parsing), -1);
	}*/

// cat < in | grep i
