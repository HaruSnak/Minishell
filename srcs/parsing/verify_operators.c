
#include "../../includes/minishell.h"

void	ft_handle_verify_bis(t_parsing *parsing, char **envp,
	char **input, char *tmp)
{
	parsing->tkn_cpy = ft_strdup(*input);
	*input = ft_separe_operator(*input);
	if (ft_check_odd_quote(*input) == -1)
		return (free(parsing->tkn_cpy), -1);
	if (ft_strchr(*input, '\'') != ft_strrchr(*input, '\'')
		|| ft_strchr(*input, '\"') != ft_strrchr(*input, '\"'))
	{
		tmp = ft_strdup(*input);
		free(*input);
		*input = ft_replace_espace(tmp, parsing);
		free(tmp);
	}
}

// Verify the operators in the input
// Add the token value to the parsing structure
// Handle the verify process for the minishell program
// Return 0 if the process is successful
int	ft_handle_verify(char **input, t_parsing *parsing, char **envp)
{
	char	*tmp;

	if (ft_handle_empty_cmd(input) == -1)
		return (0);
	ft_handle_verify_bis(parsing, envp, input, tmp);
	parsing->tkn = ft_split(*input, ' ');
	ft_delete_espace(parsing);
	if (ft_error_operator(parsing) == -1)
		return (ft_end_verify(parsing), -1);
	ft_check_quote(envp, parsing);
	ft_interpret_envp(envp, parsing);
	ft_token_value(parsing);
	if (builtins_exec(parsing, envp) == 0)
		return (ft_end_verify(parsing), -1);
	else if (execution(parsing->tkn, envp, parsing))
		ft_end_verify(parsing);
	return (0);
}
