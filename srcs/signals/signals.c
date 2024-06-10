/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:10:38 by shmoreno          #+#    #+#             */
/*   Updated: 2024/06/07 15:19:47 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Handle signals for the minishell program
void	ft_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal_quit(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 1);
	}
}

void	ft_signal_return(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
	}
}

void	ft_init_signal(struct sigaction *sa, struct sigaction *sa_quit)
{
	(*sa).sa_handler = ft_signal_handler;
	(*sa_quit).sa_handler = SIG_IGN;
	sigemptyset(&(*sa_quit).sa_mask);
	sigemptyset(&(*sa).sa_mask);
	(*sa_quit).sa_flags = 0;
	(*sa).sa_flags = 0;
}

void	ft_init_signal_block(void)
{
	struct sigaction	sa_return;
	struct sigaction	sa_quit;

	sa_return.sa_handler = ft_signal_return;
	sa_quit.sa_handler = ft_signal_quit;
	sa_quit.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_return.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGINT, &sa_return, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction");
}
