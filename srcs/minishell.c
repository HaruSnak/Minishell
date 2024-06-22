
#include "../includes/minishell.h"
#include <signal.h>

void	ft_init_main(t_parsing *parsing, t_quote *quote, char **envp, int argc)
{
	parsing->quote = quote;
	parsing->exit_value = 0;
	parsing->pwd = getenv("PWD");
	parsing->tmp = NULL;
	parsing->tmp_env = NULL;
	parsing->tmp_setenv = NULL;
	parsing->n_senv = "OLDPWD";
	parsing->v_senv = "";
	quote->check_d = false;
	quote->check_s = false;
	quote->p = 0;
	ft_setenv(envp, parsing);
	(void)argc;
}

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	struct sigaction	sa;
	struct sigaction	sa_quit;
	t_parsing			parsing;
	t_quote				quote;

	ft_init_main(&parsing, &quote, envp, argc);
	(void)argv;
	ft_init_signal(&sa, &sa_quit);
	input = NULL;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa_quit, NULL);
		input = readline(PROMPT);
		if (!input)
			break ;
		add_history(input);
		ft_handle_verify(&input, &parsing, envp);
		free(input);
	}
	if (parsing.tmp_setenv != NULL)
		ft_free_d_ptr((void ***)&parsing.tmp_setenv);
	return (0);
}
