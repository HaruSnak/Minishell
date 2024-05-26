
#include "../../includes/minishell.h"

int	ft_handle_verify(char **input, t_parsing *parsing, char **envp)
{
	parsing->tkn_cpy = ft_strdup(*input);
	*input = ft_separe_operator(*input);
	if (ft_strchr(*input, '\'') != ft_strrchr(*input, '\'')
		|| ft_strchr(*input, '\"') != ft_strrchr(*input, '\"'))
		*input = ft_replace_espace(*input, parsing);
	parsing->tkn = ft_split(*input, ' ');
	ft_delete_espace(parsing);
	ft_token_value(parsing);
	// for (int k = 0; parsing->tkn[k] != NULL; k++)
	// {
		// printf("parsing->tkn[%d] = %s | FLAG: %d\n", k, parsing->tkn[k], *parsing->tkn_value[k]);
	// }
	// for (int k = 0; parsing->tkn[k] != NULL; k++)
	// {
	// 	printf("parsing->tkn[%d] = %s ; FLAG: %d\n", k, parsing->tkn[k], *parsing->tkn_value[k]);
	// }
	execution(parsing->tkn, envp, parsing);
	// ft_end_verify(input, parsing);
	exit(0);
	// if (ft_external_cmds(input, parsing, envp) == 0)
	// 	return (ft_end_verify(input, parsing), 0);
	// if (ft_find_execve(envp, parsing) == -1)
	// {
	// 	printf("%s: command not found\n", *input);
	// 	return (ft_end_verify(input, parsing), -1);
	// }
	return (0);
}
