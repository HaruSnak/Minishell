
#include "../../includes/minishell.h"

void	ft_signal_heredoc(int signum)
{
	g_signal_number = signum;
	ft_putstr_fd("\n", 1);
	rl_done = 1;
	close(0);
}

void	ft_init_signal_heredoc(void)
{
	struct sigaction	sa_sigint;

	sa_sigint.sa_handler = ft_signal_heredoc;
	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
		perror("sigaction");
}
