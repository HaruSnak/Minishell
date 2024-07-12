
#include "../../includes/minishell.h"

void	ft_handle_verify_bis(char **input)
{
	*input = ft_separe_operator(*input);
	/*if (ft_strchr(*input, '\'') != ft_strrchr(*input, '\'')
		|| ft_strchr(*input, '\"') != ft_strrchr(*input, '\"'))
	{
		tmp = ft_strdup(*input);
		free(*input);
		*input = ft_replace_espace(tmp, parsing);
		free(tmp);
	}*/
}

// Verify the operators in the input
// Add the token value to the parsing structure
// Handle the verify process for the minishell program
// Return 0 if the process is successful
int	ft_handle_verify(char **input, t_parsing *parsing, char **envp)
{
	//char	*tmp;

	//tmp = NULL;
	if (ft_handle_empty_cmd(input) == -1)
		return (0);
	parsing->tkn_cpy = ft_strdup(*input);
	if (ft_check_odd_quote(*input) == -1)
		return (free(parsing->tkn_cpy), -1);
	ft_handle_verify_bis(input);
	parsing->tkn = ft_split_tkn(*input, ' ');
	//ft_delete_espace(parsing);
	for (int i = 0; parsing->tkn[i]; i++)
		printf("1parsing->tkn[%d] = %s\n", i, parsing->tkn[i]);
	if (ft_error_operator(parsing) == -1)
		return (ft_end_verify(parsing), -1);
	ft_check_quote(envp, parsing);
	ft_interpret_envp(envp, parsing);
	ft_token_value(parsing);
	for (int i = 0; parsing->tkn[i]; i++)
		printf("1parsing->tkn[%d] = %s\n", i, parsing->tkn[i]);
	exit(0);
	if (builtins_exec(parsing, envp) == 0)
		return (ft_end_verify(parsing), -1);
	else
		execution(parsing->tkn, envp, parsing);
	ft_end_verify(parsing);
	return (0);
}
