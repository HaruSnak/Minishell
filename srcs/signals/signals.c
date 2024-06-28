/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:10:38 by shmoreno          #+#    #+#             */
/*   Updated: 2024/06/27 13:03:52 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_signal(struct sigaction *sa, struct sigaction *sa_quit)
{
	(*sa).sa_handler = ft_signal_handler;
	(*sa_quit).sa_handler = SIG_IGN;
	(*sa_quit).sa_flags = 0;
	(*sa).sa_flags = 0;
	sigemptyset(&(*sa_quit).sa_mask);
	sigemptyset(&(*sa).sa_mask);
}

void	ft_exec_signals_main(struct sigaction sa, struct sigaction sa_quit)
{
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction");
}

void	ft_init_signal_block(void)
{
	struct sigaction	sa_return;
	struct sigaction	sa_quit;


    ft_memset(&sa_return, 0, sizeof(sa_return)); // Delete ? valgrind bug ?
    ft_memset(&sa_quit, 0, sizeof(sa_quit)); // Delete ? valgrind bug ?
	sa_return.sa_handler = ft_signal_return;
	sa_quit.sa_handler = ft_signal_quit;
	sa_quit.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_return.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGINT, &sa_return, NULL) == -1)
		perror("sigaction");
}

int	ft_g_signal(t_parsing *parsing)
{
	if (g_signal_number == SIGINT)
	{
		parsing->exit_value = 130;
		g_signal_number = 0;
		return (1);
	}
	else if (g_signal_number == SIGQUIT)
	{
		parsing->exit_value = 131;
		g_signal_number = 0;
		return (1);
	}
	return (0);
}
