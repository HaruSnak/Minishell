

#include "../includes/minishell.h"
#include <signal.h>

int g_signal = 0;

void	ft_init_main(struct s_parsing *parsing,
	char **envp, int argc)
{
	parsing->exit_value = 0;
	parsing->pwd = getenv("PWD");
	parsing->tmp = NULL;
	parsing->tmp_env = NULL;
	parsing->n_senv = "OLDPWD";
	parsing->v_senv = "";
	ft_setenv(envp, parsing);
	(void)argc; 
}

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	struct sigaction	sa;
	struct termios		term;
	struct s_parsing	parsing;

	ft_init_main(&parsing, envp, argc);
	(void)argv;
	sa.sa_handler = ft_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		term.c_cc[VQUIT] = _POSIX_VDISABLE;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		input = readline("\033[0;32mminishell\xF0\x9F\x90\x9A \033[0m");
		if (!input)
			break ;
		if (ft_handle_verify(&input, &parsing, envp) == 0)
			continue ;
		free(input);
	}
	return (0);
}
