
#include "../includes/minishell.h"
#include <signal.h>

int g_signal = 0;

void	ft_init_main(t_parsing *parsing, t_quote *quote, char **envp, int argc)
{
	parsing->exit_value = 0;
	parsing->pwd = getenv("PWD");
	parsing->tmp = NULL;
	parsing->tmp_env = NULL;
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
	struct termios		term;
	t_parsing			parsing;
	t_quote				quote;

	parsing.quote = &quote;
	ft_init_main(&parsing, &quote, envp, argc);
	(void)argv;
	sa.sa_handler = ft_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	tcgetattr(STDIN_FILENO, &term);
	input = NULL;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		term.c_cc[VQUIT] = _POSIX_VDISABLE;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		input = readline("\033[0;32mminishell\033[0m\xF0\x9F\x90\x9A ");
		add_history(input);
		if (!input)
			break ;
		ft_handle_verify(&input, &parsing, envp);
		free(input);
	}
	return (0);
}
